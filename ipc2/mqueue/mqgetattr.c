#include "unpipc.h"
#include <mqueue.h>

int main(int argc,char *argv[])
{
	mqd_t mqd=mq_open(argv[1],O_RDONLY);

	struct mq_attr attr;
	mq_getattr(mqd,&attr);
	printf("max #msg=%ld ,max #bytes/msg=%ld, #curenctly on queue =%ld\n",attr.mq_maxmsg,attr.mq_msgsize,attr.mq_curmsgs);

	mq_close(mqd);
}
