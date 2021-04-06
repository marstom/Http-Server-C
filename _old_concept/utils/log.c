
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void setBufferColor(char* color){
    if(color == NULL){/*do nothing*/}
    else if(!strcmp(color, "red")){
        printf("\033[0;31m");
    }else if (!strcmp(color, "green")){
        printf("\033[0;32m");
    }else if (!strcmp(color, "yellow")){
        printf("\033[0;33m");
    }else if (!strcmp(color, "blue")){
        printf("\033[0;34m");
    }
}

void logStr(char* title, char *message, char *color){
    setBufferColor(color);
    
    printf("%s\n", title);
    printf("%s", message);
    printf("\033[0m");
}

void logInt(char* title, size_t message, char *color){
    setBufferColor(color);
    
    printf("%s\n", title);
    printf("%ld", message);
    puts("\033[0m");
}

