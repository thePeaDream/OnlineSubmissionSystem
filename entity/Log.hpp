#pragma once
#include <iostream>
#include <string>
#include "SearchFlag.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
class Log
{
private:
    int _logId;
    string _operate;
    string _operateTime;
    SearchFlag _flag = SearchFlag::FIND;//数据库中查找完成，标识查找结果的标志位，默认FIND
public:
    Log(){}
    Log(int logId,const string& operate,const string& operateTime)
    :_logId(logId)
    ,_operate(operate)
    ,_operateTime(operateTime)
    {}
};