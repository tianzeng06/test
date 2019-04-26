#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd=open("1.txt",O_RDWR|O_CREAT,0666);
	if(fd<0)
	{
		perror("打开文件失败\n");
		exit(0);
	}

	int i=0;
	for(;i<10;++i)
		write(fd,"a",1);

	struct flock lock;
	lock.l_type=F_RDLCK;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=3;

	struct flock lock1;
	lock1.l_type=F_RDLCK;
	lock1.l_whence=SEEK_SET;
	lock1.l_start=0;
	lock1.l_len=3;

	int res=fcntl(fd,F_SETLK,&lock);
	if(res==-1)
		fprintf(stderr,"Failed to lock\n");

	res=fcntl(fd,F_SETLK,&lock1);
	if(res==-1)
		fprintf(stderr,"Failed to lock1\n");
	
	close(fd);
	exit(0);
}
