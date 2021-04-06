#include "file_checker.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool isFileBinary(char *filename){
    char *binary = strdup(BINARY_CONTENT);
    char *text = strdup(TEXT_CONTENT);
    char *tok;
    for(tok = strtok(binary, ";"); tok && *tok; tok = strtok(NULL, ";")){
        if(strstr(filename, tok) != NULL){
            free(binary);
            free(text);
            return true;
        }
    }
    tok = NULL;
    for(tok = strtok(text, ";"); tok && *tok; tok = strtok(NULL, ";")){
        if(strstr(filename, tok) != NULL){
            free(binary);
            free(text);
            return false;
        }
    }

    free(binary);
    free(text);
    printf("Unknown file extension: %s!\n", filename);
    exit(1);
}