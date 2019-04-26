/*************************************************************************
    > File Name: client.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月31日 星期日 10时49分18秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
using namespace std;

enum Type
{
	HEART,DATA
};

typedef struct PACKET_HEAD
{
	Type type;
	char s[100];
	int len;
}PACKET_HEAD;

void *heart(void *arg);

class Client
{
	private:
		//bool flag;

		sockaddr_in serv_addr;
		socklen_t ser_len;
		string ip;
		int port;
		int sockfd;

		friend void *heart(void *arg);
		void start();

		pthread_mutex_t mutex;
	public:
		Client(string i,int p);
		~Client();
		void Connect();
		void cli_echo();
};

Client::Client(string i,int p):ip(i),port(p)
{
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	if(inet_pton(AF_INET,ip.c_str(),&serv_addr.sin_addr)==0)
	{
		cerr<<"client ip transformation error: "<<strerror(errno)<<endl;
		exit(1);
	}
	serv_addr.sin_port=htons(port);
	ser_len=sizeof(serv_addr);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		cerr<<"socket error: "<<strerror(errno)<<endl;
		exit(1);
	}
	const char opt=1;
	setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&opt,sizeof(opt));
	
	mutex=PTHREAD_MUTEX_INITIALIZER;

	//flag=true;
	cout<<"create socket success"<<endl;
}

Client::~Client()
{
	close(sockfd);
}

void Client::Connect()
{
	if(connect(sockfd,(struct sockaddr *)&serv_addr,ser_len)<0)
	{
		cerr<<"client connect error: "<<errno<<"->"<<strerror(errno)<<endl;
		return ;
	}
	cout<<"connect success"<<endl;
}
void *heart(void *arg)
{
	Client *c=(Client *)arg;
	int count=0;
	PACKET_HEAD head;

	while(true)
	{
		//PACKET_HEAD head;
		head.type=HEART;
		head.len=0;
		
		pthread_mutex_lock(&(c->mutex));	
		send(c->sockfd,&head,sizeof(head),0);
		pthread_mutex_unlock(&(c->mutex));
		
		sleep(3);
		++count;
		if(count>10)
			break;
	}
	return nullptr;
}

void Client::start()
{
	pthread_t tid;
	int res=pthread_create(&tid,nullptr,heart,(void *)this);
	if(res!=0)
	{
		cerr<<"create heart error: "<<strerror(res)<<endl;
		exit(res);
	}
}
void handle(int num)
{
	cerr<<"server close connect"<<endl;
	exit(0);
}
void Client::cli_echo()
{
	start();

	PACKET_HEAD head;
	fd_set set;
	FD_ZERO(&set);
	char buff[1024];
	bool in_eof=false;
	
	signal(SIGPIPE,handle);
	while(true)
	{
		FD_SET(fileno(stdin),&set);
		FD_SET(sockfd,&set);
		int maxfd=max(fileno(stdin),sockfd)+1;
		int res=select(maxfd+1,&set,nullptr,nullptr,nullptr);
		if(res<0)
		{
			cerr<<"select err: "<<strerror(errno)<<endl;
			exit(res);
		}
		int n=0;
		
		if(FD_ISSET(sockfd,&set))
		{
			n=recv(sockfd,buff,1023,0);
	
			if(in_eof)
			{
				cout<<"client log out"<<endl;
				return ;
			}
			if(n==0)
			{
				cerr<<"server terinated prematurely"<<endl;
				exit(0);
			}
			write(fileno(stdout),buff,n);
		}
		else if(FD_ISSET(fileno(stdin),&set))
		{
			if((n=read(fileno(stdin),buff,1023))==0)
			{
				//shutdown(sockfd,SHUT_WR);
				FD_CLR(fileno(stdin),&set);
				continue;
			}
			if(strcmp("$",buff)==0)
			{
				in_eof=true;
			}
			else
			{
				head.type=DATA;
				strcpy(head.s,buff);
				head.len=n;
				
				pthread_mutex_lock(&mutex);
				send(sockfd,&head,sizeof(head),0);
				pthread_mutex_unlock(&mutex);
				//cout<<sizeof(head)<<endl;
			}
		}
	}
	return ;
}

int main()
{
	Client c("127.0.0.1",9877);
	c.Connect();
	cout<<"client send data with $ over."<<endl;
	c.cli_echo();
	return 0;
}
