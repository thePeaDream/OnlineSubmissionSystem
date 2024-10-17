#pragma once
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
class Sock{
public:
    Sock(){}
    int Socket()
    {
        int listenSock = socket(AF_INET,SOCK_STREAM,0);
        if(listenSock >= 0)
            cerr << "创建监听套接字成功"<<endl;
        else
        {
             cerr << "创建监听套接字失败"<<endl;
             exit(1);
        }
        return listenSock;
    }
    void Bind(int sock,uint16_t port)
    {
        int opt = 1;

        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
        {
            cerr << "绑定套接字失败" << endl;
            perror("bind error");
            exit(1);
        }
        cerr << "绑定套接字成功"<<endl;
    }
    void Listen(int sock)
    {
        if(listen(sock,gbacklog) < 0)
        {
            cerr << "设置套接字监听失败"<<endl;
            exit(1);
        }
        cerr << "设置套接字监听成功"<<endl;
    }
    //返回与对端通信的套接字
    int Accept(int listenSock,std::string *ip,uint16_t* port)
    {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        std::cerr << "正在等待连接"<<endl;
        int serviceSock = accept(listenSock,(struct sockaddr*)&client,&len);
        if(serviceSock < 0)
        {
            perror("获取客户端浏览器连接出错");
            return -1;
        }
        if(ip) *ip=inet_ntoa(client.sin_addr);
        if(port) *port = ntohs(client.sin_port);
        return serviceSock;        
    }
    bool Connect(int sock,const std::string& serverIp,uint16_t port)
    {
        struct sockaddr_in server;
        bzero(&server,sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(serverIp.c_str());
        server.sin_port = htons(port);
        if(connect(sock,(struct sockaddr*)&server,sizeof(server)) == 0) return true;
        return false;
    }
    ~Sock(){}
private:
    const static int gbacklog = 10;
};