#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string>
#include <thread>
#include "../tcp_utils.h"

using namespace std;
 
class Server{
    unsigned int port;
    unsigned int backlog;
    struct sockaddr_in server_socket;
    struct sockaddr_in from_socket;
    int socket_descriptor;
    static void handle_connection(int client_file_descriptor);
    virtual void create_client_thread(int client_file_descriptor) = 0;
public:
    Server(unsigned int port, unsigned int backlog);
    unsigned int get_port();
    unsigned int get_backlog();
    void start();
    void stop();
};
#endif // SERVER_H