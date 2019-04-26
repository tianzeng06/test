/*************************************************************************
    > File Name: server.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月23日 星期五 19时34分29秒
 ************************************************************************/

#include "epollserver.h"
#define INDARRY_PORT 9877

using namespace std;

int main(int argc,char **argv)
{
	Epollserver *epoll=new Epollserver(INDARRY_PORT,20);
	epoll->init();
	epoll->epoll();
	return 0;
}
