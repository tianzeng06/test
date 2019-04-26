#include "unpipc.h"
#include "my_err.h"
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>

mqd_t mqd;
struct sigevent sigev;
struct mq_attr attr;
void *buff;

static void sig_usr1(int signo)
{
	ssize_t n;
	mq_notify(mqd,&sigev);
	n=mq_receive(mqd,buff,attr.mq_msgsize,NULL);
	printf("ISGUSR1 receievd read:%ld\n",(long)n);
	return ;
}

int main()
{
	printf("请输入要创建消息队列名:");

	char name[MAXLINE];
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	mqd=mq_open(name,O_RDONLY);
	if(mqd<0)
		{
			perror("open message queue error...\n");
			return -1;
		}
	
	/*sigset_t newmask;
	sigemptyset(&newmask);//清空当前信号集
	sigaddset(&newmask,SIGUSR1);//将SIGUSR1加入当前信号集
	sigprocmask(SIG_BLOCK,&newmask,NULL);//将当前信号集的状态设为阻塞
*/
	signal(SIGUSR1,sig_usr1);
	sigev.sigev_notify=SIGEV_SIGNAL;
	sigev.sigev_signo=SIGUSR1;
	mqd_t t=mq_notify(mqd,&sigev);//当前进程被注册为接收队列的通知
	if(t<0)
	{
		printf("%s\n",strerror(errno));
		exit(t);
	}

	mq_getattr(mqd,&attr);
	buff=(char *)malloc(sizeof(char)*attr.mq_msgsize);
	while(1)
	{
		pause();
	}
	exit(0);
}
