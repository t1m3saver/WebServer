#include "Server.hpp"

namespace WebServer::Server{
    
void GeneralServer::StartServer() {
    
    server_sock = MakeSocket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (BindSocket(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed." << std::endl;
        close(server_sock);
        return;
    }

    if (ListenSocket(server_sock, 5) < 0) {
        std::cerr << "Listen failed." << std::endl;
        close(server_sock);
        return;
    }

    std::cout << "Server started, waiting for connections..." << std::endl;

    while (true) {
        client_addr_size = sizeof(client_addr);
        int client_sock = AcceptSocket(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
        if (client_sock < 0) {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }
        std::cout << "Connection accepted." << std::endl;
        // Handle client connection here
        close(client_sock);
    }
}

void GeneralServer::StopServer() {
    close(server_sock);
    std::cout << "Server stopped." << std::endl;
}

int GeneralServer::MakeSocket(int domain, int type, int protocol) {
    return socket(domain, type, protocol);
}

int GeneralServer::BindSocket(int sock, struct sockaddr* myaddr, socklen_t addrlen) {
    return bind(sock, myaddr, addrlen);
}

int GeneralServer::ListenSocket(int sock, int backlog) {
    return listen(sock, backlog);
}

int GeneralServer::AcceptSocket(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
    return accept(sockfd, addr, addrlen);
}
}