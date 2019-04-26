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

string name("/tmp");
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
const int loop=10;

int main(int argc,char **argv)
{
	//信号量在内核中
	sem_t *sem=sem_open(name.c_str(),O_CREAT|O_EXCL,FILE_MODE,1);
	if(sem==SEM_FAILED)
	{
		cerr<<strerror(errno)<<endl;
		exit(-1);
	}
	sem_unlink(name.c_str());
	//int value;
	//sem_getvalue(sem,&value);
	//cout<<value<<endl;
	
	int fd=open("1.txt",O_RDWR|O_CREAT,FILE_MODE);
	int zero=0;
	write(fd,&zero,sizeof(int));
	//子父进程都有自己的ptr副本，每个副本都指向共享内存区域的一个整数
	int *ptr=(int *)mmap(nullptr,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(ptr==MAP_FAILED)
	{
		cerr<<strerror(errno)<<endl;
		exit(1);
	}
	//close(fd);

	setbuf(stdout,nullptr);
	if((fork()==0))//子进程
	{
		cout<<"child: "<<getpid()<<" "<<getppid()<<endl;
		for(int i=0;i<loop;++i)
		{
			sem_wait(sem);
			cout<<(*ptr)++<<endl;
			sem_post(sem);
		}
		exit(0);
	}

	cout<<"parent :"<<getpid()<<" "<<getppid()<<endl;
	for(int i=0;i<loop;++i)
	{
		sem_wait(sem);
		cout<<(*ptr)++<<endl;
		sem_post(sem);
	}

	int res=0;
	read(fd,&res,sizeof(int));
	cout<<"res :"<<res<<endl;
	close(fd);
	exit(0);
}
