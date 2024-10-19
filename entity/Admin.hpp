#pragma once
#include "User.hpp"
//管理员
struct Admin:public User
{
public:
    Admin(){}
    Admin(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone)
    :User(userId,role,nickName,userName,password,avatar,phone)
    {}
};
