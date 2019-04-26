#include "server.h"

int main()
{
	if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
		err_quit("can't create %s",FIFO1);
	if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		err_quit("can't create %s",FIFO2);
	}

	int readfd=open(FIFO1,O_RDONLY);
	int writefd=open(FIFO2,O_WRONLY);

	server(readfd,writefd);

	close(readfd);
	close(writefd);

	exit(0);
}
