//#include "mysql/Person.hpp"
#include "HttpServer.hpp"
#include <memory>
#include "./mysql/SQLConnect.hpp"
#include <signal.h>
#include "Daemon.hpp"

SQLConnect sqlConnect = SQLConnect::GetInstance();

static void Usage(char* proc)
{
    cerr << "Usage:" << proc << " port" << endl;
}
int main(int argc, char* argv[])
{
    if(argc != 2){
        Usage(argv[0]);
        exit(1);
    }
    signal(SIGPIPE,SIG_IGN);
    //MyDaemon();
    std::unique_ptr<HttpServer> server(new HttpServer((uint16_t)atoi(argv[1])));
    server->start();
    return 0;
}