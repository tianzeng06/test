/*************************************************************************
    > File Name: client.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月04日 星期一 08时51分56秒
 ************************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
using namespace std;

void cli_echo(int sockfd)
{
	//设置等待时间等待connect连接成功
	struct timeval tval;
	tval.tv_sec=6;
	tval.tv_usec=0;

	fd_set set,wset;
	FD_ZERO(&set);
	FD_ZERO(&wset);
	string s;
	while(1)
	{
		FD_SET(fileno(stdin),&set);
		FD_SET(sockfd,&set);
		FD_SET(sockfd,&wset);
	
		//客户端对应两个输入，套接字和用户输入，他不能单纯的阻塞在某个中断
		//上，应该阻塞在任何一个中断上
		int maxfd=max(fileno(stdin),sockfd)+1;
		int res=select(maxfd,&set,&wset,NULL,&tval);
		if(res<=0)
		{
			cerr<<"connect time out"<<endl;
			close(sockfd);
			exit(0);
		}
		/*
		 * socket描述符只可写，连接成功
		 * 若即可读又可写，分为两种情况：
		 * 第一种:出错,因为可能是connect连接成功后远程主机断开连接close(socket)
		 * 第二种:连接成功，socket读缓冲区得到了远程主机发送的数据，根据
		 * connect连接成功后errno的返回值来判定，或通过getsockopt函数返回值
		 * 来判断,但linux下getsockopt始终返回0，错误的情况下应返回-1
		 */
		int n=0;
		if(FD_ISSET(fileno(stdin),&set))
		{
			if((n=read(fileno(stdin),(void*)s.c_str(),1024))==0)
			{
				shutdown(sockfd,SHUT_WR);
				continue;
			}
			
			//只可写肯定返回成功
			if(FD_ISSET(sockfd,&wset)&&!FD_ISSET(sockfd,&set))
			{
				//3.对已经收到RST的套接字进行写操作，内核向进程发送SIGPIPE
				//第一次write引发RST，第二次产生SIGPIPE,如何在第一次写操作
				//捕获SIGPIPE，做不到
				write(sockfd,(void *)s.c_str(),1);
				sleep(1);
				write(sockfd,(void *)(s.c_str()+1),n-1);
			}
		}
		else if(FD_ISSET(sockfd,&set)&&FD_ISSET(sockfd,&wset))
		{
			int err;
			socklen_t len=sizeof(err);
			//不通过getsockopt返回值判断，通过返回的参数判断
			getsockopt(sockfd,SOL_SOCKET,SO_ERROR,&err,&len);
			if(err)
			{
				cerr<<err<<" :"<<strerror(err)<<endl;
				exit(0);
			}
			if((n=read(sockfd,(void *)s.c_str(),1024))>0)
				write(fileno(stdout),(void *)s.c_str(),n);
			if(n==0)//2.服务器端进程关闭,客户会收到服务器的一个RST
			{
				cerr<<strerror(errno)<<endl;
				exit(0);
			}
		}
	}
	return ;
}

int main()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	//禁用nagle算法
	const char opt=1;
	setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&opt,sizeof(opt));

	sockaddr_in servadddr;
	memset(&servadddr,sizeof(servadddr),0);
	servadddr.sin_family=AF_INET;
	servadddr.sin_port=htons(9877);
	inet_pton(AF_INET,"127.0.0.1",&servadddr.sin_addr);

	int res=connect(sockfd,(struct sockaddr *)&servadddr,sizeof(servadddr));

	//1.connect返回立即发送RST
	struct linger l;
	l.l_onoff=1;
	l.l_linger=0;
	setsockopt(sockfd,SOL_SOCKET,SO_LINGER,&l,sizeof(l));
	fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL,0)|O_NONBLOCK);
	//res==0连接成功
	//==-1开始三次握手但未完成
	if(res==-1)
	{
		if(errno!=EINPROGRESS)//表示正在试图连接，不能表示连接失败
		{
			//oeration now progress:套接字为非阻塞套接字，且原来的连接未完成
			cout<<strerror(errno)<<endl;
			exit(0);
		}
		/**
		 * 也可以在此处处理select连接
		 */
	}
	cli_echo(sockfd);
	close(sockfd);
	return 0;
}
