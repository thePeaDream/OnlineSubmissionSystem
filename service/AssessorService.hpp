#pragma once
#include "../mysql/ManuscriptManage.hpp"
#include "../mysql/AssessorManage.hpp"

//审核
//1 获取稿件列表(属于自己审核的稿件,根据稿件状态)
//2 修改稿件状态,包括稿件评价 和稿件状态
//3 申请成为审核

class AssessorService{
private:
    ManuscriptManage manuscriptHandle;
    AssessorManage assessorHandle;
public:
    AssessorService(){}
    ~AssessorService(){}
    string GetAuditManuscript(const Json::Value& root)
    {
        int assessorId = root["assessorId"].asInt();
        vector<Manuscript> ret = manuscriptHandle.searchByAssessorId(assessorId);       
        return "";
    }
    string SetManuscriptState(const Json::Value& root)
    {
        int manuscriptId = root["manuscriptId"].asInt();
        ManuscriptStatus status = ManuscriptStatus(root["status"].asInt());
        string comment = root["comment"].asString();//审核回复
        bool flag = manuscriptHandle.updateForAssessor(manuscriptId,status,comment);
        if(flag == false) cerr << "更新稿件状态失败"<<endl;
        return GetAuditManuscript(root);
    }
    string applicationAssessor(const Json::Value& root)//申请成为审核
    {
        string nickName = root["nickName"].asString();
        string userName = root["userName"].asString();
        string password = root["password"].asString();
        string avatar = "????";//用户默认头像
        string phone = root["phone"].asString();
        string description = root["description"].asString();
        int categoryId = root["categoryId"].asInt();
        bool flag = assessorHandle.insert(nickName,userName,password,avatar,phone,description,categoryId);
        return "flag:"+std::to_string(flag);
    }
};