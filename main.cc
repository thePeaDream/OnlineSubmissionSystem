#include "mysql/Person.hpp"
#include "server.hpp"
#include <memory>
static void Usage(char* proc)
{
    cerr << "Usage:" << proc << " port";
}
int main(int argc, char* argv[])
{
    if(argc != 2){
        Usage(argv[0]);
        exit(1);
    }
    std::unique_ptr<TcpServer> server(new TcpServer(atoi(argv[1])));
    server->start();
    return 0;
}