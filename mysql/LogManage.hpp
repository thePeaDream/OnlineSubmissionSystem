#pragma once
#include "../entity/Log.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
//   Log(int logId,const string& operate,const string& operateTime)
class LogManage{
public:
    //Log(int logId,const string& operate,const string& operateTime)
    LogManage()
    :_con(sqlConnect.GetMYSQLObject())
    {}
    ~LogManage(){}
    bool remove(int logId);
    vector<Log> searchAll();
    vector<Log> searchByDate(const string& date);
private:
    MYSQL *_con;
};
bool LogManage::remove(int logId)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Log where logId=%d",logId);
    if(mysql_query(_con,sql) == 0)
    {
        return true;
    }
    return false;   
}
vector<Log> LogManage::searchAll()
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Log order by operateTime desc");
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<Log> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;//该结构体对象保存一行记录,其实就是个二级指针
    //row[0]对应这一行的id  row[1]对应这一行的nickName ..依次类推取决于表结构设计
    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Log(int logId,const string& operate,const string& operateTime)
        int logId = atoi(row[0]);
        string operate = row[1];
        string operateTime = row[2];
        //每一行的记录插入到vector中
        ret.push_back(Log(logId,operate,operateTime));
    }
    return ret;   
}
vector<Log> LogManage::searchByDate(const string& date)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Log where Date(operateTime)=%s order by operateTime desc",date);
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<Log> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;//该结构体对象保存一行记录,其实就是个二级指针
    //row[0]对应这一行的id  row[1]对应这一行的nickName ..依次类推取决于表结构设计
    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Log(int logId,const string& operate,const string& operateTime)
        int logId = atoi(row[0]);
        string operate = row[2];
        string operateTime = row[3];
        //每一行的记录插入到vector中
        ret.push_back(Log(logId,operate,operateTime));
    }
    return ret;   
}