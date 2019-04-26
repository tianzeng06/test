#include "header.h"

using namespace std;

int main()
{
	list<int> list_of_client;
	struct sockaddr_in cliaddr;
	cliaddr.sin_family=AF_INET;
	cliaddr.sin_port=htons(SERV_PORT);
	char ip[BUFFER_SIZE];
	fgets(stdin,ip);
	int len=strlen(ip);
	if(ip[len-1]=='\n')
		ip[len-1]='\0';
	inet_pton(AF_INET,ip,&cliaddr.sin_addr);

	clock_t start=clock();
	for(int i=0;i<EPOLL_SIZE;++i)
	{
		int sockfd=sock(AF_INET,SOCK_STREAM,0);
		connect(sockfd,(struct sockaddr *)&cliaddr,sizeof(sockaddr));
		list_of_client.push_back(sockfd);

		bzero(&message,BUFFER_SIZE);
		recv=(sockfd,message,BUFFER_SIZE,0);
		puts(message);
	}

	list<int>::iterator it;
	for(it=list_of_client.begin();it!=list_of_client.end();++it)
		close(*it);

	printf("test passed at: %.2f second\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	printf("total sever connection was: %d\n",EPOLL_SIZE);
	
	return 0;
}


