/*************************************************************************
    > File Name: pipe.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月13日 星期六 10时24分00秒
 ************************************************************************/

#include "client.h"
#include "server.h"

int main()
{
	int  p1[2],p2[2];
	pipe(p1);
	pipe(p2);

	pid_t pid;
	if((pid=fork())==0)
	{
		//子进程从p1读，写入p2
		close(p1[1]);
		close(p2[0]);
		
		server(p1[0],p2[1]);
		exit(0);
	}
	
	close(p1[0]);
	close(p2[1]);
	client(p1[1],p2[0]);

	waitpid(pid,nullptr,0);
	return 0;
}
