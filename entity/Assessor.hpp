#pragma once
#include "User.hpp"
enum AssessorStatus{
    Err,//0
    Pending,//1  待审批
    Approve,//2  已通过
};
//审核员
struct Assessor:public User
{
public:
    string _applicationTime;//申请时间
    string _description;//个人描述
    AssessorStatus _status = Pending;//审核员状态 —— 待审批 和 通过,不通过的直接从表里删掉了,并发短信给对应电话号
    int _categoryId;//擅长哪一种类别的稿件
    int _pendingAudit;//待审核稿件数量
public:
    Assessor(){}
    Assessor(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,
    const string& applicantTime,const string& description,AssessorStatus status,int categoryId,int pendingAudit)
    :User(userId,role,nickName,userName,password,avatar,phone)
    ,_applicationTime(applicantTime)
    ,_description(description)
    ,_status(status)
    ,_categoryId(categoryId)
    ,_pendingAudit(pendingAudit)
    {}
};