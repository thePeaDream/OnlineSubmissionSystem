#pragma once
#include <iostream>
#include <string>
#include "SearchFlag.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
enum Role{
    Erro,//0 占位
    Writer, //1
    Assessor, //2
    Admin,  //3
};
struct User
{
public:
    int _userId;
    Role _role;//角色
    string _nickName;//昵称
    string _userName;//用户名
    string _password;//密码
    string _avatar;//头像所在服务器路径
    string _phone;//电话
    SearchFlag _flag = SearchFlag::FIND;//数据库中查找完成，标识查找结果的标志位，默认FIND
public:
    User(){}
    User(int userId,Role role,const string& nickName,const string& userName,const string& password,const string& avatar,const string& phone)
    :_userId(userId)
    ,_role(role)
    ,_nickName(nickName)
    ,_userName(userName)
    ,_password(password)
    ,_avatar(avatar)
    ,_phone(phone)
    {}
};












