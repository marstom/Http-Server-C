#include "common.h"
#include <pthread.h>

#define MULTITHREAD 1
#define DEBUG

void *handle_connection(void* p_client_socket);

int main(){
    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;


    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("socket error.");
    
    int _ok = 1;
    if(setsockopt(server_socket, SOL_SOCKET,SO_REUSEADDR, &_ok, sizeof(int)) < 0)
        err_n_die("unable to set SO_REUSEADDR option.");
    
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if((bind(server_socket, (SA *) &server_addr, sizeof(server_addr))) < 0)
        err_n_die("Bind failed!");

    if((listen(server_socket, 10)) < 0)
        err_n_die("Listen failed!");

    while (true){
        printf("waiting for a connection on port %d\n", SERVER_PORT);
        fflush(stdout);
        client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size);
        if(client_socket < 0)
            err_n_die("Accept failed!");
        printf("Connected!");

        int *pclient = malloc(sizeof(int));
        *pclient = client_socket;    
        if(MULTITHREAD){
            /* multithreading server mode */
            pthread_t t;
            pthread_create(&t, NULL, handle_connection, pclient);
        }else{
            /* single thread server mode */
            printf("SINGLE\n");
            handle_connection(pclient);
        }

    }
    return 0;
}

void *handle_connection(void* p_client_socket){
    int client_socket = *((int*)p_client_socket);
    free(p_client_socket);
    char buffer[BUFSIZE];
    size_t bytes_read;
    int msgsize = 0;
    char actualpath[PATH_MAX+1];

    while((bytes_read=read(client_socket, buffer+msgsize, sizeof(buffer)-msgsize-1)) > 0){
        msgsize += bytes_read;
        if(msgsize > BUFSIZE-1 || buffer[msgsize-1] == '\n') break;
    }
    if(bytes_read < 0)
        err_n_die("recv error");
    buffer[msgsize-1] = 0;
    printf("REQUEST: %s\n", buffer);
    fflush(stdout);

    // validity check
    if(realpath(buffer, actualpath) == NULL){
        printf("ERROR(bad path): %s\n", buffer);
        close(client_socket);
        return NULL;
    }
    #ifdef DEBUG
    sleep(1); // very slow file access, simulate really slow HDD
    #endif
    FILE *fp = fopen(actualpath, "r");
    if(fp==NULL){
        printf("ERROR(open): %s\n", buffer);
        close(client_socket);
        return NULL;
    }

    while((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0){
        printf("sending %zu bytes\n", bytes_read);
        write(client_socket, buffer, bytes_read);
    }
    close(client_socket);
    fclose(fp);
    printf("closing connection\n");
    return NULL;
}