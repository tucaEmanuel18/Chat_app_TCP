#include "abstract_server.h"

using namespace std;

Server::Server(unsigned int port, unsigned int backlog){
    this->port = port;
    this->backlog = backlog;
}

unsigned int Server::get_port(){
    return this->port;
}

unsigned int Server::get_backlog(){
    return this->backlog;
}

void Server::start(){
    // create a new socket
    TCP_utils::check((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)),
        "[Server] Error at socket()");

    // set on the SO_REUSEADDR option
    int on = 1;
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    // preparing data structures
    bzero(&server_socket, sizeof(server_socket));
    bzero(&from_socket, sizeof(from_socket));

    this->server_socket.sin_family = AF_INET;
    this->server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server_socket.sin_port = htons(port);

    // binding the socket with the address
    TCP_utils::check(bind(socket_descriptor, (struct sockaddr *) &server_socket, sizeof(struct sockaddr)),
        "[Server] Error at bind()");

    // listening for new clients
    TCP_utils::check(listen(socket_descriptor, backlog), 
        "[Server] Error at listen()");

    while(1){
        int client;
        unsigned int length = sizeof(from_socket);

        printf("[Server] Listening at port: %d!\n", port);
        fflush(stdout);

        // accept a client
        TCP_utils::check( (client = accept(socket_descriptor, (struct sockaddr * ) &from_socket, &length)), 
            "[Server] Error at accept()", false);
        printf("[Server] Client with fd %d was connected\n", client);
        
        // create a new thread for this new client
        create_client_thread(client);
    }
}