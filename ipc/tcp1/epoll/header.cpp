#include "header.h"

int setnonblcok(int sockfd)
{
	int res=fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFD,0)|O_NONBLOCK);
	if(res<0)
	{
		perror("eval");
		exit(-1);
	}

	return 1;
}
