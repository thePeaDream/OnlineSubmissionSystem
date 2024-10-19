#pragma once
#include "../entity/Assessor.hpp"
#include "./UserManage.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
class AssessorManage : public UserManage
{
public:
    AssessorManage(){}
    ~AssessorManage(){}
    bool insert(const string& nickName,const string& userName,const string& password,
    const string& avatar,const string& phone,const string& description,int categoryId);
    bool remove(int assessorId);
    bool updateAssessorStatus(int assessorId);
    virtual User searchByUserNameAndPassword(const string& userName,const string& password);//重写虚函数实现，审核员必须被批准成为审核员，才能登录
    struct Assessor searchByAssessorId(int assessorId);
    vector<struct Assessor> searchAll();
    vector<struct Assessor> searchByStatus(AssessorStatus status);
};
//先插入到User表中，拿到新插入的id号，再插入到Assessor表，一旦出错要回滚
//默认新插入的审核员，都是要被管理员审批的
bool AssessorManage::insert(const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,const string& description,int categoryId)
{
    //开始事务
    if(mysql_query(_con,"START TRANSCATION")){
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    char sql[1024];   
    sprintf(sql,"insert into User (role,nickName,userName,password,avatar,phone) values (%d,'%s','%s','%s','%s',%d)",
    Role::Assessor,nickName.c_str(),userName.c_str(),password.c_str(),avatar.c_str(),phone.c_str());
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
    int assessorId =atoi(row[0]);
    //mysql_free_result(result);
    //3 插入到Assessor表
    sprintf(sql,"insert into Assessor (assessorId,applicationTime,description,status,categoryId,pendingAudit) values(%d,now(),'%s','Pending',%d,0)",
                                       assessorId,description,categoryId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        //回滚事务
        mysql_query(_con,"ROLLBACK");
        return false;        
    }
    return true;
}

//1 先将该审核员对应的所有稿件，assessorId全部置null
//2 再删除Assessor表里对应审核员
//3 最后删除User表里对应用户
bool AssessorManage::remove(int assessorId)
{
    if(mysql_query(_con,"start transcation")){
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    char sql[1024];
    //1 先将该审核员对应的所有稿件，assessorId全部置null
    snprintf(sql,sizeof(sql),"update Manuscript set assessorId=null where assessorId=%d",assessorId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    //2 再删除Assessor表里对应审核员
    sprintf(sql,"delete from Assessor where assessorId=%d",assessorId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    //3 最后删除User表里对应用户
    sprintf(sql,"delete from User where userId=%d",assessorId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        mysql_query(_con,"ROLLBACK");
        return false;
    }
    cerr <<  mysql_error(_con) <<endl;
    return false;    
}
bool AssessorManage::updateAssessorStatus(int assessorId)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"update Assessor set status='Approve' where assessorId=%d",assessorId);
    if(mysql_query(_con,sql))
    {
        cerr <<  mysql_error(_con) <<endl;
        return false;
    }
    return true;
}
//重写虚函数实现，审核员必须被批准成为审核员，才能登录
//在视图view_assessorUser中查找
User AssessorManage::searchByUserNameAndPassword(const string& userName,const string& password)
{
    char sql[1024];
    struct User ret;
    snprintf(sql,sizeof(sql),"select * from view_assessorUser where userName='%s' and password='%s'",userName.c_str(),password.c_str());
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
        string applicationTime = row[7];
        AssessorStatus status =AssessorStatus(atoi(row[8]));
        int categoryId = atoi(row[9]);
        int pendingAudit = atoi(row[10]);
        if(status ==AssessorStatus::Pending)
        {
            ret._flag = SearchFlag::NONE;//成为审核员请求正在审批中
            return ret;    
        }
        struct User user(userId,role,nickName,userName,password,avatar,phone);
        return user;
    }
    ret._flag = SearchFlag::NONE;//用户不存在
    return ret;    
}
struct Assessor AssessorManage::searchByAssessorId(int assessorId)
{
    char sql[1024];
    struct Assessor ret;
    snprintf(sql,sizeof(sql),"select * from view_assessorUser where User.userId='%d'",assessorId);
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
        //applicationTime,Assessor.status,Assessor.categoryId,Assessor.pendingAudit
        string applicationTime = row[7];
        string description = row[8];
        AssessorStatus status =AssessorStatus(atoi(row[9]));
        int categoryId = atoi(row[10]);
        int pendingAudit = atoi(row[11]);
        //int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,
        //const string& applicantTime,const string& description,AssessorStatus status,int categoryId,int pendingAudit
        struct Assessor assessor(userId,role,nickName,userName,password,avatar,phone,applicationTime,description,status,categoryId,pendingAudit);
        return assessor;
    }
    ret._flag = SearchFlag::NONE;//审核员不存在
    return ret;
}
vector<struct Assessor> AssessorManage::searchAll()
{
    char sql[1024];
    vector<struct Assessor> ret;
    snprintf(sql,sizeof(sql),"select * from view_assessorUser");
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return ret;
    }
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row = mysql_fetch_row(res);
    while(row = mysql_fetch_row(res))
    {
        int userId = atoi(row[0]);
        Role role = Role(atoi(row[1]));
        string nickName = row[2];
        string userName = row[3];
        string password = row[4];
        string avatar = row[5];
        string phone = row[6];
        string applicationTime = row[7];
        string description = row[8];
        AssessorStatus status =AssessorStatus(atoi(row[9]));
        int categoryId = atoi(row[10]);
        int pendingAudit = atoi(row[11]);
        //int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,
        //const string& applicantTime,const string& description,AssessorStatus status,int categoryId,int pendingAudit
        struct Assessor a(userId,role,nickName,userName,password,avatar,phone,applicationTime,description,status,categoryId,pendingAudit);
        ret.push_back(a);
    }
    return ret;
}
vector<struct Assessor> AssessorManage::searchByStatus(AssessorStatus status)
{
    char sql[1024];
    vector<struct Assessor> ret;
    snprintf(sql,sizeof(sql),"select * from view_assessorUser where status='%d'",status);
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return ret;
    }
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row = mysql_fetch_row(res);
    while(row = mysql_fetch_row(res))
    {
        int userId = atoi(row[0]);
        Role role = Role(atoi(row[1]));
        string nickName = row[2];
        string userName = row[3];
        string password = row[4];
        string avatar = row[5];
        string phone = row[6];
        string applicationTime = row[7];
        string description = row[8];
        AssessorStatus status =AssessorStatus(atoi(row[9]));
        int categoryId = atoi(row[10]);
        int pendingAudit = atoi(row[11]);
        //int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,
        //const string& applicantTime,const string& description,AssessorStatus status,int categoryId,int pendingAudit
        struct Assessor a(userId,role,nickName,userName,password,avatar,phone,applicationTime,description,status,categoryId,pendingAudit);
        ret.push_back(a);
    }
    return ret;    
}