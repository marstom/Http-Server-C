#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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