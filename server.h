#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1024
#define BACKLOG 10  // Passed to listen()


const char *CONTENT_JSON = "application/json";
const char *CONTENT_HTML = "text/html";
const char *CONTENT_JAVASCRIPT = "text/javascript";
const char *CONTENT_CSS = "text/css";
const char *CONTENT_PNG = "image/png";
const char *CONTENT_JPEG = "image/jpeg";




void setBasicHeaders(char **httpContent, const char *contentType);



/*
Content - will be send to client (Browser / Postman)
Buff - data received from server
:return content length, must know how many bytes send
*/
size_t loopbackResponse(char **httpContent, char *buff);

/*
Now it's really basic, max request lines nuber are 500
*/
void parseClientRequest(char *request);

void prepareClientResponse(char **response);

/* 
Working for text content only, not binary 
*/
void cleanFileContent(char **httpContent);