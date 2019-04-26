#include "header.h"

using namespace std;
list<int> client_list;

int handle_message(int clientfd)
{
	char buffer[BUFFER_SIZE],message[BUFFER_SIZE];
	bzero(buffer,BUFFER_SIZE);
	bzero(message,BUFFER_SIZE);

	int len=recv(clientfd,buffer,BUFFER_SIZE);
	if(len==0)
	{
		close(client);
		client_list.remove(clientfd);
	}
	else
	{
		if(client_list.size()==1)
		{
			send(clientfd,STR_NOONE_CONNECTED,strlen(STR_NOONE_CONNECTED),0);
			return len;
		}

		sprintf(message,STR_MESSAGE,clientfd,buffer);
		list<int>::iterator it;
		for(it=client_list.begin();it!=client_list.end();++it)
			if(*it!=clientfd)
				send(*it,message,BUFFER_SIZE,0);

	}
	return len;
}

int main()
{
	int listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd<0)
	{
		perror("listenfd eval");
		exit(-1);
	}
	setnonblock(listenfd);

	struct sockaddr_in servaddr,cliaddr;
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);
	
	int bindfd=bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(bindfd<0)
	{
		perror("bindfd eval");
		exit(-1);
	}

	listen(listenfd,LISTENQ);

	static struct epoll_event ev,events[EPOLL_SIZE];
	ev.events=EPOLLIN|EPOLLET;
	int epfd=epoll_create(EPOLL_SIZE);
	if(epfd<0)
	{
		perror("epfd eval");
		exit(-1);
	}
	ev.data.fd=listenfd;

	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
	int n;
	while(1)
	{
		int epoll_events_count=epoll_wait(epfd,events,EPOLL_SIZE,EPOLL_RUN_TIMEOUT);
		clock_t start=clock();
		for(int i=0;i<epoll_events_count;++i)
			if(events[i].data.fd==listenfd)
			{
				int clientfd=accept(listenfd,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
				setnonblock(clientfd);
				ev.data.fd=clientfd;
				epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&ev);
				client_list.push_back(clientfd);

				char message[BUFFER_SIZE];
				bzero(message,BUFFER_SIZE);
				n=sprintf(message,"welcome to chat,you id is: %d",clientfd);
				send(clientfd,message,BUFFER_SIZE,0);
			}
			else
				handle_message(events[i].data.fd);

		printf("static: %d events handled at: %.2f seconds\n",epoll_events_count,(double)(clock()-start)/CLOCKS_PER_SEC);
	}
	close(listenfd);
	close(epfd);

	return 0;
}
