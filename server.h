#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h>
#include <unistd.h>
#include <netdb.h> // for getnameinfo()
#include <signal.h>
#include <assert.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

// Usual socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SIZE 1024
#define BACKLOG 10  // Passed to listen()


const char *CONTENT_JSON = "application/json";
const char *CONTENT_HTML = "text/html";
const char *CONTENT_JAVASCRIPT = "text/javascript";
const char *CONTENT_CSS = "text/css";
const char *CONTENT_PNG = "image/png";
const char *CONTENT_JPEG = "image/jpeg";

/*Checking if file is binary type or not
:return true- binary false-text file
*/
bool isFileBinary(char *filename);

/*
Process request and response
:return content length, must know how many bytes send
*/
size_t processRequestResponse(char **httpContent, char *buff);

/*Parsing request use in future*/
void parseClientRequest(char *request);
/*Parsing response use in future*/
void prepareClientResponse(char **response);

/*Working for text content only, not binary*/
void cleanFileContent(char **httpContent);