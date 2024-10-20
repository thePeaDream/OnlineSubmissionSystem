#pragma once
#include "../entity/Notice.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
class NoticeManage{
public:
    NoticeManage()
    :_con(sqlConnect.GetMYSQLObject()){}
    ~NoticeManage(){};
    bool insert(const string& title,const string& content);
    bool remove(int noticeId);
    bool update(int noticeId,const string&title,const string& content);
    vector<Notice> searchByPublishDate(const string& publishDate);
    Notice searchByTitle(const string& title);
    vector<Notice> searchAll();
private:
    MYSQL* _con;
};
bool NoticeManage::insert(const string& title,const string& content)
{
     char sql[1024];
     snprintf(sql,sizeof(sql),"insert into Notice (publishTime,latestTime,title,content) values(now(),now(),'%s','%s')",title.c_str(),content.c_str());
     if(mysql_query(_con,sql))
     {
        cerr << mysql_error(_con) << endl;
        return false;
     }
     return true;
}
bool NoticeManage::remove(int noticeId)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Notice where noticeId=%d",noticeId);
    if(mysql_query(_con,sql) == 0)
    {
        return true;
    }
    return false;
}
bool NoticeManage::update(int noticeId,const string&title,const string& content)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"update Notice set latestTime=now(),title='%s',content='%s' where noticeId=%d",title.c_str(),content.c_str(),noticeId);
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;
}
//根据发布日期查询通知
vector<Notice> NoticeManage::searchByPublishDate(const string& publishDate)
{
    char sql[1024];
    //DATE(publishTime)函数将datetime类型转换为date类型
    snprintf(sql,sizeof(sql),"select * from Notice where Date(publishTime)='%s'",publishDate);
    if(mysql_query(_con,sql) != 0)
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<Notice> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;

    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Notice(int noticeId,const string& publishTime,const string& latestTime,const string& title,const string& content)
        Notice n;
        n._noticeId = atoi(row[0]);
        n._publishTime = row[1];
        n._latestTime = row[2];
        n._title = row[3];
        n._content = row[4];
        //每一行的记录插入到vector中
        ret.push_back(n);
    }
    return ret;
} 
//根据标题查询通知
Notice NoticeManage::searchByTitle(const string& title)
{
    char sql[1024];
    Notice ret;
    snprintf(sql,sizeof(sql),"select * from Notice where title='%s'",title.c_str());
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        ret._flag = SearchFlag::SQLERROR;
        return ret;
    }
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;
    if(row = mysql_fetch_row(res)) 
    {
        ret._noticeId = atoi(row[0]);
        ret._publishTime = row[1];
        ret._latestTime = row[2];
        ret._title = row[3];
        ret._content = row[4];
        return ret;
    }
    //没有查到
    ret._flag = SearchFlag::NONE;
    return ret;
}
//查询所有通知
vector<Notice> NoticeManage::searchAll()
{
    char sql[1024];
    //DATE(publishTime)函数将datetime类型转换为date类型
    snprintf(sql,sizeof(sql),"select * from Notice order by latestTime desc");
    if(mysql_query(_con,sql) != 0)
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<Notice> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;

    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Notice(int noticeId,const string& publishTime,const string& latestTime,const string& title,const string& content)
        Notice n;
        n._noticeId = atoi(row[0]);
        n._publishTime = row[1];
        n._latestTime = row[2];
        n._title = row[3];
        n._content = row[4];
        //每一行的记录插入到vector中
        ret.push_back(n);
    }
    return ret;
}

