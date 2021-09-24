#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 2021

extern int errno;

int main(){
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;

    char msg[100]; // mesaj primit de la client
    char msgrasp[100] = " "; // mesaj raspuns pentru client
    int sd; // socket descriptor (of server)

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("[Server] Eroare la socket(). \n");
        return errno;
    }

    /* pregatirea structurilor de date */
    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    // umplem structura folosita de server
    // 1. stabilim familia de socket-uri
    server.sin_family = AF_INET;
    // 2. acceptam orice adresa
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    // 3. setam portul ce va fi utilizat
    server.sin_port = htons(PORT);

    // atasam socketul la adresa
    if(bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1){
        perror("[Server] Eroare la bind(). \n");
        return errno;
    }

    // punem serverul sa asculte daca vin clienti sa se conecteze
    if(listen(sd, 5) == -1){
        perror("[server] Eroare la listen(). \n");
        return errno;
    }

    // servim in mod iterativ clientii
    while(1){
        int client;
        int length = sizeof(from);

        printf("[SERVER] Asteptam la portul %d ... \n", PORT);
        fflush(stdout);

        // accepta un client (stare clocanta pana la realizarea conexiunii) */
        client = accept(sd, (struct sockaddr * ) &from, &length);

        // eroare la acceptarea conexiunii de la un client
        if(client < 0){
            perror("[Server] Eroare la accept(). \n");
            continue;
        }

        // s-a realizat conexiunea, se asteapta mesajul
        printf("[Server] Asteptam mesajul ... \n ");
        fflush(stdout);

        // citirea mesajului
        bzero(msg, 100);
        if(read(client, msg, 100) <= 0){
            perror("[Server] Eroare la read() de la client. \n");
            close(client);
            continue;
        }

        printf("[Server Mesajul a fost receptionat: %s\n]", msg);
        
        //pregatirea mesajului de raspuns
        bzero(msgrasp, 100);
        strcat(msgrasp, "Hello ");
        strcat(msgrasp, msg);

        printf("[Server] Trimitem mesajul inapoi: %s\n", msgrasp);

        if( write(client, msgrasp, 100) <= 0){
            perror("[Server] Eroare la write() catre client");
            continue;
        }else{
            printf("[Server] Mesajul a fost transmis cu succes. \n");
            // am terminat cu acest client, inchidem conexiunea 
            close(client);
        }
    }
}   