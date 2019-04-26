#include "unpipc.h"
#include <mqueue.h>

int main()
{
	char name[MAXLINE];
	printf("请输入要接受消息队列的名字:");
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	mqd_t mqd=mq_open(name,O_RDONLY);

	struct mq_attr attr;
	mq_getattr(mqd,&attr);
	char *buffer=(char *)malloc(sizeof(char)*attr.mq_msgsize);

	int i;
	for(int i=0;i<6;++i)
	{
		int prio;
		if(mq_receive(mqd,buffer,attr.mq_msgsize,&prio)<0)
		{
			printf("receive message failed. error info: %s\n",strerror(errno));
			continue;
		}
		printf("receive message %d: %s, prio is: %d\n",i+1,buffer,prio);
	}
	mq_close(mqd);
	exit(0);
}
