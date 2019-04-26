/*************************************************************************
    > File Name: server.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月13日 星期六 10时35分48秒
 ************************************************************************/

#include "server.h"

void server(int in,int out)
{
	char path[024];
	size_t n=0;
	if((n=read(in,path,1024))==0)
	{
		cerr<<"end-of_file while read pathname"<<endl;
		exit(1);
	}

	path[n]='\0';
	int fd=open(path,O_RDONLY);
	if(fd<0)
	{
		stringstream ss;
		string s1(" can't open");
		string p(path);
		p.append(s1);
		ss<<strerror(errno);
		string s2;
		ss>>s2;
		p.append(" ").append(s2);
		write(out,p.c_str(),p.size());
	}
	else
	{
		char buff[1024];
		while((n=read(fd,buff,1024))>0)
			write(out,buff,n);
	}
	return ;
}
