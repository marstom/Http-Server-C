#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1024
#define BACKLOG 10  // Passed to listen()


const char *CONTENT_JSON = "application/json";
const char *CONTENT_HTML = "text/html";
const char *CONTENT_PNG = "file/png";
const char *CONTENT_JPEG = "file/jpeg";



void setHttpHeader(char **httpContent);

void setBasicHeaders(char **httpContent, const char *contentType);

void manageFile(char **httpContent);

/*
Content - will be send to client (Browser / Postman)
Buff - data received from server
*/
void loopbackResponse(char **httpContent, char *buff);

/*
Now it's really basic, max request lines nuber are 500
*/
void parseClientRequest(char *request);

void prepareClientResponse(char **response);

/* 
Working for text content only, not binary 
*/
void cleanFileContent(char **httpContent);