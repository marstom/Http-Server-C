/*

This is udp server example

gcc server_udp.c && ./a.out
Connect:
nc -u localhost 8002


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h> 

#include <sys/socket.h>
#include <sys/un.h>


#include<arpa/inet.h> 
#include<netinet/in.h> 
#include<netdb.h>


#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(){
    ssize_t nread;
    int serverFd = socket(
        AF_INET,
        SOCK_DGRAM,
        0
    );
    int ok;
    if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) == -1){
        handle_error("socketopt");
    }
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8002);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(serverFd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1){
        handle_error("bind");
    }

    char buffer[200];
    int addressSize = sizeof(my_addr);
    for(;;){
        nread = recvfrom(serverFd, buffer, 200, 0, (struct sockaddr *)&my_addr, &addressSize);
        buffer[nread] = '\0';
        if(nread == -1)
            continue;
        sendto(serverFd, "OK!\n", 4, 0, (struct sockaddr *)&my_addr, addressSize);
        printf("BUFF: %s", buffer);
        memset(buffer, 200 , '\0');
    }
    return 0;
}