#include "unpipc.h"
#include <mqueue.h>

int main()
{
	printf("请输入消息队列的名字:");
	char name[MAXLINE];
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	int flags=O_WRONLY;
	mqd_t mqd=mq_open(name,flags,FILE_MODE,NULL);
	if(mqd<0)
	{
		if(errno==EEXIST)
		{
			mq_unlink(name);
			mqd=mq_open(name,O_RDWR|O_CREAT,FILE_MODE,NULL);
		}
		else
		{
			printf("open message queue error...\n");
			return -1;
		}
	}
	struct mq_attr attr;
	mq_getattr(mqd,&attr);
	char msg[MAXLINE];

	int i;
	for(i=0;i<6;++i)
	{
		printf("请输入第 %d 个消息:",i+1);
		scanf("%s",msg);
		printf("请输入第 %d 个消息的优先级:",i+1);
		int prio;
		scanf("%d",&prio);

		if(mq_send(mqd,msg,sizeof(msg),prio)<0)
			printf("send message: %d faild.error info: %s\n",i,strerror(errno));
		
		printf("send message: %d success.\n",i+1);

		//sleep(1);
	}
	exit(0);
}
