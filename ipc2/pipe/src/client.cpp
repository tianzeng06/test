/*************************************************************************
    > File Name: client.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月13日 星期六 10时34分59秒
 ************************************************************************/

#include "client.h"

void client(int in,int out)
{
	string path;
	cin>>path;
	write(in,path.c_str(),path.size());

	size_t n=0;
	char buff[1024];
	while((n=read(out,buff,1024))>0)
		write(fileno(stdout),buff,n);

	return ;
}
