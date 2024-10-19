#pragma once
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void MyDaemon()
{
    //1 忽略信号，SIGPIPE,SIGCHLD 不让我们的服务因为一些特殊信号终止了
    signal(SIGPIPE,SIG_IGN);
    signal(SIGCHLD,SIG_IGN);
    //2 不要让自己成为组长 父进程终止，只剩下子进程
    if(fork() > 0) exit(0);

    //3 调用setsid
    setsid();
    //4 标准输入、标准输出、标准错误的重定向
    int devnull = open("/dev/null",O_RDONLY|O_WRONLY);//类似于黑洞
    if(devnull > 0)
    {
        dup2(devnull,0);
        dup2(devnull,1);
        dup2(devnull,2);
        close(devnull);
    }
}