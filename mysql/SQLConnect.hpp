#ifndef SQLCONNECT_HPP
#define SQLCONNECT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class SQLConnect
{
private:
    MYSQL *_con;
public:
    SQLConnect()
    {
        // 0 初始化数据库对象  获取一个用于连接数据库的结构体对象,包含数据库的各种属性信息，连接到数据库后会填充里面的属性
        MYSQL *msql = mysql_init(nullptr); // 默认用拉丁的编码
        if (msql == nullptr)
        {
            cerr << mysql_error(_con) << endl;
            exit(1);
        }
        cerr << "初始化数据库对象成功" << endl;

        // 1 登录数据库
        // MYSQL* mysql_real_connect(MYSQL* mysql, const char* host,const char* user
        //                          const char* passwd,const char*db,unsigned int port,const char* unix_socket, unsigned long clientflag);
        // host:数据库的ip地址  user:连哪个用户  passwd:密码  db:连接哪一个数据库名字  port:端口号  unix_socket:本地连接还是远端，设为nullptr  clientflag:0
        const char *user = "root";
        const char *password = "MYSQL363656690qQ";
        const char *mysqlIp = "127.0.0.1";
        const int serverPort = 3306;
        const char *dbName = "OnlineSubmissionSystem";
        if (mysql_real_connect(msql, mysqlIp, user, password, dbName, serverPort, nullptr, 0) == nullptr)
        {
            cerr << "连接数据库失败" << endl;
            exit(2);
        }
        cerr << "连接数据库成功" << endl;
        // 设置编码为utf8
        mysql_set_character_set(msql, "utf8");
    }
    ~SQLConnect()
    {
        // 关闭数据库连接
        mysql_close(_con);
    }
    // 获取MYSQL数据库对象
    MYSQL *GetMYSQLObject()
    {
        return _con;
    }
};
#endif