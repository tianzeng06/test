/*************************************************************************
    > File Name: main.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年03月29日 星期五 20时57分00秒
 ************************************************************************/

#include "threadpool.h"

void fun(void *arg)
{
	cout<<"handle is :"<<*(int *)arg<<endl;
	return ;
}

int main()
{
	ThreadPool tp(6);
	int res=tp.initializer();
	if(res<0)
	{
		cerr<<"threadpool initializer error"<<endl;
		return 0;
	}
	for(int i=1;i<=10;++i)
	{
		int *x=new int();
		*x=i;
		Task *t=new Task{&fun,(void *)x};
		//cout<<t<<endl;
		tp.add_task(t);
	}
	return 0;
}
