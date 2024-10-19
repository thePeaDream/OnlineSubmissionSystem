#pragma once
#include "User.hpp"
//作者
struct Writer:public User
{
public:
    int _manuscriptNumber;//稿件数目
public:
    Writer(){}
    Writer(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone,int manuscriptNumber)
    :_manuscriptNumber(manuscriptNumber)
    ,User(userId,role,nickName,userName,password,avatar,phone)
    {}
};