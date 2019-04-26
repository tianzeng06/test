/*************************************************************************
    > File Name: test.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2019年04月15日 星期一 10时48分16秒
 ************************************************************************/

#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	cout<<sysconf(_SC_SEM_NSEMS_MAX)<<" "<<sysconf(_SC_SEM_VALUE_MAX)<<endl;
	return 0;
}
