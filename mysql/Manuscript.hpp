#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;


struct Manuscript
{
    int id;
    string submitTime;
    string name;//稿件名/标题
    string description;
    int state;//1 已提交 2 已驳回 3 审核中
    string comment;//审核评价
    string file;//稿件文件所在路径
    int writerId;//作者id    
};

class ManuscriptManager{
    ManuscriptManager(){}
    ~ManuscriptManager();
public:
    //设置成单例模式
    static ManuscriptManager* GetInstance()
    {
        static ManuscriptManager ManuscriptManager;
        return &ManuscriptManager; 
    }

    bool insert(const Manuscript& m);
    bool remove(const Manuscript& m);
    bool update(const Manuscript& m);
    vector<Manuscript> query(const string& condition);

private:
    MYSQL* _con;
    const char* user = "root";
    const char* password = "123456";
    const char* mysqlIp = "127.0.0.1";
    const int serverPort = 3306;
    const char* dbName = "OnlineSubmissionSystem";
};

bool ManuscriptManager::insert(const Manuscript& m)
{
     char sql[1024];
     snprintf(sql,sizeof(sql),"insert into Manuscripts (submitTime,name,description,state,comment,file,writerId)\
     values('%s','%s','%s',%d,'%s','%s',%d)",
     m.submitTime.c_str(),m.name.c_str(),m.description.c_str(),m.state,m.comment.c_str(),m.file.c_str(),m.writerId);
     
     if(mysql_query(_con,sql) == -1)
     {
        cerr << "添加稿件发生错误" << endl;
        return false;
     }
     return true;
}

bool ManuscriptManager::remove(const Manuscript& m)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"delete from Manuscripts where id=%d",m.id);
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "删除稿件发生错误"<<endl;
        return false;
    }
    return true;
}

bool ManuscriptManager::update(const Manuscript& m)
{
     char sql[1024];
     snprintf(sql,sizeof(sql),"update Manuscript set submitTime='%s',name='%s',description='%s',state=%d,comment='%s',file='%s',writerId=%d where id=%d",
                              m.submitTime.c_str(),m.name.c_str(),m.description.c_str(),m.state,m.comment.c_str(),m.file.c_str(),m.writerId);
     if(mysql_query(_con,sql) == -1)
     {
        cerr << "更新稿件信息发生错误" << endl;
        return false;
     }
     return true;
}

vector<Manuscript> ManuscriptManager::query(const string& condition)
{
    char sql[1024];
    snprintf(sql,sizeof(sql),"select * from Manuscripts %s",condition.c_str());
    if(mysql_query(_con,sql) == -1)
    {
        cerr << "查询Manuscript信息出错"<<endl;
        return {};
    }
    vector<Manuscript> ret;
    //查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES* res = mysql_store_result(_con);
    MYSQL_ROW row;

    while(row = mysql_fetch_row(res)) //读完了会返回nullptr
    {
        Manuscript m;
        m.id = atoi(row[0]);
        m.submitTime = row[1];
        m.name = row[2];
        m.description = row[3];
        m.state = atoi(row[4]);
        m.comment = row[5];
        m.file = row[6];
        m.writerId = atoi(row[7]);
        //每一行的记录插入到vector中
        ret.push_back(m);
    }
    return ret;
} 
