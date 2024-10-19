#pragma once
#include "../entity/Category.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
class CategoryManage{
public:
    CategoryManage()
    :_con(sqlConnect.GetMYSQLObject()){}
    ~CategoryManage(){}
    bool insert(const string& name);
    bool remove(const string& name);
    vector<Category> searchAll();
private:
    MYSQL* _con;
};
bool CategoryManage::insert(const string& name)
{
     char sql[1024];
     snprintf(sql,sizeof(sql),"insert into Category(name) values('%s')",name.c_str());
     if(mysql_query(_con,sql))
     {
        cerr << mysql_error(_con) << endl;
        return false;
     }
     return true;
}
bool CategoryManage::remove(const string& name)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Category where name='%s'",name);
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;   
}
vector<Category> CategoryManage::searchAll()
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Category order");
    if(mysql_query(_con,sql))
    {
        cerr << mysql_error(_con) <<endl;
        return {};
    }
    vector<Category> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;//该结构体对象保存一行记录,其实就是个二级指针
    //row[0]对应这一行的id  row[1]对应这一行的nickName ..依次类推取决于表结构设计
    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        //Category(int categoryId,const string& name)
        int categoryId = atoi(row[0]);
        string name = row[1];
        //每一行的记录插入到vector中
        ret.push_back(Category(categoryId,name));
    }
    return ret;   
}