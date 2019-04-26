/*************************************************************************
    > File Name: db.h
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月25日 星期日 17时21分37秒
 ************************************************************************/

#ifndef DB_H
#define DB_H
#include <iostream>
#include <mysql/mysql.h>
#include <string>
using namespace std;

class Db
{
	private:
		MYSQL *con;
		MYSQL_RES *res;
		MYSQL_ROW row;

	public:
		Db();
		~Db();
		bool init_db(string host,string user,string pwd,string db_name);
		bool exec(string sql);
};

#endif
