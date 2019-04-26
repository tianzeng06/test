#include "unpipc.h"
#include "my_err.h"
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	printf("请输入要创建消息队列名:");

	char name[MAXLINE];
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	mqd_t mqd=mq_open(name,O_RDONLY|O_NONBLOCK);
	if(mqd<0)
		{
			perror("open message queue error...\n");
			return -1;
		}
	
	sigset_t newmask;
	sigemptyset(&newmask);//清空当前信号集
	sigaddset(&newmask,SIGUSR1);//将SIGUSR1加入当前信号集
	sigprocmask(SIG_BLOCK,&newmask,NULL);//将当前信号集的状态设为阻塞

	struct sigevent sigev;
	sigev.sigev_notify=SIGEV_SIGNAL;
	sigev.sigev_signo=SIGUSR1;
	mq_notify(mqd,&sigev);//当前进程被注册为接收队列的通知

	int signo;
	struct mq_attr attr;
	mq_getattr(mqd,&attr);
	char *buffer=(char *)malloc(sizeof(char)*attr.mq_msgsize);
	while(1)
	{
		sigwait(&newmask,&signo);//把阻塞信号从挂起信号集中删除，解除阻塞，所检测的进程必须是阻塞处理的
		if(signo==SIGUSR1)
		{
			mq_notify(mqd,&sigev);//通知被发送给注册进程时，注册即被撤销，需再次注册

			int n=mq_receive(mqd,buffer,attr.mq_msgsize,NULL);
			if(n>0)
				printf("receive mesage is: %s\n",buffer);
			
			if(n<0)
			{
				if(errno==EAGAIN)
					continue;
			}
		}
	}
	exit(0);
}
