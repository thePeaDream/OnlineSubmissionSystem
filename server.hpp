#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
class TcpServer{
private:
    int _listenSock;
    int _port;
public:
    TcpServer(uint16_t port = 8080);
    ~TcpServer();
    void start();
    //处理客户端的请求
    void handle(const char* buffer);
};
TcpServer::TcpServer(uint16_t port = 8080)
:_port(port)
,_listenSock(-1)
{
    //1 创建套接字
    _listenSock = socket(PF_INET,SOCK_STREAM,0);
    //2 绑定套接字 ip和port 服务器采用绑定任意ip
    struct sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = 0;
    if(bind(_listenSock,(struct sockaddr*)&addr,sizeof(addr)) == -1)
    {
        cerr << "bind error" << endl;
        exit(1);
    }
    //3 把套接字设置为监听状态，等待连接
    if(listen(_listenSock,5) == -1)
    {
        cerr << "set listen error" << endl;
        exit(2);
    }
}
TcpServer::~TcpServer()
{
    if(_listenSock >= 0)
        close(_listenSock);
}
void TcpServer::start()
{
    //4 获取客户端连接
    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    while(true)
    {
        int sock = accept(_listenSock,(struct sockaddr*)&clientAddr,&len);
        if(sock == -1){
            cerr << "获取客户端连接发生异常"<<endl;
            continue;
        }
        pid_t id = fork();
        if(id == 0)
        {
            if(fork() > 0) exit(0);
            //孙子进程
            while(true)
            {
                //5 读取客户端的发来的请求
                char buffer[1024];
                ssize_t s = read(sock,buffer,sizeof(buffer)-1);
                buffer[s] = '\0';

                //6 处理客户端的请求
                handle(buffer);
            }
            exit(0);
        }
        close(sock);
        waitpid(id,nullptr,0);
    }
}
void TcpServer::handle(const char* buffer)
{
    //通用
    //1 登录
    //2 注册
    //3 修改个人信息
    //4 获取个人信息
    //5 获取系统通知列表
    
    //用户
    //1 获取个人历史稿件
    //2 提交稿件
    //3 删除稿件
    //4 修改历史稿件

    //审核
    //1 获取稿件列表(几乎所有作者的稿件)
    //2 修改稿件状态
    
    //管理员
    //1 添加系统通知
    //
    //2 获取用户列表
    //3 删除用户
    //4 根据userName查找某个用户
    //
    //5 获取审核列表
    //6 删除审核
    //7 添加审核 
}

