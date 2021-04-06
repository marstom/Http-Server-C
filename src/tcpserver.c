// TODO



#include "common.h"

void handle_connection(int client_socket);

int main(){
    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;


    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("socket error.");
    
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
        handle_connection(client_socket);

    }
    return 0;
}

void handle_connection(int client_socket){
    int n;
    uint8_t buff[MAXLINE+1];
    uint8_t recvline[MAXLINE+1];
    memset(recvline, 0, MAXLINE);

    while( (n= read(client_socket, recvline, MAXLINE - 1))  > 0){
        fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

        //hacky way to detect end of request
        if(recvline[n-1] == '\n')
            break;
        memset(recvline, 0, MAXLINE);
    }
    if(n <0)
        err_n_die("read error");
    
    // response
    snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");
    write(client_socket, (char*)buff, strlen((char *) buff));
    close(client_socket);
}