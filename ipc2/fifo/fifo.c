#include "client.h"
#include "server.h"

int main()
{
	if((mkfifo(FIFO1,FILE_MODE)<0)&&(errno!=EEXIST))
		err_sys("can't create %s",FIFO1);
	if((mkfifo(FIFO2,FILE_MODE)<0)&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		err_sys("can't create %s",FIFO2);
	}

	pid_t cpid;
	int readfd,writefd;
	if((cpid=fork())==0)
	{
		readfd=open(FIFO1,O_RDONLY);
		writefd=open(FIFO2,O_WRONLY);

		server(readfd,writefd);
		exit(0);
	}
	
	//副子进程都打开读，没有进程打开写，fifo进程打开读阻塞，死锁
	//readfd=open(FIFO2,O_RDONLY,0);
	writefd=open(FIFO1,O_WRONLY);
	readfd=open(FIFO2,O_RDONLY);

	client(readfd,writefd);

	waitpid(cpid,NULL,0);//等待子进程结束
	close(readfd);
	close(writefd);

	unlink(FIFO1);
	unlink(FIFO2);
	exit(0);
}
