#pragma once
#include <jsoncpp/json/json.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Sock.hpp"
#include "AdminService.hpp"
#include "AssessorService.hpp"
#include "WriterService.hpp"
#include "CommonService.hpp"
#include <math.h>
#include <mutex>
#include <thread>
#include <set>
#include <time.h>
#include <stdlib.h>

//预检请求（preflight request）是一种特殊的 HTTP 请求
//通常由浏览器在发送实际的跨域请求之前自动发送。预检请求使用 OPTIONS 方法。
#define ROOT "./wwwroot"

#define MAX_NUM 1000000
#define CODE_SIZE 14
using std::set;
using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;
class HttpServer
{
private:
    Sock _sock;
    int _listenSock;
    uint16_t _port;
    std::set<string> _code;
    std::mutex _mtx;
public:
    HttpServer(uint16_t port = 8080);
    ~HttpServer();
    void start();
    //由线程来处理Http
    void HandleHttp(int serviceSock);
    // 获取整个http请求
    string GetHttpRequest(int sock);
    // 处理客户端的某个url请求,处理完成后返回 要回复的正文数据(用json格式)
    string HandleRequest(const string &url, const string &json, const string& code);
    //处理预检请求
    void HandleOption(int sock);
    // 给客户端回复HTTP报文
    void HandleResponse(const string &json, int ,const string&code);
    string extractMethod(const string& httpReq);//提取请求方法
    string extractURL(const string &httpReq);  // 提取URL
    string extractJSON(const string &httpReq); // 提取正文里的JSON数据
    string extractAuthorization(const string &httpReq); // 提取Http请求的校验码，用于身份认证,无校验码只能进行登录注册，如果没有登录该校验码无效
    
    // 访问这个set时，需要加锁
    bool validate(const string& code); // 查看当前检验码是否有效
    string generateCode();      // 生成当前系统里唯一标识已登录客户端的校验码
    void freeCode(const string& code);// 释放校验码
};

HttpServer::HttpServer(uint16_t port = 8080)
    : _port(port), _listenSock(-1)
{
    // 1 创建套接字
    _listenSock = _sock.Socket();
    // 设置端口复用
    int opt = 1;
    int ret = setsockopt(_listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (ret == 0)
    {
        cout << "设置端口复用成功" << endl;
    }
    // 2 绑定套接字
    _sock.Bind(_listenSock, _port);
    // 3 把套接字设置为监听状态，等待连接
    _sock.Listen(_listenSock);
}
HttpServer::~HttpServer()
{
    if(_listenSock >= 0)
        close(_listenSock);
}
void HttpServer::start()
{
    while (true)
    {
        // 4 获取客户端连接
        std::string clientIp;
        uint16_t clientPort;
        int serviceSock = _sock.Accept(_listenSock, &clientIp, &clientPort);
        if (serviceSock < 0)
        {
            cerr << "服务套接字获取失败"<<endl;
            continue;
        }
        cerr << "获取客户端连接成功!!!"<<endl;
        std::thread t(&HttpServer::HandleHttp,this,serviceSock);
        t.detach();//线程分离，由os回收线程资源
    }
}
void HttpServer::HandleHttp(int serviceSock)
{
    cerr << "开始处理Http请求"<<endl;
    // 获取整个http请求报文
    string req = GetHttpRequest(serviceSock);
    cerr << "成功获取Http请求全部报文"<<endl;
    
    // 提取出正文、请求报头中的url、身份验证Authorization:Bearer your_token_here
    string method = extractMethod(req);

    cerr << method << endl;
    if(method == "OPTIONS")
    {
        cerr << "处理预检请求"<<endl;
        HandleOption(serviceSock);
    }
    else{
        string url = extractURL(req);
        string json = extractJSON(req);
        string code = extractAuthorization(req);
        
        // 处理请求
        string res = HandleRequest(url, json, code);
        cerr << "请求处理完成"<<endl;
        
        // 回复客户端
        HandleResponse(res, serviceSock,code);
        cerr << "已经给客户端回应"<<endl;
    }
    cerr << "本次Http请求处理完成" << endl;
    close(serviceSock);
}
void HttpServer::HandleOption(int sock)
{
    string httpResponse = "HTTP/1.1 200 OK\r\n";
    httpResponse += "Access-Control-Allow-Origin:*\r\n";
    httpResponse += "Access-Control-Allow-Methods:GET,POST,DELETE,OPTIONS\r\n";
    httpResponse += "Access-Control-Allow-Credentials:true\r\n";
    httpResponse += "Access-Control-Allow-Headers:content-type\r\n";
    httpResponse += "\r\n";
    send(sock,httpResponse.c_str(),httpResponse.size(),0);
    cerr << "已经回应预检请求"<<endl;
}
string HttpServer::GetHttpRequest(int sock)
{
    char buffer[10240];
    ssize_t s = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[s] = '\0';
    string ret(buffer);
    return ret;
}

string HttpServer::extractMethod(const string& httpReq)//提取请求方法
{
    size_t pos = httpReq.find(" ");   
    string method = httpReq.substr(0,pos);
    return method;
}
string HttpServer::extractURL(const string &httpReq) //提取URL
{
    size_t pos = httpReq.find(" ");
    pos += 1;
    size_t endPos = httpReq.find(" ",pos);
    string url = httpReq.substr(pos,endPos-pos);
    return url;
}
string HttpServer::extractJSON(const string &httpReq) // 提取正文里的JSON数据
{
    // 找到描述正文长度报头的位置
    size_t pos = httpReq.find("Content-Length: ", 0);
    if (pos == string::npos)
        return "";
    // 移动到长度值的开始位置
    pos += strlen("Content-Length: ");
    size_t endPos = httpReq.find("\r\n", pos);
    string lengthStr = httpReq.substr(pos, endPos - pos);

    size_t contentLength = atoi(lengthStr.c_str());
    // 找到正文起始位置
    size_t bodyStart = httpReq.find("\r\n\r\n");
    if (bodyStart == string::npos)
        return "";
    bodyStart += 4;
    string content = httpReq.substr(bodyStart, contentLength);
    return content;
}
string HttpServer::extractAuthorization(const string &httpReq) // 提取校验码，用于身份认证,无校验码只能进行登录注册，如果没有登录该校验码无效
{
    size_t pos = httpReq.find("Authorization:",0);
    if(pos == string::npos){
        return "";
    }
    pos += strlen("Authorization: ");
    size_t endpos = httpReq.find("\r\n",pos);
    string codeString = httpReq.substr(pos,endpos-pos);
    return codeString;
}
bool HttpServer::validate(const string& code) // 查看当前检验码是否有效
{
    _mtx.lock();
    bool ret = (_code.find(code) != _code.end());
    _mtx.unlock();
    return ret;
}
string HttpServer::generateCode() // 生成当前系统里唯一标识已登录客户端的校验码
{
    const string characters =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                               "abcdefghijklmnopqrstuvwxyz"
                                "0123456789";
    srand(time(nullptr));
    //如果生成了set中没有的字符串，插入并返回
    //否则重新生成
    string ret;
    ret.resize(CODE_SIZE);
    while(true)
    {
        for(size_t i = 0; i < CODE_SIZE; ++i)
            ret[i] = characters[rand()%characters.size()];
        _mtx.lock();
        if(_code.find(ret) == _code.end())
        {
            _code.insert(ret);
            _mtx.unlock();
            break;
        }
    }
    return ret;
}
void HttpServer::freeCode(const string& code)
{
    _mtx.lock();
    if(_code.find(code) != _code.end())
    {
        _code.erase(code);
    }
    _mtx.unlock();
}

string HttpServer::HandleRequest(const string &url, const string &json, const string& code)
{
    AssessorService assessorService;
    AdminService adminService;
    WriterService writerService;
    CommonService commonService;
    
    Json::Value root;
    Json::Reader reader;
    //解析字符串json到root1中
    reader.parse(json, root);

    //通用
    if(url == "/login")//登录
    {
        return commonService.Login(root);
    }
    else if(url == "/getPersonalAllInformation")//查看个人全部信息
    {
        return commonService.GetPersonalAllInformation(root);
    }
    else if(url == "/updatePersonalBaseInformation")//修改/更新个人基本信息
    {
        return commonService.UpdatePersonalBaseInformation(root);
    }
    else if(url == "/getAllNotice")//查看所有通知
    {
        return commonService.GetAllNotice();
    }
    else if(url == "/getAllCategory")//获取所有稿件类别名
    {
        return commonService.GetAllCategory();
    }
    
    //作者
    if(url == "/register")//注册
    {
       return writerService.Register(root);
    }
    else if(url == "/getAllPersonalManuscript")//查看个人所有稿件
    {
        return writerService.GetAllPersonalManuscript(root);
    }
    else if(url == "/submitPersonManuscript")//提交个人稿件
    {
        return writerService.SubmitPersonalManuscript(root);
    }
    else if(url == "/removePersonManuscript")//删除个人稿件
    {
        return writerService.RemovePersonalManuscript(root);
    }
    else if(url == "/getAllPublishManuscript")//查看所有公开的稿件
    {
        return writerService.GetAllPublishManuscript(root);
    }
    else if(url == "/updatePersonalManuscript")//更新/修改个人稿件
    {
        return writerService.UpdatePersonalManuscript(root);
    }

    //审核员
    if(url == "/getAuditManuscript")//获取本人所有要审核的稿件
    {
        return assessorService.GetAuditManuscript(root);
    }
    else if(url == "/setManuscriptStatus")//设置稿件状态,包括稿件评价/稿件状态
    {
        return assessorService.SetManuscriptState(root);
    }
    else if(url == "/applicationAssessor")//申请成为审稿人
    {
       return assessorService.applicationAssessor(root);
    }

    //管理员
    if(url == "/addNotice")// 添加通知
    {
        return adminService.AddNotice(root);
    }
    else if(url == "/removeNotice")// 删除通知
    {
        return adminService.RemoveNotice(root);
    }
    else if(url == "/updateNotice")//修改通知
    {
        return adminService.UpdateNotice(root);
    }
    else if(url == "/getAllWriter")// 获取所有作者信息
    {
        return adminService.GetAllWriter();
    }
    else if(url == "/removeWriter")// 手动删除作者
    {
        return adminService.RemoveWriter(root);
    }
    else if(url == "/getAllAssessor")// 获取所有审核员信息
    {
        return adminService.GetAllAssessor();
    }
    else if(url == "/setAssessorStatus")//修改审核员的申请状态
    {
        return adminService.SetAssessorStatus(root);
    }
    else if(url == "/removeAssessor")//删除审核员
    {
        return adminService.RemoveAssessor(root);
    }
    else if(url == "/getAllManuscript")//获取所有稿件
    {
        return adminService.GetAllManuscript();
    }
    else if(url == "/assignAssessor")//为稿件分配审核员
    {
        return adminService.AssignAssessor(root);
    }
    //服务不存在 404
    return "";    
}
// 给客户端回复HTTP报文
void HttpServer::HandleResponse(const string &json, int sock,const string&code)
{
    //cerr << "开始回复客户端" << sock <<endl;
    string httpResponse;
    httpResponse += "HTTP/1.1 200 OK\r\n";
    //cerr << "请求行构建完成" << endl;
    httpResponse += "Access-Control-Allow-Origin:*\r\n";
    //指定内容类型json
    httpResponse += "Content-Type:application/json\r\n";

    //正文部分的长度/字节数
    httpResponse += "Content-Length:";
    int length = (int)json.size();
    httpResponse += std::to_string(length); 
    httpResponse += "\r\n";
    
    //检验码
    httpResponse += ("Authorization:"+ code + "\r\n");
    httpResponse += "\r\n";
    httpResponse += json;
    //cerr << "httpResponse构建完成"<<endl;
    ssize_t s = send(sock,httpResponse.c_str(),httpResponse.size(),0);
    if(s > 0)
    {
        cerr << "发送成功"<<endl;
    }
}
