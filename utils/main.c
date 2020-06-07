/*
This is test driver program
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "split_string.h"



int main(){
    char *str = calloc(1024, sizeof(char));
    FILE *htmlData = fopen("resp.txt", "r");

    char line[100];
    while (fgets(line, 100, htmlData) != 0) {
        strcat(str, line);
    }
    fclose(htmlData);


    HeaderContent *headerContent;
    headerContent = malloc(sizeof(HeaderContent));
    initHeaderContent(&headerContent, str);

    char **splittedLine = malloc(sizeof(char*) * 20);
    getSplittedLine(headerContent, splittedLine, 0);
    puts("hahah\n");
    puts(splittedLine[1]);
    return 0;
}