#include "client.h"

int main()
{
	int writefd=open(FIFO1,O_WRONLY);
	int readfd=open(FIFO2,O_RDONLY);

	client(readfd,writefd);

	close(readfd);
	close(writefd);

	unlink(FIFO1);
	unlink(FIFO2);
	exit(0);
}
