#pragma once
#include "../entity/User.hpp"
#include "SQLConnect.hpp"
class WriterManage
{
public:
    WriterManage(MYSQL* con):_con(con){}
    ~WriterManage(){};
    bool insert(const struct Writer& w);
    bool remove(int writerId);
    bool update(const struct Writer& w);
    //根据某个条件查找作者信息
    struct Writer searchByNickName(const string& nickName);
    struct Writer searchByUserNameAndPassword(const string& userName,const string& password);
    vector<struct Writer> searchAll();
private:
    MYSQL* _con;
};

//先插入到User表中，拿到新插入的id号，再插入到Writer表，一旦出错要回滚
bool WriterManage::insert(const struct Writer& w)
{
    //开始事务
    if(mysql_query(_con,"START TRANSCATION")){
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    char sql[1024];   
    sprintf(sql,"insert into User (role,nickName,userName,password,avatar,phone) values (%d,'%s','%s','%s','%s',%d)",
    w._role,w._nickName.c_str(),w._userName.c_str(),w._password.c_str(),w._avatar.c_str(),w._phone.c_str());
    //1 插入数据到User表中，出错，事务回滚
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        //回滚事务
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    //2 获取插入的User ID值
    MYSQL_RES* result = mysql_store_result(_con);
    if(result == 0)
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    int userId =atoi(row[0]);
    mysql_free_result(result);
    //3 插入到Writer 表
    sprintf(sql,"insert into Writer (writerId,manuscriptNumber)",userId,0);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        //回滚事务
        mysql_query(_con,"ROLLBACK");
        return false;        
    }
    cerr << "新增作者成功" << endl;
    return true;
}

//会先删除用户的所有稿件，再删除Writer表里对应用户，最后删除User表里对应用户
bool WriterManage::remove(int writerId)
{
    if(mysql_query(_con,"start transcation")){
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    char sql[1024];
    //1 先删除用户所有稿件
    snprintf(sql,sizeof(sql),"delete from Menuscript where writerId=%d",writerId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    //2 再删除Writer表里对应用户
    sprintf(sql,"delete from Writer where writerId=%d",writerId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    //3 最后删除User表里对应用户
    sprintf(sql,"delete from User where userId=%d",writerId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }

    cerr <<  mysql_error(_con) <<endl;
    return false;
}

//修改作者个人信息
//稿件数目在作者提交稿件后，触发器会自动++,不用管
bool WriterManage::update(const struct Writer& w)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"update User set nickName='%s',password='%s',avatar='%s',phone='%s' where userId=%d",
    w._nickName.c_str(),w._password.c_str(),w._avatar.c_str(),w._phone.c_str(),w._userId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    return true;
}

//从视图view_writerUser中查找所有用户信息
vector<struct Writer> WriterManage::searchAll()
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from view_writerUser");
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<struct Writer> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;//该结构体对象保存一行记录,其实就是个二级指针
    //row[0]对应这一行的id  row[1]对应这一行的nickName ..依次类推取决于表结构设计
    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Writer(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,int manuscriptNumber)
        int userId = atoi(row[0]);
        Role role = Role(atoi(row[1]));
        string nickName = row[2];
        string userName = row[3];
        string password = row[4];
        string avatar = row[5];
        string phone = row[6];
        int menuscriptNumber = atoi(row[7]);
        cerr << role << endl << endl;
        struct Writer w(userId,role,nickName,userName,password,avatar,phone,menuscriptNumber);
        //每一行的记录插入到vector中
        ret.push_back(w);
    }
    return ret;
}

//返回的作者信息，如果稿件数目为-1表示数据库查询异常或无该作者
struct Writer WriterManage::searchByNickName(const string& nickName)
{
    char sql[1024];
    struct Writer ret;
    snprintf(sql,sizeof(sql),"select * from view_writerUser where nickName='%s'",nickName.c_str());
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        ret._manuscriptNumber = -1;//查询出错
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
        int menuscriptNumber = atoi(row[7]);
        cerr << role << endl << endl;
        struct Writer w(userId,role,nickName,userName,password,avatar,phone,menuscriptNumber);
        return w;
    }
    ret._manuscriptNumber = -1;//作者不存在
    return ret;
}

//返回的作者信息，如果稿件数目为-1表示数据库查询异常或无该作者
struct Writer WriterManage::searchByUserNameAndPassword(const string& userName,const string& password)
{
    char sql[1024];
    struct Writer ret;
    snprintf(sql,sizeof(sql),"select * from view_writerUser where userName='%s' and password='%s'",userName.c_str(),password.c_str());
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        ret._manuscriptNumber = -1;//查询出错
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
        int menuscriptNumber = atoi(row[7]);
        cerr << role << endl << endl;
        struct Writer w(userId,role,nickName,userName,password,avatar,phone,menuscriptNumber);
        return w;
    }
    ret._manuscriptNumber = -1;//作者不存在
    return ret;
}
