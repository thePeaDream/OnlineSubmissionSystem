#pragma once
#include <iostream>
#include <string>
#include "SearchFlag.hpp"
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
enum ManuscriptStatus
{
    Err,
    Publish,// 1 已公开 2 已驳回 3 审核中
    Rejected,
    UnderReview
};
struct Manuscript
{
public:
    int _manuscriptId;
    string _description;//稿件描述或摘要
    string _submitTime;//稿件提交时间
    string _latestTime;//最新修改时间
    string _comment;//审核回复消息
    string _name;//稿件名
    string _path;//稿件所在服务器位置
    int _size;//稿件大小
    int _categoryId;//稿件类型
    ManuscriptStatus _status;//稿件状态
    int _writerId;//稿件作者
    int _assessorId;//该稿件的审核员
    SearchFlag _flag = SearchFlag::FIND;//数据库中查找完成，标识查找结果的标志位，默认FIND
public:
    Manuscript(){}
    Manuscript( int manuscriptId,const string& description,const string& submitTime,const string& latestTime,const string& comment,
                const string& name,const string& path,int size,int categoryId,ManuscriptStatus status,int writerId,int assessorId)
    :_manuscriptId(manuscriptId)
    ,_description(description)
    ,_submitTime(submitTime)
    ,_latestTime(latestTime)
    ,_comment(comment)
    ,_name(name)
    ,_path(path)
    ,_size(size)
    ,_categoryId(categoryId)
    ,_status(status)
    ,_writerId(writerId)
    ,_assessorId(assessorId)
    {}
};

