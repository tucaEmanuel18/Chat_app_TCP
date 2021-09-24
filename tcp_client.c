#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int port;
extern int errno;

int main(int argc, char* argv[]){
    int sd; // descriptorul de socket
    struct sockaddr_in server; // structura folosita pentru conectarea la adresa serverului
    char msg[100]; // mesajul trimis

    // exista toate argumentele in linia de comanda?
    if(argc != 3){
        printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    // stabilim portul
    port = atoi(argv[2]);

    // cream socketul
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("Eroare la socket().\n");
        return errno;
    }

    // completam cu date structura de conectare la server
    // 1. Setam familia socketului
    server.sin_family = AF_INET;
    // 2. Setam adresa IP a serverului
    server.sin_addr.s_addr = inet_addr(argv[1]);
    //  3. Setam portul de conectare
    server.sin_port = htons(port);

    // ne conectam la server
    if(connect(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
        perror("[Client] Eroare la conectarea la server");
        return errno;
    }

    // citirea mesajului
    bzero(msg, 100);
    printf("[Client] Introduceti un nume: ");
    fflush(stdout);

    read(0, msg, 100);

    //trimiterea mesajului la server
    if(write(sd, msg, 100) <= 0){
        perror("[Client] Eroare la write() spre server. \n");
        return errno;
    }

    // citirea rapsunsului dat de server
    // (apel blocant pana cand serverul raspunde)
    if( read(sd, msg, 100) < 0){
        perror("[Client] Eroare la read() de la server!");
        return errno;
    }

    // afisam mesajul primit
    printf("[Client] Mesajul primit este: %s\n", msg);

    // inchidem conexiunea, am terminat
    close(sd);
}   