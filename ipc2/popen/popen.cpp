/*************************************************************************
    > File Name: popen.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月13日 星期六 15时05分46秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <error.h>
#include <string.h>
using namespace std;

int main()
{
	string cmd;
	cin>>cmd;

	string t("cat ");
	cmd=t.append(cmd);
	FILE *fp=popen(cmd.c_str(),"r");
	if(fp==nullptr)
	{
		cerr<<strerror(errno)<<endl;
		return 0;
	}
	else
	{
		char buff[1024];
		while(fgets(buff,1024,fp)!=nullptr)
			fputs(buff,stdout);
	}
	return 0;
}
