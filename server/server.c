//
// Created by regoeco on 15/02/17.
//
#include <stdlib.h>
#include "server.h"

Server* newServer(){
    Server *server = malloc(sizeof(Server));
    server->dest = new_sockaddr_server();
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server->socket == -1){
        perror("SOCKET");
        abort();
    }else {
        bind(server->socket, (const struct sockaddr *) &(server->dest), sizeof(struct sockaddr));
        char str_addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(server->dest.sin_addr), str_addr, INET_ADDRSTRLEN);    // now get it back and print it
        printf("Init: %s:%d", str_addr, server->dest.sin_port);


        server->get_sockaddr = _get_sockaddr_server;
        server->set_sockaddr = _set_sockaddr_in_server;
        server->get_socket = _get_socket_server;
        server->set_socket = _set_socket_server;
        server->listen = _listen_server;
        server->run = _run_server;
    }

    return server;
}

struct sockaddr_in _get_sockaddr_server(Server *this){
    return this->dest;
}

void _set_sockaddr_in_server(Server *this, struct sockaddr_in sockaddr_in1){
    this->dest = sockaddr_in1;
}

struct sockaddr_in new_sockaddr_server(){
    struct sockaddr_in dest = {
            .sin_addr.s_addr = INADDR_ANY,
            .sin_family = AF_INET, //RED
            .sin_port = htons(7777) //PORT
    };
    //inet_aton("127.0.0.1", &(dest.sin_addr)); //direccion remota
    memset(&(dest.sin_zero), '\0', 8);

    return dest;
}

int _get_socket_server(Server* this){
    return this->socket;
}

void _set_socket_server(Server *this, int socket){
    this->socket = socket;
}

int _listen_server(Server* this){
    return listen(this->socket, 5);
}

void _run_server(Server* this){
    int nuevo;
    socklen_t size = sizeof(struct sockaddr);
    time_t t;
    struct tm tm;
    char str_time[255];
    while (1) {
        nuevo = accept(this->socket, (struct sockaddr *) &(this->dest), &size);
        if(nuevo == -1){
            perror("ACCEPT");
            abort();
        }
        if (fork() == 0) {
            close(this->socket);
            t = time(NULL);
            tm = *localtime(&t);
            sprintf(str_time, "SERVER_MIN TIME: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            send(nuevo, str_time, strlen(str_time), 0);
            close(nuevo);
            exit(0);
        } else {
            close(nuevo);
        }
    }
}