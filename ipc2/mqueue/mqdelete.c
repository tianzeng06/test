#include "unpipc.h"
#include <mqueue.h>

int main()
{
	char name[MAXLINE];
	printf("请输入要删除队列的名字: %s",name);
	fgets(name,MAXLINE,stdin);
	int len=strlen(name);
	if(name[len-1]=='\n')
		name[len-1]='\0';
	mqd_t mqd=mq_open(name,O_RDONLY);

	if(mq_close(mqd)<0)
		printf("关闭消息队列失败.\n");
	if(mq_unlink(name)<0)
		printf("删除消息队列失败.\n");

	exit(0);
}
