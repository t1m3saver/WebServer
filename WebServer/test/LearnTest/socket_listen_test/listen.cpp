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

    while(!stop){
        sleep(1);
    }
    close(socketFd);
    return 0;
}