/*************************************************************************
    > File Name: epollserver.h
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月23日 星期五 17时07分25秒
 ************************************************************************/

#ifndef EPOLL_SERVER_H
#define EPOLL_SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>//write头文件
#include <errno.h>
#include "threadpool.h"

#define MAX_EVENT 1024
#define MAX_BUFFER 2048
using namespace std;

class Basetask
{
	public:
		virtual void doit()=0;
};

class Task:public Basetask
{
	private:
		int sockfd;
		char msg[MAX_BUFFER];
	
	public:
		Task(int ,char *);
		void doit();
};

Task::Task(int fd,char *str):sockfd(fd)
{
	memset(msg,'\0',sizeof(msg));
	strcpy(msg,str);
}

void Task::doit()
{
	cout<<"server reveive message is: "<<msg<<endl;
	write(sockfd,msg,strlen(msg));
	//Threadpool<Task>::mv_to_idle(tid);
}

class Epollserver
{
	private:
		bool is_stop;//是否停止epoll_wait
		int num;//线程数目
		int sockfd;
		int port;
		int epollfd;
		Threadpool<Task> *pool;//线程池的指针
		epoll_event events[MAX_EVENT];
		struct sockaddr_in servaddr;
	
	public:
		Epollserver(int p,int n);
		Epollserver(){}
		~Epollserver();
		void init();
		void epoll();
		static int setnonblocking(int fd);
		static void addfd(int epollfd,int sockfd,bool onshot);
};
Epollserver::Epollserver(int p,int n):port(p),num(n),is_stop(false),
						pool(NULL)
{

}

Epollserver::~Epollserver()
{
	delete pool;
}

void Epollserver::init()
{
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);

	//监听套接字
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		cerr<<"Epollserver socket init error"<<endl;
		exit(1);
	}

	int tmp=bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(tmp<0)
	{
		cerr<<"Epollserver bind init error: "<<strerror(errno)<<endl;
		exit(1);
	}

	tmp=listen(sockfd,10);
	if(tmp<0)
	{
		cerr<<"Epollserver listen init error:"<<strerror(errno)<<endl;
		exit(1);
	}

	epollfd=epoll_create(1024);
	if(epollfd<0)
	{
		cerr<<"Epollserver epoll_create init error"<<endl;
		exit(1);
	}

	//创建线程池,num是线程池中线程的个数,调用构造函数
	pool=new Threadpool<Task>(num); 
}

void Epollserver::epoll()
{
	pool->start();//启动线程池

	addfd(epollfd,sockfd,false);
	while(!is_stop)
	{
		int ret=epoll_wait(epollfd,events,MAX_EVENT,-1);
		if(ret<0)
		{
			cerr<<"epoll_wait error"<<endl;
			exit(1);
		}

		for(int i=0;i<ret;++i)
		{
			//int fd=events[i].data.fd;
			if(events[i].data.fd==sockfd)
			{
				struct sockaddr_in cliaddr;
				socklen_t len=sizeof(cliaddr);
				//accpet 返回已连接套接字
				int confd=accept(sockfd,(struct sockaddr *)&cliaddr,&len);
				Epollserver::addfd(epollfd,confd,false);
			}
			else if(events[i].events&EPOLLIN)//有数据可读
			{
				char buffer[MAX_BUFFER];
				int fd=events[i].data.fd;
	readagain:	memset(buffer,0,sizeof(buffer));
				ret=read(fd,buffer,MAX_BUFFER-1);
				if(ret==0)//某个fd关闭连接
				{
					struct epoll_event ev;
					ev.events=EPOLLIN;
					ev.data.fd=fd;
					epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
					shutdown(fd,SHUT_RDWR);
					cout<<fd<<" exit"<<endl;
					continue;
				}
				else if(ret<0)//读取失败,返回-1
				{
					if(errno==EAGAIN)
					{
						cout<<"read error. read again"<<endl;
						goto readagain;
						break;
					}
				}
				else//读取成功
				{
					Task *task=new Task(fd,buffer);
					pool->append_task(task);
				}
			}//else if
			else
				cerr<<"something else had happend"<<endl;
		}//for
	}//while
	close(sockfd);
	pool->stop();
}

int Epollserver::setnonblocking(int fd)
{
	int old_opt=fcntl(fd,F_GETFL);
	int new_opt=old_opt|O_NONBLOCK;
	fcntl(fd,F_SETFL,new_opt);
	return old_opt;
}

void Epollserver::addfd(int epollfd,int sockfd,bool oneshot)
{
	epoll_event event;
	event.data.fd=sockfd;
	event.events=EPOLLIN|EPOLLET;
	if(oneshot)
		event.events|=EPOLLONESHOT;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,sockfd,&event);
	Epollserver::setnonblocking(sockfd);
}

#endif
