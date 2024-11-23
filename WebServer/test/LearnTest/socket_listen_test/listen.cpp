#include <csignal>
#include <cassert>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

static bool stop = false;

static void handle_term(int sig){
    stop = true;
}
int main(int argc, char* argv[]){
    //处理信号
    signal(SIGTERM, handle_term);
    //处理入参
    assert(argc == 4);
    const char* ip = argv[1];//服务器ip
    int port = std::stoi(argv[2]);//服务器监听端口
    int backlog = std::stoi(argv[3]);//服务器监听队列长度

    int socketFd = socket(PF_INET, SOCK_STREAM, 0);//<sys/socket.h>，创建socket
    assert(socketFd >= 0);

    struct sockaddr_in address;//netinet/in.h 服务器监听地址，且采用ipv4
    bzero(&address, sizeof(address));//<strings.h> 地址刷为0
    address.sin_family = AF_INET; //设置服务器的地址协议簇
    address.sin_port = htons(port);//netinet/in.h 设置服务器的监听端口
    int inet_pton_ret = inet_pton(AF_INET, ip, &address.sin_addr.s_addr);//arpa/inet.h 设置，把可读ip地址转为网络字节序地址并且放置到ipv4地址结构中
    assert(inet_pton_ret == 1);



    int bindRet = bind(socketFd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address));//命名socket地址
    assert(bindRet == 0);

    int listenRet = listen(socketFd, backlog);//开启监听
    assert(listenRet == 0);

    while(!stop){
        sleep(1);
    }
    close(socketFd);
    return 0;
}