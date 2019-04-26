#include "unpipc.h"
#include "my_err.h"
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
volatile sig_atomic_t flag;
static void sig_usr1(int signo)
{
	flag=1;
	return;
}

int main()
{
	printf("请输入要创建消息队列名:");

	char name[MAXLINE];
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	mqd_t mqd=mq_open(name,O_RDONLY);
	if(mqd<0)
	{
		perror(strerror(errno));
		return -1;
	}
	
	sigset_t newmask,zeromask,oldmask;
	sigemptyset(&newmask);//清空当前信号集
	sigemptyset(&zeromask);
	sigemptyset(&oldmask);
	sigaddset(&newmask,SIGUSR1);//将SIGUSR1加入当前信号集

	signal(SIGUSR1,sig_usr1);
	struct sigevent sigev;
	sigev.sigev_notify=SIGEV_SIGNAL;
	sigev.sigev_signo=SIGUSR1;
	mqd_t t=mq_notify(mqd,&sigev);//当前进程被注册为接收队列的通知
	if(t<0)
	{
		perror(strerror(errno));
		return t;
	}
	struct mq_attr attr;
	mq_getattr(mqd,&attr);
	char *buffer=(char *)malloc(sizeof(char)*attr.mq_msgsize);
	while(1)
	{
		//no signal block
		sigprocmask(SIG_BLOCK,&newmask,&oldmask);
		while(flag==0)
			sigsuspend(&zeromask);
		flag=0;

		mq_notify(mqd,&sigev);
		ssize_t n=mq_receive(mqd,buffer,attr.mq_msgsize,NULL);
		printf("read %ld",(long)n);
		fflush(stdout);
		//ublock usr1
		sigprocmask(SIG_UNBLOCK,&newmask,NULL);
	}
	exit(0);
}
