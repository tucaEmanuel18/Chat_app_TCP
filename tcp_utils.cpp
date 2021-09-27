#include "tcp_utils.h"

using namespace std;

void TCP_utils::check(int operationResult, string message, bool with_exit){
    if(operationResult < 0){
        perror(message.c_str());
        if(with_exit){
            exit(errno);
        }
    }
}

void TCP_utils::send(unsigned int file_descriptor, string message){
    int length = message.size();
    check(write(file_descriptor, &length, sizeof(int)), 
        "Error at sending length of message!");

    check(write(file_descriptor, message.c_str(), message.size()),
         "Error at sending message!");
}

string TCP_utils::receive(unsigned int file_descriptor){
    int length;
    check(read(file_descriptor, &length, sizeof(int)), 
        "Error at receiving the length of message");

    char* buffer = new char[length];
    check(
        read(file_descriptor, buffer, length),
        "Error at reading the message"
    );

    buffer[length] = '\n';
    string message = "";
    return message + buffer;
}