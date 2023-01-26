#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include "client.h"


Client* newClient(const char* dir, const char* port){
    Client *client = malloc(sizeof(Client));
    client->dest = new_sockaddr_client(dir, port);
    client->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client->socket == -1){
        perror("SOCKET");
        abort();
    }else{
        client->connect = _connect_client;
    }
    return client;
}

static struct sockaddr_in new_sockaddr_client(const char* dir, const char* port ){
    struct sockaddr_in dest;//estructura
    dest.sin_family = AF_INET; //red
    dest.sin_port =  htons((uint16_t) atoi(port)); //puerto
    inet_aton(dir, &(dest.sin_addr)); //direccion remota
    memset(&(dest.sin_zero), '\0', 8);

    return dest;
}

static void _connect_client(Client* this){
    char buffer[255];
    //CONNEXION WITH HOST
    socklen_t size = sizeof(struct sockaddr);
    int c = connect(this->socket, (struct sockaddr *) &(this->dest), size);
    if( c != 0){
        perror("CONNECT");
        abort();
    }
    ssize_t num_bytes = recv(this->socket, buffer, 254, 0);
    buffer[num_bytes]='\0';
    printf("%s", buffer);
    printf("Bytes recibidos:%zi\n", num_bytes);
    close(this->socket);
}