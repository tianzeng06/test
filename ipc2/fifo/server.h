#include "fifo.h"
#include "my_err.h"

void server(int readfd,int writefd)
{
	char buffer[MAXLINE],pathname[MAXLINE];
	size_t n;
	if((n=read(readfd,pathname,MAXLINE))==0)
		err_quit("end-of-file while read pathname");
	buffer[n]='\0';

	int fd=open(pathname,O_RDONLY);
	if(fd<0)
	{
		snprintf(pathname+n,sizeof(pathname)-n,":can't open ,%s",pathname);
		n=strlen(pathname);
		write(writefd,pathname,n);
	}
	else
	{
		while((n=read(fd,buffer,MAXLINE))>0)
			write(writefd,buffer,n);
		//close(fd);
	}
	close(fd);
}
