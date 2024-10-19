#pragma once
#include "../mysql/NoticeManage.hpp"
#include "../mysql/AdminManage.hpp"
#include "../mysql/AssessorManage.hpp"
#include "../mysql/WriterManage.hpp"
#include "../mysql/CategoryManage.hpp"
#include <jsoncpp/json/json.h>

//通用
//1 登录 
//2 修改个人基本信息 
//3 获取个人全部信息
//4 获取系统通知列表 
//5 获取稿件所有类别 
class CommonService{
private:
    CategoryManage categoryHandle;
    NoticeManage noticeHandle;
    AdminManage adminHandle;
    UserManage userHandle;
    WriterManage writerHandle;
    AssessorManage assessorHandle;
public:
    CommonService(){}
    string Login(const Json::Value& root)
    {
        string userName = root["userName"].asString();
        string password = root["password"].asString();
        Role role =Role(root["role"].asInt());
        
        User user;
        //子类对象赋值给父类对象 —— 切片
        if(role == Assessor)
            user = assessorHandle.searchByUserNameAndPassword(userName,password);
        else if(role == Admin)
            user = adminHandle.searchByUserNameAndPassword(userName,password);
        else if(role == Writer)
            user = writerHandle.searchByUserNameAndPassword(userName,password);
        
        if(user._flag == NONE)//用户不存在
        {
            return "";
        }
        else if(user._flag == SQLERROR)//数据库查找发生异常
        {
            return "";
        }
        else if(user._flag == FIND)
        {
            Json::Value root2;
            root2["id"] = user._userId;
            root2["userName"] = user._userName;
            root2["avatar"] = user._avatar;
            root2["password"] = user._password;
            root2["nickName"] = user._nickName;
            root2["role"] = user._role;
            root2["phone"] = user._phone;
            Json::FastWriter w;
            return w.write(root2);
        }
    }
    string UpdatePersonalBaseInformation(const Json::Value& root)
    {
        User tmp;
        tmp._userId = root["userId"].asInt();
        tmp._userName = root["userName"].asString();
        tmp._password = root["password"].asString();
        tmp._phone = root["phone"].asString();
        tmp._nickName = root["nickName"].asString();
        tmp._role = Role(root["role"].asInt());
        tmp._avatar = root["avatar"].asString();
        bool flag = userHandle.updateBase(tmp);
        if(flag == false) cerr << "更新个人基本信息失败" << endl;
        Json::FastWriter w;
        return w.write(root);    
    }
    string GetPersonalAllInformation(const Json::Value& root)
    {
        string userName = root["userName"].asString();
        Role role = Role(root["role"].asInt());
        Json::Value root2;
        Json::FastWriter fwrite;
        if(role == Role::Writer)
        {
            struct Writer w = writerHandle.searchByUserName(userName);
            root2["writerId"] = w._userId;
            root2["userName"] = w._userName;
            root2["avatar"] = w._avatar;
            root2["password"] = w._password;
            root2["nickName"] = w._nickName;
            root2["role"] = w._role;
            root2["phone"] = w._phone;
            root2["manuscriptNumber"] = w._manuscriptNumber;
            return fwrite.write(root2);
        }
        else if(role == Role::Admin)
        {
            struct Admin admin = adminHandle.searchByUserName(userName);
            root2["adminId"] = admin._userId;
            root2["userName"] = admin._userName;
            root2["avatar"] = admin._avatar;
            root2["password"] = admin._password;
            root2["nickName"] = admin._nickName;
            root2["role"] = admin._role;
            root2["phone"] = admin._phone;
            return fwrite.write(root2);
        }
        else if(role == Role::Assessor)
        {
            struct Assessor assessor = assessorHandle.searchByUserName(userName);
            root2["adminId"] = assessor._userId;
            root2["userName"] = assessor._userName;
            root2["avatar"] = assessor._avatar;
            root2["password"] = assessor._password;
            root2["nickName"] = assessor._nickName;
            root2["role"] = assessor._role;
            root2["phone"] = assessor._phone;
            root2["applicationTime"] = assessor._applicationTime;
            root2["description"] = assessor._description;
            root2["status"] = assessor._status;
            root2["categoryId"] = assessor._categoryId;
            root2["pendingAudit"] = assessor._pendingAudit;
            return fwrite.write(root2);
        }
    }
    string GetAllNotice()
    {
        vector<Notice> ret = noticeHandle.searchAll();
        return "";
    }
    string GetAllCategory()
    {
        vector<Category> ret = categoryHandle.searchAll();
        return "";
    }
};