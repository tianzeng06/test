/*************************************************************************
    > File Name: mmap.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月16日 星期二 16时53分40秒
 ************************************************************************/

#include <iostream>
#include <sys/mman.h>
#include <sys/types.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <error.h>

using namespace std;

typedef struct Shared
{
	int count;
	sem_t sem;
}Shared;
const int loop=10;
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc,char **argv)
{
	Shared s;
	int fd=open("1.txt",O_RDWR|O_CREAT,FILE_MODE);
	write(fd,&s,sizeof(Shared));
	//子父进程都有自己的ptr副本，每个副本都指向共享内存区域的一个整数
	Shared *ptr=(Shared *)mmap(nullptr,sizeof(Shared),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(ptr==MAP_FAILED)
	{
		cerr<<strerror(errno)<<endl;
		exit(1);
	}
	close(fd);
	
	//此时信号量在共享内存中
	int res=sem_init(&ptr->sem,1,1);
	if(res==-1)
	{
		cerr<<strerror(errno)<<endl;
		exit(1);
	}

	//取消缓冲
	setbuf(stdout,nullptr);
	if((fork()==0))//子进程
	{
		cout<<"child: "<<getpid()<<" "<<getppid()<<endl;
		for(int i=0;i<loop;++i)
		{
			sem_wait(&ptr->sem);
			cout<<(*ptr).count++<<endl;
			sem_post(&ptr->sem);
		}
		exit(0);
	}

	cout<<"parent :"<<getpid()<<" "<<getppid()<<endl;
	for(int i=0;i<loop;++i)
	{
		sem_wait(&ptr->sem);
		cout<<(*ptr).count++<<endl;
		sem_post(&ptr->sem);
	}
	exit(0);
}
