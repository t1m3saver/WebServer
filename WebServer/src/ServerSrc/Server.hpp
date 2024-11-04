#include "../LogSystem/LoggerItf.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace WebServer::Server {
    
class ServerInterface{
public:
    ServerInterface() = delete;
    virtual ~ServerInterface() = default;

    virtual void StartServer() = 0;
    virtual void StopServer() = 0;
private:
    virtual int MakeSocket(int domain, int type, int protocal) = 0;
    virtual int BindSocket(int socket, struct sockaddr* myaddr, socklen_t addrlen) = 0;
    virtual int ListenSocket(int socket, int backlog) = 0;
    virtual int AcceptSocket(int sockfd, struct sockaddr* addr, socklen_t* addrlen) = 0;
};

class GeneralServer : public ServerInterface {
public:
    GeneralServer() = default;
    ~GeneralServer() override = default;

    void StartServer() override;
    void StopServer() override;
private:
    int MakeSocket(int domain, int type, int protocal) override;
    int BindSocket(int socket, struct sockaddr* myaddr, socklen_t addrlen) override;
    int ListenSocket(int socket, int backlog) override;
    int AcceptSocket(int sockfd, struct sockaddr* addr, socklen_t* addrlen) override;
    bool initLog();
private:
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;
    int server_sock;
    WebServer::Log::FileLogger fileLog;
};
}//namespace WebServer::Server
