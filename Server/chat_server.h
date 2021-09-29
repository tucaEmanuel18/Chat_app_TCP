#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include "abstract_server.h"
#include <string>

using namespace std;
class Chat_Server : public Server{
static void handle_connection(int client_file_descriptor);
virtual void create_client_thread(int client_file_descriptor);
public:
    Chat_Server(unsigned int port, unsigned int backlog);

};

#endif // CHAT_SERVER_H