#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
#include  <fcntl.h>
#include <zconf.h>

int main(){
    char msg_env[] = "hola\r\n";
    char msg_res[255];
    struct sockaddr_in dest;//estructura
    dest.sin_family = AF_INET; //red
    dest.sin_port = 0; // htons(0); //puerto
    dest.sin_addr.s_addr = INADDR_ANY;
    //inet_aton("127.0.0.1", &(dest.sin_addr)); //direccion remota
    memset(&(dest.sin_zero),'\0', 8);


    int s = socket(AF_INET, SOCK_STREAM, 0);

    bind(s, (struct sockaddr *) &dest, sizeof(struct sockaddr) );
    listen(s, 5);
    int nuevo;
    socklen_t size = sizeof(struct sockaddr);
    while(1){
        nuevo = accept(s, (struct sockaddr *) &dest, &size);
        if(fork() == 0){
            close(s);
            send(nuevo, "200: hi\n", 15, 0);
            close(nuevo);
            exit(0);
        }else{
            close(nuevo);
        }
    }


    //CONNEXION WITH HOST
    if(connect(s, (const struct sockaddr *) &dest, sizeof(struct sockaddr)) == 0){
        perror("Socket connection");
        abort();
    }

    ssize_t num_bytes = send(s, msg_env, strlen(msg_env), 0);
    if(num_bytes < 0){
        perror("NOT READ FAILED");
        abort();
    }
    printf("num_bytes:%zi", num_bytes);
    num_bytes = recv(s,msg_res, 254, 0);
    printf("num_bytes:%zi", num_bytes);



    //char * buffer;
    //int bytes_reads = recv(s, buffer, 10, 0);
    //if(bytes_reads < 0){
    //    perror("NOT READ FAILED");
    //    abort();
    //}

    // READ
    /*
    char Name[NAME], Address[ADDRESS], Phone[PHONE];
    FILE *f;
    if((f = fdopen(s, "r")) == NULL){
        perror("NOT CONVERSION FAILED");
        abort();
    }
    fclose(f);
    else if(fscanf(f, "%s, %s, %s\n","hello","hello1", "hello2") < 0){
        perror("NOT FSCANF");
        abort();
    }*/


}

void function_convert(){
// USE IPV4
    struct sockaddr_in antelope;
    char *some_addr;
    inet_aton("10.0.0.1", &antelope.sin_addr); // store IP in antelope
    some_addr = inet_ntoa(antelope.sin_addr); // return the IP
    printf("%s\n", some_addr); // prints "10.0.0.1"
    // and this call is the same as the inet_aton() call, above:
    antelope.sin_addr.s_addr = inet_addr("10.0.0.1");


// IPv4 demo of inet_ntop() and inet_pton()
    struct sockaddr_in sa;
    char str[INET_ADDRSTRLEN];
    inet_pton(AF_INET, "192.0.2.33", &(sa.sin_addr));    // store this IP address in sa:
    inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);    // now get it back and print it
    printf("%s\n", str); // prints "192.0.2.33"


// IPv6 demo of inet_ntop() and inet_pton()
// (basically the same except with a bunch of 6s thrown around)
    struct sockaddr_in6 sa2;
    char str2[INET6_ADDRSTRLEN];
    inet_pton(AF_INET6, "2001:db8:8714:3a90::12", &(sa2.sin6_addr));// store this IP address in sa:
    inet_ntop(AF_INET6, &(sa2.sin6_addr), str2, INET6_ADDRSTRLEN);// now get it back and print it
    printf("%s\n", str2); // prints "2001:db8:8714:3a90::12"
}

// Helper function you can use:
//Convert a struct sockaddr address to a string, IPv4 and IPv6:
char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen) {
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), s, maxlen);
            break;
        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), s, maxlen);
            break;
        default:
            strncpy(s, "Unknown AF", maxlen);
            return NULL;
    }
    return s;
}
