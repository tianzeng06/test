#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#define SERV_PORT 9877
#define MAXLINE 1024
#define max(a,b) ((a)>(b)?(a):(b))
void str_cli(FILE *fp,int sockfd)
{
	char buffer[MAXLINE];
	int stdineof=0;

	fd_set rest;
	FD_ZERO(&rest);
	
	int n;
	while(1)
	{
		if(stdineof==0)
			FD_SET(fileno(fp),&rest);

		FD_SET(sockfd,&rest);//把socked描述符加入rest集合
		
		int maxfd=max(fileno(fp),sockfd)+1;
		/*
		 *客户端等待可读：标准输入可读或是套接字可读，select返回后会把以前
		 *加入的但并无时间发生的fd清空，所以每次select开始之前要把fd逐个加入
		 */
		select(maxfd,&rest,NULL,NULL,NULL);

		/*等待套接字可读
		 * 1.对端tcp发送数据，该套接字变为可读，read并返回个大于0的数
		 * 2.对端tcp发送FIN(对端进程终止)，该套接字变为可读，read返回0(EOF)
		 * 3.对端tcp发送RST(对端主机)崩溃并重启，该套接字变为可读，read返回
		 *	 -1，errno中含有确切的错误代码
		 */
		/*补充下服务器端的套接字可读或可写
		 * 1.accept成功之后便是可读
		 * 2.当客户端发送recv函数，服务器端便知道客户端可写，
		 */
		if(FD_ISSET(sockfd,&rest))
		{
			if((n=read(sockfd,buffer,MAXLINE))==0)
				if(stdineof==1)
					return;
				else
				{
					puts("str_cli: server terinated prematurely");
					exit(1);
				}
			else if(n==-1)
			{
				printf("%s\n",strerror(errno));
				exit(1);
			}
			else
				write(fileno(stdout),buffer,n);
		}

		//等待stdin可读，有数据就可读
		if(FD_ISSET(fileno(fp),&rest))
		{
			//客户端输入完成
			if((n=read(fileno(fp),buffer,MAXLINE))==0)
			{
				stdineof=1;
				/*SHUT_WR
				 * send FIN，留在当前缓冲区中的数据被发送，后跟TCP的终止序列
				 * 不论socket的引用是否为0，都关闭；在标准输入的方式下，输入
				 * 的eof并不以为socket同时也完成了读，有可能请求在区服务器的
				 * 路上，或者答应可能返回客户的路上，所以需要一种关闭tcp一般
				 * 的方法，给服务器发送FIN，告诉服务器我们已经完成了数据输入
				 * 但socket仍打开保持读。
				 */
				shutdown(sockfd,SHUT_WR);
				//客户端完成了数据发送，要清除stdin文件描符，防止再次发送数
				//据
				FD_CLR(fileno(fp),&rest);
				continue;
			}

			write(sockfd,buffer,n);
		}
	}
	return ;
}


int main(int argc,char **argv)
{
	//命令行获取服务器ip
	if(argc!=2)
	{
		puts("please input tcplicent <IP-address");
		exit(1);
	}

	int sockfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in servaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(SERV_PORT);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);//把assic转换为二进制

	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

	str_cli(stdin,sockfd);
	exit(0);
}
