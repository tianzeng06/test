/*************************************************************************
    > File Name: server.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月04日 星期一 09时35分26秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

void header(int num)
{
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		cout<<"child:"<<pid<<"terminated"<<endl;
	return ;
}
void str_echo(int fd)
{
	ssize_t n=0;
	char buf[1024];
again:while((n=read(fd,buf,1024))>0)
		  write(fd,buf,n);
	  //处理中断系统调用错误
	  if(n<0&&errno==EINTR)
		  goto again;
	  else if(n<0&&errno==ECONNRESET)//1.
	  {
		  cerr<<"reset by perr"<<endl;
		  exit(0);
	  }
	  else
		  cerr<<"read error"<<endl;
}

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	int keepidle=1;
	setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,(void *)&keepidle,sizeof(keepidle));
	sockaddr_in cliaddr,servaddr;
	memset(&servaddr,sizeof(servaddr),0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9877);
	servaddr.sin_addr.s_addr=htonl(0);//INADDR_ANY
	
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	listen(sockfd,1024);
	signal(SIGCHLD,header);
	while(1)
	{
		socklen_t len=sizeof(cliaddr);
		//1.模拟较忙的服务器
		//sleep(10);//完成三路握手后客户发送RST(复位)
	conn:int connfd=accept(sockfd,(sockaddr *)&cliaddr,&len);
		 //处理被中断的系统调用，因为在阻塞于某个中断时，这时候进来一个
		 //信号，执行信号处理函数返回后系统调用会返回EINTR
		if(connfd<0)
		{
			if(errno==EINTR)
				goto conn;
			else if(errno==ECONNABORTED)
			{
				cerr<<"accept:connect reset by peer"<<endl;
				exit(0);
			}
		}
		else
		{
			pid_t pid;
			if((pid=fork())==0)
			{
				close(sockfd);
				char des[100];
				//cout<<getpid()<<endl;
				inet_ntop(AF_INET,&cliaddr.sin_addr.s_addr,des,sizeof(des));
				cout<<"accept success,cliaddr is:"<<des<<endl;
				str_echo(connfd);
				close(connfd);
				exit(0);
			}
			close(connfd);
		}
	}
	return 0;
}
