#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <unistd.h>
#include <fcntl.h>
//#include <pthread.h>
//#include <error.h>
//#include <string.h>
#include <map>
#include <vector>
#include "threadpool.h"
using namespace std;

const int MAXEPOLLSIZE=1000;
enum Type {HEART,DATA};
typedef struct  PACKET_HEAD
{
	Type type;
	char s[100];
	int len;
}PACKET_HEAD;

class Server
{
    public:
		Server(int p=9877);
		~Server();
		void Bind();
		void Listen();
		void Start();
	    void Recv(int num);
    private:
		int port;
		int listenfd;
		struct sockaddr_in server_addr;
		
		//epoll处理
		int epfd;
		struct epoll_event ev;
		struct epoll_event events[MAXEPOLLSIZE];
		int nfds;
		static int cur_nfds;
		
		map<int,pair<string,int> > mmap;
		
		pthread_mutex_t mutex;

		void Accept();
		friend void *heart_header(void *arg);
};
int Server::cur_nfds=1;

Server::Server(int p)
{
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd<0)
    {
		cerr<<strerror(errno)<<endl;
		exit(0);
    }
	cout<<"create socket success"<<endl;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(0);
    server_addr.sin_port=htons(p);
    
	//int opt=1;
	//setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	mutex=PTHREAD_MUTEX_INITIALIZER;

	//把感兴趣的事件listenfd添加到ev中
	epfd=epoll_create(MAXEPOLLSIZE);
	ev.events=EPOLLIN;
	ev.data.fd=listenfd;
	int res=0;
	if((res=epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev))<0)
	{
		cerr<<"epoll_ctl error: "<<strerror(errno)<<endl;
		exit(res);
	}
	mutex=PTHREAD_MUTEX_INITIALIZER;
}

Server::~Server()
{
	for(int i=0;i<MAXEPOLLSIZE;++i)
		close(i);
}

void Server::Bind()
{ 
    socklen_t len=sizeof(server_addr);
    int res=bind(listenfd,(struct sockaddr*)&server_addr,len);
    if(res<0)
    {
		cerr<<strerror(errno)<<endl;
		exit(0);
    }
	cout<<"bind success"<<endl;
    return ;
}

void Server::Listen()
{
    int res=listen(listenfd,1024);
    if(res<0)
    {
		cerr<<strerror(errno)<<endl;
		exit(0);
    }
	cout<<"listen suceess"<<endl;
    return ;
}

void Server::Accept()
{
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    socklen_t len=sizeof(client_addr);
    int new_fd=accept(listenfd,(struct sockaddr*)&client_addr,&len);
    if(new_fd<0)
    {
		cerr<<strerror(errno)<<endl;
		exit(0);
    }
	//new_fd:已连接套接字，与客户端的通信通过已连接套接字
	if(new_fd>=MAXEPOLLSIZE)
	{
		cerr<<"too many connection than:"<<MAXEPOLLSIZE<<endl;
		close(new_fd);
		return ;
	}

	int res=fcntl(new_fd,F_SETFL,fcntl(new_fd,F_GETFD,0)|O_NONBLOCK);
	if(res==-1)
	{
		cerr<<"set nonblcok error"<<strerror(errno)<<endl;
	}
	ev.events=EPOLLIN;
	ev.data.fd=new_fd;
	
	if((res=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&ev))<0)
	{
		cerr<<"add socket to epoll error: "<<strerror(errno)<<endl;
		return ;
	}
	//多个客户连接的话只有一个客户调用accept，其他阻塞
	//所以cur_nfds不用互斥访问
	++cur_nfds;

    char ip[32];
	int len_ip=sizeof(ip);
    inet_ntop(AF_INET,&client_addr.sin_addr,ip,len_ip);
    cout<<"accept success,ip is:"<<ip<<endl;
    mmap.insert({new_fd,{ip,0}});    
}

void *heart_header(void *args)
{
	Server *s=(Server *)args;

	while(true)
	{
		for(auto it=s->mmap.begin();it!=s->mmap.end();)
		{
			pthread_mutex_lock(&(s->mutex));
			if(it->second.second>=10)//30s
			{
				cout<<"The client :"<<it->first<<" offline"<<endl;
				close(it->first);
				--Server::cur_nfds;
				s->mmap.erase(it++);
			}
			else if(it->second.second>=0&&it->second.second<10)
			{
				++(it->second.second);
				++it;
			}
			else
				++it;
			pthread_mutex_unlock(&(s->mutex));
		}
		sleep(3);//定时三秒
	}
	//return nullptr;
}

/*typedef void (Server::*ptr_recv)(int );
ptr_recv fun=&Server::Recv;*/

void Server::Start()
{
	//in main thread open thread handle HeartBeat
	pthread_t pid;
	int res=pthread_create(&pid,nullptr,heart_header,(void *)this);
	if(res!=0)
	{
		cerr<<strerror(errno)<<endl;
		exit(0);
	}
	//open threadpool
	ThreadPool tp(6);
	tp.initializer();

	while(true)
	{
		nfds=epoll_wait(epfd,events,cur_nfds,-1);
		if(nfds==-1)
		{
			cerr<<"epoll wait error: "<<strerror(errno)<<endl;
			continue;
		}

		for(int i=0;i<nfds;++i)
		{
			if(events[i].data.fd==listenfd)
				Accept();
			else if(events[i].events&EPOLLIN)
			{

				char buff[1024];
				int num=events[i].data.fd;//read fd
				int fds=open("2.txt",O_RDWR|O_TRUNC);
				
				PACKET_HEAD head;
				res=recv(num,&head,sizeof(head),0);
				if(head.type==HEART)//HeartBeat packge
				{
					cout<<"reveive heart-beat from client"<<endl;
					if(res==0)
					{
						epoll_ctl(epfd,EPOLL_CTL_DEL,num,&ev);
						shutdown(num,SHUT_RDWR);
						cout<<num<<" -> log out"<<endl;
						--Server::cur_nfds;
						continue;
					}
				}
				else if(head.type==DATA)//data packet
				{
					//pthread_mutex_lock(&mutex);
					mmap[num].second=0;
					//pthread_mutex_unlock(&mutex);
					int len=0;
					if(len!=head.len)
					{
						memset(buff,'\0',sizeof(buff));
						//int res=recv(num,&head.s,1023,0);
						strcpy(buff,head.s);
						len=strlen(head.s);
						if(res==0)//close sockfd
						{
							epoll_ctl(epfd,EPOLL_CTL_DEL,num,&ev);
							shutdown(num,SHUT_RDWR);
							cout<<num<<" -> log out"<<endl;
							--Server::cur_nfds;
							break ;
						}
						else if(res<0)
						{
							if(errno==EAGAIN||errno==EWOULDBLOCK)
							{
								ev.data.fd=num;
								ev.events=EPOLLIN|EPOLLET;
								epoll_ctl(epfd,EPOLL_CTL_MOD,num,&ev);
								//goto F;
							}
						}
						write(fds,buff,len);
						//len-=res;
					}
					memset(buff,0,sizeof(buff));
					lseek(fds,0,SEEK_SET);
					int r=read(fds,buff,len);
					if(r<0)
						cerr<<strerror(errno)<<endl;
					//cout<<buff<<endl;
	
					//intptr_t *
					Task *t=new Task(buff,num);
					tp.add_task(t);
				}
			}
		}
	}
	return ;
}


int main()
{	
	//设置每个进程打开的最大文件描述符数
	struct rlimit rt;
	rt.rlim_cur=rt.rlim_max=MAXEPOLLSIZE;
	int res=0;
	if((res=setrlimit(RLIMIT_NOFILE,&rt)==-1))
	{
		cerr<<"setrlimit error:"<<strerror(errno)<<endl;
		return 0;
	}

	Server s;
	s.Bind();
	s.Listen();
	s.Start();

	return 0;
}
