/*************************************************************************
    > File Name: mmap3.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月17日 星期三 17时21分31秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
using namespace std;

const int SIZE=32768;
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IRGRP)
int main()
{
	/*
	 * 指定一个大于该文件大小的内存映射区，内核跟踪着被映射的底层对象大小
	 * 以确保不访问当前文件尾以及更远的部分，然后就让该文件大小随着往其每
	 * 次写入数据而增长
	 */
	int fd=open("1.txt",O_RDWR|O_CREAT|O_TRUNC,FILE_MODE);
	char *ptr=(char *)mmap(nullptr,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	
	for(int i=4096;i<=SIZE;i+=4096)
	{
		cout<<"seting file sizs: "<<i<<endl;
		ftruncate(fd,i);
		cout<<"ptr["<<i<<"]="<<ptr[i-1]<<endl;
	}
	return 0;
}
