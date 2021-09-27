#include "chat_server.h"

int main(){
    unsigned int PORT = 3705;
    unsigned int BACKLOG = 5;
    Chat_Server server(PORT, BACKLOG);
    server.start();
}