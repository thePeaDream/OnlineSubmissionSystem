#pragma once
#include <iostream>
#include <string>
#include "SearchFlag.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
struct Notice
{
public:
    int _noticeId;
    string _publishTime;
    string _latestTime;
    string _title;
    string _content;
    SearchFlag _flag = SearchFlag::FIND;//数据库中查找完成，标识查找结果的标志位,默认FIND
public:
    Notice(){}
    Notice(int noticeId,const string& publishTime,const string& latestTime,const string& title,const string& content)
    :_noticeId(noticeId)
    ,_publishTime(publishTime)
    ,_latestTime(latestTime)
    ,_title(title)
    ,_content(content)
    {}
};

