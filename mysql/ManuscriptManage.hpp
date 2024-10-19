#include "../entity/Manuscript.hpp"
#include "../entity/Category.hpp"
#include "SQLConnect.hpp"
extern SQLConnect sqlConnect;
class ManuscriptManage
{
public:
    ManuscriptManage()
        : _con(sqlConnect.GetMYSQLObject()) {}
    ~ManuscriptManage() {};
    bool insert(const string& description,const string& comment,const string& name,const string& path,int size,int categoryId,int writerId); //新增稿件
    bool remove(int id);//删除稿件
    bool assignAssessor(int manuscriptId,int assessorId);//给稿件分配一位审核员
    //一旦修改稿件后，稿件的状态会被重置 —— 稿件为待审核，审核人设置为空
    bool update(int manuscriptId,const string& description,const string& comment,const string& name,const string& path,int size,int categoryId);//更新稿件信息
    bool updateForAssessor(int manuscriptId,ManuscriptStatus status,const string& comment);
    Manuscript searchByManuscriptId(int manuscriptId);     // 稿件id
    vector<Manuscript> searchByAssessorId(int assessorId); // 审核人id
    vector<Manuscript> searchByWriterId(int writerId);     // 作者id
    vector<Manuscript> searchByName(const string &name);   // 稿件名
    vector<Manuscript> searchByCategory(const Category& category);  //稿件类型
    vector<Manuscript> searchByState(ManuscriptStatus status);      // 稿件状态
    vector<Manuscript> searchAll();
private:
    MYSQL *_con;
};

bool ManuscriptManage::insert(const string& description,const string& comment,const string& name,const string& path,int size,int categoryId,int writerId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "insert into Manuscript (description,submitTime,latestTime,comment,name,path,size,categoryId,status,writerId,assessorId)\
                                                    values('%s',     now(),      now(),    '%s',  '%s','%s',%d,    %d,   'UnderReview', %d,    null)",
                                                        description.c_str(), comment.c_str(), name.c_str(), path.c_str(), size, categoryId, writerId);
    if (mysql_query(_con, sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;
}
bool ManuscriptManage::remove(int menuscriptId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "delete from Manuscript where manuscriptId=%d", menuscriptId);
     if (mysql_query(_con, sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;
}

//分配审核员
bool ManuscriptManage::assignAssessor(int manuscriptId,int assessorId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "update Manuscript set assessorId=%d where manuscriptId=%d",
            assessorId, manuscriptId);
    if (mysql_query(_con, sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;
}
//一旦修改稿件后，稿件的状态会被重置 —— 稿件为待审核，审核人设置为null
bool ManuscriptManage::update(int manuscriptId,const string& description,const string& comment,const string& name,const string& path,int size,int categoryId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "update Manuscript set description='%s',latestTime=now(),comment='%s',name='%s',path='%s',\
                                size=%d,categoryId=%d,status='审核中',assessorId=null) where manuscriptId=%d",
            description.c_str(),comment.c_str(),name.c_str(),path.c_str(),
            size,categoryId, manuscriptId);
    if (mysql_query(_con, sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;
    }
    return true;
}

// 根据稿件id查找稿件
Manuscript ManuscriptManage::searchByManuscriptId(int manuscriptId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where manuscriptId=%d", manuscriptId);
    if (mysql_query(_con, sql))
    {
        Manuscript m;
        cerr << mysql_error(_con) << endl;
        m._flag = SearchFlag::SQLERROR;
        return m;
    }
    Manuscript m;
    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;
    if(row = mysql_fetch_row(res))
    {
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        return m;
    } 
    m._flag = SearchFlag::NONE;
    return m;
}
// 根据审核人id查找稿件
vector<Manuscript> ManuscriptManage::searchByAssessorId(int assessorId)
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript where assessorId=%d",assessorId);
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}
// 根据作者id查找稿件
vector<Manuscript> ManuscriptManage::searchByWriterId(int writerId)
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript where writerId=%d",writerId);
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}
// 根据稿件名查找
vector<Manuscript> ManuscriptManage::searchByName(const string &name)
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript where name='%s'",name);
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}
// 根据稿件类型查找稿件
vector<Manuscript> ManuscriptManage::searchByCategory(const Category& category) 
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript where categoryId=%d",category._categoryId);
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}
// 根据稿件状态查找稿件
vector<Manuscript> ManuscriptManage::searchByState(ManuscriptStatus status)
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript where status=%d",s);
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}
vector<Manuscript> ManuscriptManage::searchAll()
{
   char sql[1024];
   sprintf(sql,"select * from Manuscript");
   if(mysql_query(_con,sql))
   {
        cerr << mysql_error(_con) << endl;
        return {};
   }
   vector<Manuscript> ret;
   MYSQL_RES *res = mysql_store_result(_con);
   MYSQL_ROW row;
   while(row = mysql_fetch_row(res))
   {
        Manuscript m;
        m._manuscriptId = atoi(row[0]);
        m._description = row[1];
        m._submitTime = row[2];
        m._latestTime = row[3];
        m._comment = row[4];
        m._name = row[5];
        m._path = row[6];
        m._size = atoi(row[7]);
        m._categoryId = atoi(row[8]);
        m._status = ManuscriptStatus(atoi(row[9]));
        m._writerId = atoi(row[10]);
        m._assessorId = atoi(row[11]);
        ret.push_back(m);
   }
   return ret;
}