/*************************************************************************
    > File Name: db.cpp
    > Author: Chen Tianzeng
    > Mail: 971859774@qq.com 
    > Created Time: 2018年11月25日 星期日 17时25分04秒
 ************************************************************************/

#include "db.h"
using namespace std;

Db::Db()
{
	con=mysql_init(NULL);//初始化链接变量
	if(con==NULL)
	{
		cerr<<"error: "<<mysql_error(con)<<endl;
		exit(1);
	}
}

Db::~Db()
{
	if(con)
		mysql_close(con);
}

bool Db::init_db(string host,string user,string pwd,string db_name)
{
	//用mysql_real_connect建立一个连接
	con=mysql_real_connect(con,host.c_str(),user.c_str(),pwd.c_str(),
								db_name.c_str(),0,NULL,0);
	if(con==NULL)
	{
		cerr<<"error: "<<mysql_error(con)<<endl;
		exit(1);
	}
	return true;
}

bool Db::exec(string sql)
{
	//执行sql查询语句,成功返回0，失败返回非0
	if(mysql_query(con,sql.c_str()))
	{
		cerr<<"query error: "<<mysql_error(con)<<endl;
		exit(1);
	}
	else
	{
		//获取查询的结果
		res=mysql_store_result(con);
		if(res)
		{
			//返回查询的列数
			for(int i=0;i<mysql_num_rows(res);++i)
			{
				row=mysql_fetch_row(res);
				if(row<0)
					break;

				//结果集中的字段数
				for(int j=0;j<mysql_num_fields(res);++j)
					cout<<row[j]<<" ";
				cout<<endl;
			}
		}
		else//res==NULL
		{
			if(mysql_field_count(con)==0)
				int num_rows=mysql_affected_rows(con);
			else
			{
				cout<<"get result error: "<<mysql_error(con)<<endl;
				return false;
			}
		}
	}
	//释放结果集
	mysql_free_result(res);
	return true;
}
