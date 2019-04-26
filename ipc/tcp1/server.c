#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 1204
#define SERV_PORT 9877
#define LISTENQ 1024
/*
 *	若使用wait，会导致使用wait的进程(父进程)阻塞，直到子进程结束或者收到一
 *信号为止；如果在同一台主机上运行，启动多个客户信号处理函数只会执行一次，在
 *不同主机上运行，信号处理函数执行两次，一次是产生信号，一次是其他信号处理
 *函数在执行时发生，也不能如下在循环中调用wait：没有办法防止wait正在运行的
 *子进程尚有未终止的阻塞。
 *	用waitpid，指定WNOHANG选项，提供一个非阻塞的wait版本，pid=-1等待任
 *何一个子进程退出，与wait作用一样，所以用waitpid。1.在信号处理函数中，如果
 *有子进程终止，通过while一次性回收2.非阻塞模式：保证回收最后一个中止的子进
 *程后，没有子进程退出时，waitpid返回出错，主进程从信号处理函数中跳出而不是
 *阻塞在信号处理函数中
 */
void header(int signo)
{
	pid_t pid;
	int stat;

	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child %d terminated\n",pid);

	return;
}

void str_echo(int sockfd)
{
	ssize_t n;
	char buffer[MAXLINE];

again:
	while((n=read(sockfd,buffer,MAXLINE))>0)
		write(sockfd,buffer,n);

	//处理被中断的慢系统调用
	if(n<0&&errno==EINTR)
		goto again;
	else if(n<0)
	{
		puts("str_echo:read error");
		exit(1);
	}
}

int main()
{
	int listenfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in cliaddr,servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);

	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	listen(listenfd,LISTENQ);

	/*
	 *客户套接字发送FIN给服务器，服务器收到回应ACK以确认，这就是TCP的终止链
	 *的前半部分
	 *当服务器TCP收到FIN时，该连接的读半部关闭，read返回0,str_echo返回，至
	 *子进程服务器exit终止返回至main函数，子进程服务器打开的所有描述符全部
	 *关闭，由子进程关闭套接字会发tcp终止连接的最后连个分节，一个服务器到
	 *客户的FIN和客户到服务器的ACK，至此完全终止链接，客户套接字进入
	 *TIME_WAIT状态。由于任何子进程终止时会给父进程发放送一个SIGCHLD信号，该
	 *信号的默认处理是忽略，父进程不处理此信号，子进程会进入僵尸状态，所以父
	 *进程要捕获该信号。
	 */
	signal(SIGCHLD,header);

	while(1)
	{
		socklen_t clilen=sizeof(cliaddr);
		
		/*
		 * 当一直没有客户连接到服务器，accept函数会阻塞，当在accept中阻塞时
		 * 收到某个信号且从信号处理程序中返回，这个系统调用会被中断，调用返
		 * 错误，设置errno为EINTR，对于accept系统调用要进行人为重启，但是co
		 * nnect不能重启，否则会返回错误，处理方法是：用select等待连接而完成
		 *递交SIGCHLD信号时，父进程阻塞于accept调用
		 */
		int connfd=accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
		if(connfd<0)
			if(errno==EINTR)
				continue;
			else
			{
				puts("accept error");
				exit(1);
			}

		pid_t cpid;
		//fork之后listenfd和connfd的引用计数都为2
		if((cpid=fork())==0)
		{
			close(listenfd);//关闭监听套接字，时listenfd计数一直为一
			str_echo(connfd);
			close(connfd);
			exit(0);
		}
		close(connfd);//新的客户由子进程提供服务，父进程可以关掉已连接套接字
	}
	exit(0);
}
