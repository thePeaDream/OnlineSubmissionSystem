#pragma once
#include "../mysql/NoticeManage.hpp"
#include "../mysql/AssessorManage.hpp"
#include "../mysql/WriterManage.hpp"
#include "../mysql/ManuscriptManage.hpp"
#include "../mysql/LogManage.hpp"

// 管理员
// 1 添加系统通知
// 2 删除系统通知
// 3 修改系统通知

// 4 获取审核员列表
// 5 修改审核员申请状态 pending Approve
// 6 删除审核员
// 7 手动添加审核员

// 8 获取作者列表
// 9 删除作者
// 10 手动添加作者

// 10 获取所有稿件
// 11 为稿件分配审核员

// 12 查看系统日志
// 13 删除某条日志信息

class AdminService
{
private:
    NoticeManage noticeHandle;
    AssessorManage assessorHandle;
    WriterManage writerHandle;
    ManuscriptManage manuscriptHandle;    
    LogManage logHandle;
public:
    AdminService(){}
    ~AdminService(){}
    // 添加通知
    string AddNotice(const Json::Value& root)
    {
        string title = root["title"].asString();
        string content = root["content"].asString();
        bool flag = noticeHandle.insert(title,content);
        return "";
    }
    // 删除通知
    string RemoveNotice(const Json::Value& root)
    {
        int noticeId = root["noticeId"].asInt();
        bool flag = noticeHandle.remove(noticeId);
        return "";
    }
    // 修改通知
    string UpdateNotice(const Json::Value& root)
    {
        int noticeId = root["noticeId"].asInt();
        string title = root["title"].asString();
        string content = root["content"].asString();
        bool flag = noticeHandle.update(noticeId,title,content);
        return "";
    }
    
    // 获取审核员列表
    string GetAllAssessor()
    {
        vector<struct Assessor> ret = assessorHandle.searchAll();
        return "";
    }
    // 设置审核员的申请状态
    string SetAssessorStatus(const Json::Value& root)
    {
        int assessorId = root["assessorId"].asInt();
        AssessorStatus status =AssessorStatus(root["status"].asInt());
        bool flag = assessorHandle.updateAssessorStatus(assessorId,status);
        return GetAllAssessor();
    }
    // 删除审核员
    string RemoveAssessor(const Json::Value& root)
    {
        int assessorId = root["assessorId"].asInt();
        bool flag = assessorHandle.remove(assessorId);
        return GetAllAssessor();
    }
    
    // 获取所有作者信息
    string GetAllWriter()
    {
        vector<struct Writer> ret = writerHandle.searchAll();
        return "";
    }
    // 删除作者
    string RemoveWriter(const Json::Value& root)
    {
        int writerId = root["writerId"].asInt();
        bool flag = writerHandle.remove(writerId);
        return GetAllWriter();
    }

    //获取所有稿件
    string GetAllManuscript()
    {
        vector<Manuscript> ret = manuscriptHandle.searchAll();
        return "";
    }
    //为稿件分配审核员
    string AssignAssessor(const Json::Value& root)
    {
        int manuscriptId = root["manuscriptId"].asInt();
        int assessorId = root["assessorId"].asInt();
        bool flag = manuscriptHandle.assignAssessor(manuscriptId,assessorId);
        return GetAllManuscript();
    }

    //查看系统所有日志
    string GetAllLog()
    {
        vector<Log> ret = logHandle.searchAll();
        return "";
    }
    //删除系统日志
    string RemoveLog(const Json::Value& root)
    {
        int logId = root["logId"].asInt();
        bool flag = logHandle.remove(logId);
        return GetAllLog();
    }
};