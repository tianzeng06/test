#include "fifo.h"
#include "my_err.h"

void server(int readfd,int writefd)
{
	char buffer[MAXLINE];
	size_t n;

	if((n=read(readfd,buffer,MAXLINE))==0)
		err_quit("file-end-of while reading pathname");
	buffer[n]='\0';

	int fd=open(buffer,O_RDONLY);
	if(fd<0)
	{
		snprintf(buffer+n,sizeof(buffer)-n,":can't open %s\n",strerror(errno));
	}
	else
	{
		while((n=read(fd,buffer,MAXLINE))>0)
			write(writefd,buffer,n);
	}
	close(fd);
}


