#pragma once
#include "../entity/Admin.hpp"
#include "UserManage.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
class AdminManage :public UserManage
{
public:
    AdminManage(){}
    ~AdminManage(){}
    struct Admin searchByUserName(const string& userName);
};
struct Admin AdminManage::searchByUserName(const string& userName)
{
    char sql[1024];
    struct Admin ret;
    snprintf(sql,sizeof(sql),"select * from User where userName='%s'",userName.c_str());
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        ret._flag =SearchFlag::SQLERROR;//查询出错
        return ret;
    }
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row = mysql_fetch_row(res))
    {
        int userId = atoi(row[0]);
        Role role = Role(atoi(row[1]));
        string nickName = row[2];
        string userName = row[3];
        string password = row[4];
        string avatar = row[5];
        string phone = row[6];
        struct Admin admin(userId,role,nickName,userName,password,avatar,phone);
        return admin;
    }
    ret._flag = SearchFlag::NONE;//作者不存在
    return ret;
}
