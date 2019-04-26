#include "fifo.h"

void client(int readfd,int writefd)
{
	char buffer[MAXLINE];
	fgets(buffer,MAXLINE,stdin);
	size_t len=strlen(buffer);
	if(buffer[len-1]=='\n')
		--len;

	//把路径名写入管道给server
	write(writefd,buffer,len);
	
	while((len=read(readfd,buffer,MAXLINE))>0)
		write(1,buffer,len);
}

