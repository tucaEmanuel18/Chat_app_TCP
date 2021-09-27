#ifndef TCP_UTILS_H
#define TCP_UTILS_H

#include <string>
#include <unistd.h>
#include <stdio.h>

using namespace std;
class TCP_utils{
public:
    static void check(int operationResult, string message, bool with_exit = true);
    static void send(unsigned int file_descriptor, string message);
    static string receive(unsigned int fd);
};

#endif // TCP_UTILS_H