//
// Created by regoeco on 14/01/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "server.h"


int main() {
    Server *server = newServer();
    int lis = server->listen(server);
    if(lis == -1){
        perror("LISTEN");
        abort();
    }else{
        server->run(server);
    }

    return EXIT_SUCCESS;
}