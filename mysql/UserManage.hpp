#pragma once
#include "../entity/User.hpp"
#include "SQLConnect.hpp"
class UserManage
{
public:
    UserManage()
    :_con(sqlConnect.GetMYSQLObject())
    {}
    virtual ~UserManage(){}
    virtual bool updateBase(const User& u);//修改个人基本信息
    virtual User searchByUserNameAndPassword(const string& userName,const string& password);//用于登录，只有审核员需要重写实现
protected:
    MYSQL* _con;
};
bool UserManage::updateBase(const User& u)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"update User set nickName='%s',password='%s',avatar='%s',phone='%s' where userId=%d",
                            u._nickName.c_str(),u._password.c_str(),u._avatar.c_str(),u._phone.c_str(),u._userId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    return true;
}
User UserManage::searchByUserNameAndPassword(const string& userName,const string& password)
{
    char sql[1024];
    struct User ret;
    snprintf(sql,sizeof(sql),"select * from User where userName='%s' and password='%s'",userName.c_str(),password.c_str());
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        ret._flag = SearchFlag::SQLERROR;//查询出错
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
        //User(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone)
        struct User user(userId,role,nickName,userName,password,avatar,phone);
        return user;
    }
    ret._flag = SearchFlag::NONE;//用户不存在
    return ret;
}