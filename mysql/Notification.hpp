#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;


struct Notification
{
    int id;
    string date;
    string title;
    string content;
};

class NotificationManager{
    NotificationManager(){}
    ~NotificationManager();
public:
    //设置成单例模式
    static NotificationManager* GetInstance()
    {
        static NotificationManager NotificationManager;
        return &NotificationManager; 
    }

    bool insert(const Notification& n);
    bool remove(const Notification& n);
    vector<Notification> query(const string& condition);

private:
    MYSQL* _con;
    const char* user = "root";
    const char* password = "123456";
    const char* mysqlIp = "127.0.0.1";
    const int serverPort = 3306;
    const char* dbName = "OnlineSubmissionSystem";
};

bool NotificationManager::insert(const Notification& n)
{
     char sql[1024];
     //注意c的枚举是从0开始，但mysql的枚举是从1开始
     snprintf(sql,sizeof(sql),"insert into Notifications (date,title,content) values('%s','%s','%s')",n.date,n.title,n.content);
     if(mysql_query(_con,sql) == -1)
     {
        cerr << "插入通知发生错误" << endl;
        return false;
     }
     return true;
}

bool NotificationManager::remove(const Notification& n)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Notifications where id=%d",n.id);
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "删除通知发生错误"<<endl;
        return false;
    }
    return true;
}

vector<Notification> NotificationManager::query(const string& condition)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Notifications %s",condition.c_str());
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "查询Notification信息出错"<<endl;
        return {};
    }
    vector<Notification> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;

    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        Notification n;
        n.id = atoi(row[0]);
        n.date = row[1];
        n.title = row[2];
        n.content = row[3];

        //每一行的记录插入到vector中
        ret.push_back(n);
    }
    return ret;
} 
