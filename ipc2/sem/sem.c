#include "unpipc.h"

#define BUFF 10
#define SEM_MUTEX "/tmpmutex"
#define SEM_NEMPTY "/tmpnempty"
#define SEM_NSTORED "/tmpnstored"

struct shared
{
	int buffer[BUFF];
	sem_t *mutex,*nempty,*nstored;
}shared;

void *produce(void *arg)
{
	int i;
	for(i=0;i<BUFF;++i)
	{
		sem_wait(shared.nempty);
		sem_wait(shared.mutex);

		shared.buffer[i%BUFF]=i;

		sem_post(shared.mutex);
		sem_post(shared.nstored);
	}
	return NULL;
}

void *consume(void *arg)
{
	int i=0;
	for(i=0;i<BUFF;++i)
	{
		sem_wait(shared.nstored);//这两个wait交换会造成死锁
		sem_wait(shared.mutex);

		printf("shared.buffer[%d]= %d\n",i,shared.buffer[i%BUFF]);

		sem_post(shared.mutex);
		sem_post(shared.nempty);
	}
	return NULL;
}

int main()
{
	pthread_setconcurrency(2);
	pthread_t pid_consume,pid_produce;

	/*每个信号量都需要正确的初始化，如果先前建立的信号里因本程序终止没有
	 * 删除，那么，可以在sem_open之前调用sem_unlink，并忽略任何错误，也
	 * 可以指定O_EXCL，检查是否返回EEXIST错误，若是，调用sem_unlink，并
	 * 且再次调用sem_open。如果想验证本程序只有一个副本在运行，可以调用
	 * fcntl文件锁
	 */
	shared.mutex=sem_open(SEM_MUTEX,O_CREAT|O_EXCL,FILE_MODE,1);
	shared.nempty=sem_open(SEM_NEMPTY,O_CREAT|O_EXCL,FILE_MODE,BUFF);
	shared.nstored=sem_open(SEM_NSTORED,O_CREAT|O_EXCL,FILE_MODE,BUFF);

	pthread_create(&pid_produce,NULL,produce,NULL);
	pthread_create(&pid_consume,NULL,consume,NULL);

	pthread_join(pid_produce,NULL);
	pthread_join(pid_consume,NULL);

	sem_unlink(SEM_MUTEX);
	sem_unlink(SEM_NEMPTY);
	sem_unlink(SEM_NSTORED);

	exit(0);
}

