/*************************************************************************
    > File Name: main.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月25日 星期日 17时39分06秒
 ************************************************************************/

#include "db.h"
using namespace std;

int main()
{
	Db db;
	db.init_db("localhost","root","root","stu");
	db.exec("select * from stu_info");
	//db.exec("insert into stu_info values('000002','hualian','21','1005',100)");
	return 0;
}
