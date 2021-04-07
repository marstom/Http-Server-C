#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>

#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define SERVER_PORT 8080
#define MAXLINE 4096
#define BUFSIZE 4096
#define PATH_MAX 255
#define SOCKETERROR (-1)
#define SEVER_BACKLOG 1
#define SA struct sockaddr
#define SA_IN struct sockaddr_in


void err_n_die(const char *fmt, ...);
char *bin2hex(const unsigned char *input, size_t len);
