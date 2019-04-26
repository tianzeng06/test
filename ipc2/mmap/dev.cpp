/*************************************************************************
    > File Name: dev.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月16日 星期二 21时40分03秒
 ************************************************************************/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
using namespace std;

int main()
{
	int fd=open("dev/zero",O_RDWR);
	int *ptr=(int *)mmap(nullptr,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	close(fd);
	return 0;
}
