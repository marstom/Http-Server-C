#include "split_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t initHeaderContent(HeaderContent **hc, char *str){
    HeaderContent *h = *hc;
    size_t numberOfLines = __allocLines(str, &h);
    __allocSentences(str, &h);
    __fill_content(str, &h);
    (*hc) = h;
    return numberOfLines;
}

size_t __allocLines(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str), sizeof(char));
    strcpy(temp, str);
    char *separator ="\n";
    char *content = strtok(temp, separator);
    size_t numberOfLines = 0;
    while(content != NULL){
        numberOfLines++;
        content = strtok(NULL, separator);
    }
    h->lines = calloc((numberOfLines+11), sizeof(char*));
    (*hc) = h;
    return numberOfLines;
}


void __allocSentences(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str), sizeof(char));
    strcpy(temp, str);
    char *separator ="\r\n";
    char *content = strtok(temp, separator);
    size_t lineNumber = 0;
    while(content != NULL){
        size_t sentenceLen = strlen(content)+5;
        h->lines[lineNumber] = calloc(sentenceLen, sizeof(char));
        lineNumber++;
        content = strtok(NULL, separator);
    }
    (*hc) = h;

}

void __fill_content(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str), sizeof(char));
    strcpy(temp, str);
    char *separator ="\r\n";
    char *content = strtok(temp, separator);
    size_t lineNumber = 0;
    while(content != NULL){
        strcpy(h->lines[lineNumber], content);
        lineNumber++;
        content = strtok(NULL, separator);
    }
    (*hc) = h;
}

void getSplittedLine(HeaderContent *hc, char **array, int lineNumber){
    char *line = hc->lines[lineNumber];
    char *temp = calloc(strlen(line), sizeof(char));
    strcpy(temp, line);
    char *separator =" ";
    char *content = strtok(temp, separator);
    size_t lineNo = 0;
    while(content != NULL){
        array[lineNo] = calloc(strlen(content)+1, sizeof(char));
        strcpy(array[lineNo], content);
        content = strtok(NULL, separator);
        lineNo++;
    }
}
