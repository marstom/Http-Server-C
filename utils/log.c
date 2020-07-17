
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void log(char* title, char *message, char *color){
    if(color == NULL){/*do nothing*/}
    else if(!strcmp(color, "red")){
        puts("\033[0;31m");
    }else if (!strcmp(color, "green")){
        puts("\033[0;32m");
    }
    
    puts(title);
    puts(message);
    putchar('\n');
    puts("\033[0m");
}