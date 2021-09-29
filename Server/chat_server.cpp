#include "chat_server.h"

Chat_Server::Chat_Server(unsigned int port, unsigned int backlog) : Server(port, backlog){
}

void Chat_Server::create_client_thread(int client){
    new thread(handle_connection, client);
}

void Chat_Server::handle_connection(int client){
    string prefix = "[Server -> Client " + to_string(client) + "]";

    printf("%s Waiting the message ... \n", prefix.c_str());
    fflush(stdout);

    string msg = TCP_utils::receive(client);
    printf("%s The received message: %s", prefix.c_str(), msg.c_str());

    // the connection should be closed

    //prepare the response message
    string msg_rasp = "Hello " + msg;
    TCP_utils::send(client, msg_rasp);
    printf("%s The following message was send: %s\n", prefix.c_str(), msg_rasp.c_str());

    // close the connection
    close(client);
}