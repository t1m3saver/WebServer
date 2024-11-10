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
    signal(SIGTERM, handle_term);

    assert(argc == 4);
    const char* ip = argv[1];
    int port = std::stoi(argv[2]);
    int backlog = std::stoi(argv[3]);

    int socketFd = socket(PF_INET, SOCK_STREAM, 0);//<sys/socket.h>
    assert(socketFd >= 0);

    struct sockaddr_in address;//netinet/in.h
    bzero(&address, sizeof(address));//<strings.h>
    address.sin_family = AF_INET;
    address.sin_port = htons(port);//netinet/in.h
    int inet_pton_ret = inet_pton(AF_INET, ip, &address.sin_addr.s_addr);//arpa/inet.h
    assert(inet_pton_ret == 1);

    int bindRet = bind(socketFd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address));
    assert(bindRet == 0);

    int listenRet = listen(socketFd, backlog);
    assert(listenRet == 0);

    sleep(30);

    struct sockaddr_in address_client;
    socklen_t address_client_length = sizeof(address_client);
    int connectFd = accept(socketFd, reinterpret_cast<struct sockaddr*>(&address_client), &address_client_length);
    assert(connectFd != -1);
    char remoteIP[INET_ADDRSTRLEN];
    std::cout<<"client ip::"<<inet_ntop(AF_INET, &address_client.sin_addr, remoteIP, INET_ADDRSTRLEN)<<std::endl;
    std::cout<<"client port::"<<ntohs(address_client.sin_port)<<std::endl;
    close(connectFd);
    close(socketFd);
    return 0;
}