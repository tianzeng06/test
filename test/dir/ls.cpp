/*************************************************************************
    > File Name: ls.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月07日 星期四 11时16分12秒
 ************************************************************************/

#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

void ls_dirent(char *s)
{
	DIR *dir;
	struct dirent *d;
	struct stat stats;

	if((dir=opendir(s))==NULL)
	{
		cout<<s<<endl;
		return;
	}
	
	chdir(s);
	while((d=readdir(dir))!=NULL)
	{
		lstat(d->d_name,&stats);
		
		if(S_ISDIR(stats.st_mode))
		{
			if(strcmp(d->d_name,".")==0||strcmp(d->d_name,"..")==0)
				continue;
			else
			{
				char str[100];
				memset(str,'\0',sizeof(str));
				strcpy(str,s);
				strcat(str,"/");
				strcat(str,d->d_name);
				ls_dirent(str);
			}
		}
		else
		{
			char dircwd[100];
			memset(dircwd,'\0',100);
			strcpy(dircwd,s);
			strcat(dircwd,"/");
			strcat(dircwd,d->d_name);
			cout<<dircwd<<endl;
		}
	}
	chdir("..");
	closedir(dir);
	return ;
}
int main(int argc,char **argv)
{
	char s[100];
	cin>>s;
	ls_dirent(s);
	return 0;
}
