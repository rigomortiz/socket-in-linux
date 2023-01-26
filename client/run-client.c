//
// Created by regoeco on 15/02/17.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
int main(int argc, char* argv[]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("CLIENT_MIN TIME: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    Client *client = newClient("0.0.0.0", "7777");
    client->connect(client);

    free(client);
    return EXIT_SUCCESS;
}