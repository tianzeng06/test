#include "unpipc.h"
#include <pthread.h>
#include <string.h>

#define BUFF 10

struct shared
{
	struct buff
	{
		char data[BUFFSIZE];
		size_t n;
	}buffer[BUFF];
	sem_t mutex,nempty,nstored;
}shared;

int fd;

void *produce(void *arg)
{
	//printf("thread produce is: %d\n",fd);
	int i=0;
	while(1)
	{
		sem_wait(&shared.nempty);

		sem_wait(&shared.mutex);
		//如果数据缓冲区要是在一个连表上维护，此处是链表中移除某个缓冲区的
		//地方，把该操作放在临界区是避免生产者消费者对链表操作发生冲突
		sem_post(&shared.mutex);

		shared.buffer[i].n=read(fd,shared.buffer[i].data,BUFFSIZE);
		if(shared.buffer[i].n==0)//读取结束
		{
			sem_post(&shared.nstored);
			return NULL;
		}

		if(++i>=BUFF)
			i=0;//循环缓冲

		sem_post(&shared.nstored);
	}
	return NULL;
}

void *consume(void *arg)
{
	//printf("thread consume is: %d\n",fd);
	int i=0;
	while(1)
	{
		sem_wait(&shared.nstored);

		sem_wait(&shared.mutex);
		//同上
		sem_post(&shared.mutex);

		if(shared.buffer[i].n==0)
			return NULL;

		write(1,shared.buffer[i].data,shared.buffer[i].n);
		if(++i>BUFF)
			i=0;

		sem_post(&shared.nempty);
	}
	return NULL;
}

int main()
{
	printf("请输入文件名\n");
	char pathname[100];
	fgets(pathname,100,stdin);
	int len=strlen(pathname);
	if(pathname[len-1]=='\n')
		pathname[len-1]='\0';
	fd=open(pathname,O_RDONLY);
	//printf("pathname:%s",pathname);
	//printf("fd is main: %d\n",fd);

	sem_init(&shared.mutex,0,1);
	sem_init(&shared.nempty,0,BUFF);
	sem_init(&shared.nstored,0,0);

	pthread_setconcurrency(2);

	pthread_t pid_produce,pid_consume;
	//printf("thread is starting..\n");
	pthread_create(&pid_consume,NULL,consume,NULL);
	pthread_create(&pid_produce,NULL,produce,NULL);
	//pthread_create(&pid_consume,NULL,consume,NULL);

	pthread_join(pid_produce,NULL);
	pthread_join(pid_consume,NULL);

	sem_destroy(&shared.mutex);
	sem_destroy(&shared.nempty);
	sem_destroy(&shared.nstored);

	exit(0);
}
