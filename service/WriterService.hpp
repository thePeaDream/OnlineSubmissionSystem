#include "../mysql/ManuscriptManage.hpp"
#include "../mysql/NoticeManage.hpp"
#include "../mysql/WriterManage.hpp"

// 作者
// 0 注册 
// 1 提交个人稿件
// 2 获取个人历史稿件
// 3 删除个人稿件
// 4 修改个人稿件
// 5 查看所有已公开稿件(可以根据稿件名、稿件类型来搜索稿件)
class WriterService
{
private:
    ManuscriptManage manuscriptHandle;
    WriterManage writerHandle;
public:
    WriterService(){}
    ~WriterService(){}
    // 注册
    string Register(const Json::Value& root)
    { 
        string nickName = root["nickName"].asString();
        string userName = root["userName"].asString();
        string password = root["password"].asString();
        string avatar = "????";//用户默认头像
        string phone = root["phone"].asString();
        bool flag = writerHandle.insert(nickName,userName,password,avatar,phone);
        if(flag == false)
            cerr << "注册失败,用户名或密码有误"<<endl;
        else 
            cerr << "注册成功"<<endl;
        return "flag:"+std::to_string(flag);;
    }
    // 提交个人稿件
    string SubmitPersonalManuscript(const Json::Value& root)
    {
        string description = root["description"].asString();
        int categoryId = root["categoryId"].asInt();
        int writerId = root["writerId"].asInt();

        return ""; 
    }
    // 获取个人所有稿件
    string GetAllPersonalManuscript(const Json::Value& root)
    {
        int writerId = root["writerId"].asInt();
        vector<Manuscript> ret = manuscriptHandle.searchByWriterId(writerId);
        return "";
    }
    // 删除个人稿件
    string RemovePersonalManuscript(const Json::Value& root)
    {
        int manuscriptId = root["manuscriptId"].asInt();
        int userId = root["userId"].asInt();
        bool flag = manuscriptHandle.remove(manuscriptId);
        return GetAllPersonalManuscript(root); 
    }
    //修改/更新个人稿件，当自己更新个人稿件时，审核回复和稿件状态会重置
    string UpdatePersonalManuscript(const Json::Value& root)
    {
        int manuscriptId = root["manuscriptId"].asInt();
        string description = root["description"].asString();
        string latestTime = root["latestTime"].asString();
        int categoryId = root["categoryId"].asInt();
        
        return "";
    }
    //查看所有已公开稿件
    string GetAllPublishManuscript(const Json::Value& root)
    {
        vector<Manuscript> ret = manuscriptHandle.searchByState(ManuscriptStatus::Publish);
        
        return "";
    }
};