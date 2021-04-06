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
#include <errno.h>

// Usual socket headers
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define REQUEST_BUFFER_SIZE 12000
#define BACKLOG 100  // Passed to listen()


const char *CONTENT_JSON = "application/json";
const char *CONTENT_HTML = "text/html";
const char *CONTENT_JAVASCRIPT = "text/javascript";
const char *CONTENT_CSS = "text/css";
const char *CONTENT_PNG = "image/png";
const char *CONTENT_JPEG = "image/jpeg";

/*
FILE  - serve file
STATUS - serve always index.html
*/
typedef struct {
    char mode;
    char *filename;
}RequestData;

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
void parseClientRequest(char *request, RequestData *requestData);
/*Parsing response use in future*/
size_t prepareClientResponse(char **response, RequestData *requestData);

/*Working for text content only, not binary*/
void cleanFileContent(char **httpContent);