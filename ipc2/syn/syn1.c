#include "unpipc.h"
#include "my_err.h"
#include <pthread.h>
#define MAXITEMS 6
#define MAXTHREADS 3

int buffer[MAXITEMS];

struct shared
{
	pthread_mutex_t mutex;
	int input;//下标
	int i;//存入的值
}shared={PTHREAD_MUTEX_INITIALIZER};

struct ready
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int nready;//
	int nget;//
}ready={PTHREAD_MUTEX_INITIALIZER,PTHREAD_COND_INITIALIZER};

void *produce(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&shared.mutex);
		if(shared.i>=MAXITEMS)
		{
			pthread_mutex_unlock(&shared.mutex);
			return NULL;
		}

		buffer[shared.input]=shared.i;
		if(++shared.input>=MAXITEMS)//
			shared.input=0;

		//++shared.input;
		++shared.i;//值

		pthread_mutex_unlock(&shared.mutex);

		//使临界区尽量短使用多个互斥量
		pthread_mutex_lock(&ready.mutex);
		if(ready.nready==0)
			pthread_cond_signal(&ready.cond);
		++ready.nready;

		pthread_mutex_unlock(&ready.mutex);

	}
	return NULL;
}
			
void *consume(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&ready.mutex);

		if(ready.nready==0)
			pthread_cond_wait(&ready.cond,&ready.mutex);
		if(++ready.nget>=MAXITEMS)//1...MAXITEMS
		{
			if(ready.nget==MAXITEMS)
				printf("buffer[%d] = %d \n",ready.nget-1,buffer[(ready.nget-1)%MAXITEMS]);

			pthread_cond_signal(&ready.cond);//
			pthread_mutex_unlock(&ready.mutex);
			return NULL;
		}
		--ready.nready;
		pthread_mutex_unlock(&ready.mutex);

		printf("buffer[%d] = %d\n",ready.nget-1,buffer[(ready.nget-1)%MAXITEMS]);
	}
	return NULL;
}

int main()
{
	pthread_setconcurrency(MAXTHREADS*2);//
	
	int i;
	pthread_t pid_produce[MAXTHREADS],pid_consume[MAXTHREADS];
	for(i=0;i<MAXTHREADS;++i)
		pthread_create(&pid_produce[i],NULL,produce,NULL);
	
	for(i=0;i<MAXTHREADS;++i)
		pthread_create(&pid_consume[i],NULL,consume,NULL);
	
	for(i=0;i<MAXTHREADS;++i)
		pthread_join(pid_produce[i],NULL);

	for(i=0;i<MAXTHREADS;++i)
		pthread_join(pid_consume[i],NULL);

	exit(0);
}
