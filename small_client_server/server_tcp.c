/*

This is tcp server example

gcc server_tcp.c && ./a.out
Connect:
nc localhost 8002


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


#define MS_EOF 1
#define MS_SHUTDOWN 2
#define MS_START_TRANSMISSION 3

int 
requestQueue(int serverFd, struct sockaddr_in peer_addr){
    int ok;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);
    serverFd = accept(serverFd, (struct sockaddr *)&peer_addr, &peer_addr_size);
    if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) == -1){
        handle_error("socketopt");
    }
    if(serverFd == -1 ){
        handle_error("accept");
    }
    return serverFd;
}

typedef struct {
    bool shutdown;
    bool transmit;
    bool eof;

} MS_Command;

void 
handleCommand(MS_Command *comm, char* buff){
    if(strcmp(buff, "eof\n") == 0){
        comm->eof = true;
    }else if(strcmp(buff, "transmit\n") == 0){
        comm->transmit = true; // no usage
        comm->eof = false;
    }else if(strcmp(buff, "shutdown\n") == 0){
        comm->shutdown = true;
    }
}


int 
main(){
    MS_Command msCommand = {
        .eof=false, .shutdown=false, .transmit=true
    };
    int newSockerFd;
    int serverFd = socket(
        AF_INET,
        SOCK_STREAM,
        0);

    int ok;
    if(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(int)) == -1){
        handle_error("socketopt");
    }
    struct sockaddr_in my_addr, peer_addr;
    memset(&my_addr, 0, sizeof(struct sockaddr_in));
    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8002);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(serverFd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1){
        handle_error("bind");
    }
    if(listen(serverFd, 3) == -1){
        handle_error("listen");
    }

    printf("PATH: %d\n", ntohs(my_addr.sin_port));
    char buffer[200];
    char bufferSend[200];
    strcpy(bufferSend, "OK\r\n");

    
    while(!msCommand.shutdown){
        newSockerFd = requestQueue(serverFd, peer_addr);
        msCommand.eof = false;
        while(!msCommand.eof){
            if(recv(newSockerFd, buffer, 200, 0) == -1){
                handle_error("recv");
            }
            handleCommand(&msCommand, buffer);

            if(send(newSockerFd, bufferSend, strlen(bufferSend), 0) == -1){
                handle_error("send");
            } 
            printf("%s", buffer);
            memset(buffer, '\0', 200);
        }
        
        close(newSockerFd);
    }

    puts("Server shutting down....\n");
    close(newSockerFd);
    close(serverFd);
    
    return 0;
}