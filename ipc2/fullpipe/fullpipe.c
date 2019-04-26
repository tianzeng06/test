#include "unpipc.h"
#include "my_err.h"

int main()
{
	int fd[2];
	//pipe(fd);
	socketpair(AF_UNIX,SOCK_DGRAM,0,fd);

	char c;
	size_t n;
	pid_t cpid;
	if((cpid=fork())==0)
	{
		sleep(3);//让父进程的read调用优先于子进程的，测试父进程是否读入刚写入的字符
		if((n=read(fd[0],&c,1))<0)
			err_quit("child:read return %d\n",n);

		printf("child read %c\n",c);
		write(fd[0],"c",1);
		close(fd[0]);
		exit(0);
	}

	write(fd[1],"p",1);
	if((n=read(fd[1],&c,1))!=1)
		err_quit("parent:read return %d\n",n);

	printf("parent read %c\n",c);
	close(fd[1]);
	exit(0);
}
