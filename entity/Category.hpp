#pragma once
#include <iostream>
#include <string>
#include "SearchFlag.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
struct Category{
public:
    int _categoryId;
    string _name;
    SearchFlag _flag=SearchFlag::FIND;//数据库中查找完成，标识查找结果的标志位，默认FIND
public:
    Category(){}
    Category(int categoryId,const string& name)
    :_categoryId(categoryId)
    ,_name(name)
    {}
};