#include "unpipc.h"
#include <mqueue.h>

int main()
{
	int flags=O_RDWR|O_CREAT;
	printf("请输入要创建的消息队列名称:");
	char name[MAXLINE];
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';

	mqd_t mqd=mq_open(name,flags,FILE_MODE,NULL);

	mq_close(mqd);
	//mq_unlink(name);
	exit(0);
}

