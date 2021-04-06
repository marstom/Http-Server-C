#include "request_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void initHeaderContent(HeaderContent **hc, char *str){
    HeaderContent *h = *hc;
    h->numberOfRequestLines = __allocLines(str, &h);
    __allocSentences(str, &h);
    __fill_content(str, &h);
    (*hc) = h;
}

void getSplittedLine(HeaderContent *hc, int lineNumber){
    char *line = hc->lines[lineNumber];
    char *temp = calloc(strlen(line)+1, sizeof(char));
    strcpy(temp, line);
    char *separator =" ";
    char *content = strtok(temp, separator);
    hc->numberOfRequestSplittedLines = 0;
    while(content != NULL){
        hc->requestSplittedLine[hc->numberOfRequestSplittedLines] = calloc(strlen(content)+1, sizeof(char));
        strcpy(hc->requestSplittedLine[hc->numberOfRequestSplittedLines], content);
        content = strtok(NULL, separator);
        hc->numberOfRequestSplittedLines++;
    }
    free(temp);
}


void tearDownHeaderContent(HeaderContent **hc){
    HeaderContent *h = *hc;
    for (size_t i = 0; i < h->numberOfRequestLines; i++){
        free(h->lines[i]);
    }
    free(h->lines);

    for (size_t i = 0; i < h->numberOfRequestSplittedLines; i++){
        free(h->requestSplittedLine[i]);
    }
    free(h->requestSplittedLine);
    free(h);
}

size_t __allocLines(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str)+1, sizeof(char));
    strcpy(temp, str);
    char *separator ="\n";
    char *content = strtok(temp, separator);
    size_t numberOfLines = 0;
    while(content != NULL){
        numberOfLines++;
        content = strtok(NULL, separator);
    }
    h->lines = calloc((numberOfLines+11), sizeof(char*));
    free(temp);
    (*hc) = h;
    return numberOfLines;
}


void __allocSentences(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str)+1, sizeof(char));
    strcpy(temp, str);
    char *separator ="\r\n";
    char *content = strtok(temp, separator);
    size_t lineNumber = 0;
    while(content != NULL){
        size_t sentenceLen = strlen(content)+1;
        h->lines[lineNumber] = calloc(sentenceLen, sizeof(char));
        lineNumber++;
        content = strtok(NULL, separator);
    }
    free(temp);
    (*hc) = h;

}

void __fill_content(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str)+1, sizeof(char));
    strcpy(temp, str);
    char *separator ="\r\n";
    char *content = strtok(temp, separator);
    size_t lineNumber = 0;
    while(content != NULL){
        strcpy(h->lines[lineNumber], content);
        lineNumber++;
        content = strtok(NULL, separator);
    }
    free(temp);
    (*hc) = h;
}

