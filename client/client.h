//
// Created by regoeco on 15/02/17.
//

#ifndef SOCKET_IN_LINUX_CLIENT_H
#define SOCKET_IN_LINUX_CLIENT_H
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <time.h>
typedef struct Client{
    struct sockaddr_in dest;
    int socket;
    void(*connect)(struct Client* this);
}Client;

Client* newClient(const char* dir, const char* port);
static struct sockaddr_in new_sockaddr_client(const char* dir, const char* port );
static void _connect_client(Client* this);
#endif //SOCKET_IN_LINUX_CLIENT_H
