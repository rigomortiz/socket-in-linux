//
// Created by regoeco on 15/02/17.
//

#ifndef SOCKET_IN_LINUX_SERVER_H
#define SOCKET_IN_LINUX_SERVER_H
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
typedef struct Server{
    struct sockaddr_in dest;
    int socket;

    void(*set_sockaddr)(struct Server *this, struct sockaddr_in sockaddr_in1);
    struct sockaddr_in(*get_sockaddr)(struct Server *this);
    void(*set_socket)(struct Server *this, int server);
    int(*get_socket)(struct Server* this);

    int (*listen)(struct Server* this);
    void (*run)(struct Server* this);
}Server;

Server* newServer();
static void _set_sockaddr_in_server(Server *this, struct sockaddr_in sockaddr_in1);
static struct sockaddr_in new_sockaddr_server();
static int _get_socket_server(Server *this);
static void _set_socket_server(Server *this, int socket);
static struct sockaddr_in _get_sockaddr_server(Server *this);
static int _listen_server(Server* this);
static void _run_server(Server* this);

#endif //SOCKET_IN_LINUX_SERVER_H
