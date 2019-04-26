/*************************************************************************
    > File Name: anon.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月16日 星期二 20时19分50秒
 ************************************************************************/

#include <iostream>
#include <sys/mman.h>
#include <unistd.h>//fork
#include <fcntl.h>//O_RDWR
#include <semaphore.h>
#include <string.h>//strerror
#include <error.h>
using namespace std;

string name("/tmp2");
const int loop=10;
int main()
{
	sem_t *sem=sem_open(name.c_str(),O_CREAT|O_EXCL,1);
	if(sem==SEM_FAILED)
	{
		cerr<<strerror(errno)<<endl;
		exit(1);
	}
	
	//内存区初始化为0
	int *ptr=(int *)mmap(nullptr,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
	if(ptr==MAP_FAILED)
	{
		cerr<<strerror(errno)<<endl;
		exit(1);
	}
	
	if(fork()==0)
	{
		cout<<"child: "<<getpid()<<" "<<getppid()<<endl;
		for(int i=0;i<loop;++i)
		{
			sem_wait(sem);
			cout<<(*ptr)++<<endl;
			sem_post(sem);
		}
		sem_unlink(name.c_str());
		sem_close(sem);
		exit(0);//不显示的调用
	}

	cout<<"parent: "<<getpid()<<" "<<getppid()<<endl;
	for(int i=0;i<loop;++i)
	{
		sem_wait(sem);
		cout<<(*ptr)++<<endl;
		sem_post(sem);
	}
	
	sem_unlink(name.c_str());
	sem_close(sem);
	munmap(ptr,sizeof(int));
	exit(0);
}
