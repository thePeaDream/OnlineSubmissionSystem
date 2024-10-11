#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

enum Role{
    Writer, //0
    Assessor, //1
    Admin  //2
};

struct Person
{
    int id;
    string nickName;//昵称
    string userName;
    string password;
    string avatar;//头像路径
    string phone;
    Role role;
};

class PersonManager{
    PersonManager(){}
    ~PersonManager();
public:
    //设置成单例模式
    static PersonManager* GetInstance()
    {
        static PersonManager PersonManager;
        return &PersonManager; 
    }

    bool insert(const Person& w);
    bool update(const Person& w);
    bool remove(const Person& w);
    vector<Person> query(const string& condition);//根据某个条件查找作者信息

private:
    MYSQL* _con;
    const char* user = "root";
    const char* password = "123456";
    const char* mysqlIp = "127.0.0.1";
    const int serverPort = 3306;
    const char* dbName = "OnlineSubmissionSystem";
};

bool PersonManager::insert(const Person& w)
{
     char sql[1024];
     //注意c的枚举是从0开始，但mysql的枚举是从1开始
     snprintf(sql,sizeof(sql),"insert into Persons (nickName,userName,password,avatar,phone,role) values('%s','%s','%s','%s','%s',%d)",w.nickName,w.userName,w.password,w.avatar,w.phone,w.role + 1);
     if(mysql_query(_con,sql) == -1)
     {
        cerr << "插入数据发生错误" << endl;
        return false;
     }
     return true;
}

bool PersonManager::update(const Person& w)
{
     char sql[1024];
     snprintf(sql,sizeof(sql),"update Persons set nickName='%s',password='%s',avatar='%s',phone='%s' where id=%d",w.nickName,w.password,w.avatar,w.phone,w.id);
     if(mysql_query(_con,sql) == -1)
     {
        cerr << "更新数据发生错误" << endl;
        return false;
     }
     return true;
}

bool PersonManager::remove(const Person& w)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Persons where id=%d",w.id);
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "删除数据发生错误"<<endl;
        return false;
    }
    return true;
}

vector<Person> PersonManager::query(const string& condition)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Persons %s",condition.c_str());
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "查询Person出错"<<endl;
        return {};
    }
    vector<Person> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;//该结构体对象保存一行记录,其实就是个二级指针
    //row[0]对应这一行的id  row[1]对应这一行的nickName ..依次类推取决于表结构设计
    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        Person w;
        w.id = atoi(row[0]);
        w.nickName = row[1];
        w.userName = row[2];
        w.password = row[3];
        w.avatar = row[4];
        w.phone = row[5];
        w.role = Role(atoi(row[6])-1);
        //每一行的记录插入到vector中
        ret.push_back(w);
    }
    return ret;
} 
