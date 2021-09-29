#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "../tcp_utils.h"

int port;

int main(int argc, char* argv[]){
    int socket_descriptor; 
    struct sockaddr_in client_socket; 
    char msg[100];

    // check the arguments
    if(argc != 3){
        printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    port = atoi(argv[2]);
    // creating a new socket
    TCP_utils::check((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)), "Error at socket()");
    // preparing data structures
    client_socket.sin_family = AF_INET;
    client_socket.sin_addr.s_addr = inet_addr(argv[1]);
    client_socket.sin_port = htons(port);

    // connecting to the server
    TCP_utils::check(
        connect(socket_descriptor, (struct sockaddr *) &client_socket, sizeof(struct sockaddr)), 
        "Error at connect()");

    // getting the client message
    bzero(msg, 100);
    printf("[Client] Introduceti un nume: ");
    fflush(stdout);
    read(0, msg, 100);

    //Sending the message to the server
    TCP_utils::send(socket_descriptor, msg);

    // Receiving the message from the server
    TCP_utils::receive(socket_descriptor);
    // printing the received message
    printf("[Client] Mesajul primit este: %s\n", msg);

    // closing the connection
    close(socket_descriptor);
}   