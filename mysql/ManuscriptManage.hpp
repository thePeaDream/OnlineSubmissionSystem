#include "../entity/Manuscript.hpp"
#include "../entity/Category.hpp"
#include "SQLConnect.hpp"
class ManuscriptManage
{
public:
    ManuscriptManage(MYSQL *con)
        : _con(con) {}
    ~ManuscriptManage() {};
    bool insert(const Manuscript &m);
    bool remove(int id);
    bool update(const Manuscript &m);
    Manuscript searchByManuscriptId(int menuscriptId);     // 稿件id
    vector<Manuscript> searchByAssessorId(int assessorId); // 审核人id
    vector<Manuscript> searchByWriterId(int writerId);     // 作者id
    vector<Manuscript> searchByName(const string &name);   // 稿件名
    vector<Manuscript> searchBySubmitDate(const string& submitDate); // 稿件上传日期
    vector<Manuscript> searchByCategory(const Category& category);  //稿件类型
    vector<Manuscript> searchByState(Status s);            // 稿件状态
private:
    MYSQL *_con;
};
bool ManuscriptManage::insert(const Manuscript &m)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "insert into Manuscript (description,submitTime,latestTime,comment,name,path,size,categoryId,status,writerId,assessorId)\
                                                    values('%s',     now(),      now(),    '%s',  '%s','%s',%d,    %d,       %d,    %d,       %d)",
            m._description.c_str(), m._submitTime.c_str(), m._latestTime.c_str(), 
            m._comment.c_str(),m._name.c_str(),m._path.c_str(),
            m._size,m._categoryId,m._status,m._writerId, m._assessorId);
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
bool ManuscriptManage::update(const Manuscript &m)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "update Manuscript set description='%s',submitTime='%s',latestTime='%s',comment='%s',name='%s',path='%s',\
                                size=%d,categoryId=%d,status=%d,assessorId=%d) where manuscriptId=%d",
            m._description.c_str(), m._submitTime.c_str(), m._latestTime.c_str(), 
            m._comment.c_str(),m._name.c_str(),m._path.c_str(),
            m._size,m._categoryId,m._status, m._assessorId,m._manuscriptId);
    if (mysql_query(_con, sql))
    {
        cerr << mysql_error(_con) << endl;
        return false;

    }
    return true;
}

// 根据稿件id查找稿件
Manuscript ManuscriptManage::searchByManuscriptId(int menuscriptId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where manuscriptId=%d", id);
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }

    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row = mysql_fetch_row(res);
    Manuscript m;
    m.id = atoi(row[0]);
    m.submitTime = row[1];
    m.latestUpdateTime = row[2];
    m.name = row[3];
    m.description = row[4];
    m.state = State(atoi(row[5]) - 1);
    m.comment = row[6];
    m.file = row[7];
    m.writerId = atoi(row[8]);
    m.AssessorId = atoi(row[9]);

    return m;
}
// 根据审核人id查找稿件
vector<Manuscript> ManuscriptManage::searchByAssessorId(int assessorId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where id=%d", id);
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }

    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;
    if(row = mysql_fetch_row(res))
    {

    } 
    Manuscript m;
    m.id = atoi(row[0]);
    m.submitTime = row[1];
    m.latestUpdateTime = row[2];
    m.name = row[3];
    m.description = row[4];
    m.state = State(atoi(row[5]) - 1);
    m.comment = row[6];
    m.file = row[7];
    m.writerId = atoi(row[8]);
    m.AssessorId = atoi(row[9]);

    return m;
}
// 根据作者id查找稿件
vector<Manuscript> ManuscriptManage::searchByWriterId(int writerId)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where writerId=%d", writerId);
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }
    vector<Manuscript> ret;
    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;

    while (row = mysql_fetch_row(res)) // 读完了会返回nullptr
    {
        Manuscript m;
        m.id = atoi(row[0]);
        m.submitTime = row[1];
        m.latestUpdateTime = row[2];
        m.name = row[3];
        m.description = row[4];
        m.state = State(atoi(row[5]) - 1);
        m.comment = row[6];
        m.file = row[7];
        m.writerId = atoi(row[8]);
        m.AssessorId = atoi(row[9]);
        // 每一行的记录插入到vector中
        ret.push_back(m);
    }
    return ret;
}

// 根据稿件名查找
vector<Manuscript> ManuscriptManage::searchByName(const string &name)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where name='%s'", name.c_str());
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }
    vector<Manuscript> ret;
    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;

    while (row = mysql_fetch_row(res)) // 读完了会返回nullptr
    {
        Manuscript m;
        m.id = atoi(row[0]);
        m.submitTime = row[1];
        m.latestUpdateTime = row[2];
        m.name = row[3];
        m.description = row[4];
        m.state = State(atoi(row[5]) - 1);
        m.comment = row[6];
        m.file = row[7];
        m.writerId = atoi(row[8]);
        m.AssessorId = atoi(row[9]);
        // 每一行的记录插入到vector中
        ret.push_back(m);
    }
    return ret;
}
// 根据稿件上传日期查找
vector<Manuscript> ManuscriptManage::searchByName(const string &name)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where name='%s'", name.c_str());
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }
    vector<Manuscript> ret;
    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;

    while (row = mysql_fetch_row(res)) // 读完了会返回nullptr
    {
        Manuscript m;
        m.id = atoi(row[0]);
        m.submitTime = row[1];
        m.latestUpdateTime = row[2];
        m.name = row[3];
        m.description = row[4];
        m.state = State(atoi(row[5]) - 1);
        m.comment = row[6];
        m.file = row[7];
        m.writerId = atoi(row[8]);
        m.AssessorId = atoi(row[9]);
        // 每一行的记录插入到vector中
        ret.push_back(m);
    }
    return ret;
}
// 根据稿件类型查找稿件
vector<Manuscript> ManuscriptManage::searchByCategory(const Category& category) 
{

}
// 根据稿件状态查找稿件
vector<Manuscript> ManuscriptManage::searchByState(Status s)
{
    char sql[1024];
    snprintf(sql, sizeof(sql), "select * from Manuscript where state=%d", (int)s + 1);
    if (mysql_query(_con, sql) != 0)
    {
        cerr << mysql_error(_con) << endl;
        return {};
    }
    vector<Manuscript> ret;
    // 查询结构是放在了MYSQL _con结构体对象里,可以用接口提取
    MYSQL_RES *res = mysql_store_result(_con);
    MYSQL_ROW row;

    while (row = mysql_fetch_row(res)) // 读完了会返回nullptr
    {
        Manuscript m;
        m.id = atoi(row[0]);
        m.submitTime = row[1];
        m.latestUpdateTime = row[2];
        m.name = row[3];
        m.description = row[4];
        m.state = State(atoi(row[5]) - 1);
        m.comment = row[6];
        m.file = row[7];
        m.writerId = atoi(row[8]);
        m.AssessorId = atoi(row[9]);
        // 每一行的记录插入到vector中
        ret.push_back(m);
    }
    return ret;
}