#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_rwlock_t rwlock=PTHREAD_RWLOCK_INITIALIZER;
pthread_t pid1,pid2;

void *thread1(void *arg)
{
	pthread_rwlock_rdlock(&rwlock);
	printf("thread1 got a read lock\n");
	sleep(3);
	pthread_cancel(pid2);
	sleep(3);

	pthread_rwlock_unlock(&rwlock);
	return NULL;
}

void *thread2(void *arg)
{
	printf("thread2 trying to obtain a write lock\n");
	pthread_rwlock_wrlock(&rwlock);
	printf("thread2 got a write lock\n");

	sleep(1);
	pthread_rwlock_unlock(&rwlock);
	printf("thread2 exiting...\n");
	return NULL;
}

int main()
{
#ifdef __USE_UNIX98
	pthread_setconcurrency(2);	
#endif
	pthread_create(&pid1,NULL,thread1,NULL);
	sleep(1);
	pthread_create(&pid2,NULL,thread2,NULL);

	void *status;
	pthread_join(pid2,&status);
	if(status!=PTHREAD_CANCELED)
		printf("thread2 status= %p\n",status);

	pthread_join(pid1,&status);
	if(status!=PTHREAD_CANCELED)
		printf("thread1 status= %p\n",status);

	/*printf("rw_refcount= %d, rw_nwaitreaders= %d, rw_nwaitwrites= %d\n",rwlock.rw_refcount,rwlock.rw_nwaitreaders,rwlock.rw_nwaitwriters);*/

	pthread_rwlock_destroy(&rwlock);
	exit(0);
}
