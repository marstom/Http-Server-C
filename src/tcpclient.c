/*

https://www.youtube.com/watch?v=bdIiTxtMaKA&t=0s&ab_channel=JacobSorber


*/

#include "common.h"

int main(int argc, char **argv){
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in serveraddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    if (argc != 2)
        err_n_die("Usage: %s <server address>", argv[0]);
    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_n_die("Error while creating the socket!");
    
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    // htons translate to binary considering my computer byte order
    serveraddr.sin_port = htons(SERVER_PORT); 

    if(inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) <= 0)
        err_n_die("ined_pton error for %s ", argv[1]);

    if(connect(sockfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
        err_n_die("connect failed!");

    // prepare message to server
    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes = strlen(sendline);

    if(write(sockfd, sendline, sendbytes) != sendbytes)
        err_n_die("write error");

    memset(recvline, 0, MAXLINE);
    while( (n=read(sockfd, recvline, MAXLINE-1)) > 0){
        printf("%s", recvline);
    }
    if(n<0)
        err_n_die("read error");
    
    return 0;
}