#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct t_hcontent{
    char **lines;
}HeaderContent;

/*
Fill with data whole structure
*/
void initHeaderContent(HeaderContent **hc, char *str);

void getSplittedLine(HeaderContent *hc, char **array, int lineNumber);

void __allocLines(char *str, HeaderContent **hc);
void __allocSentences(char *str, HeaderContent **hc);
void __fill_content(char *str, HeaderContent **hc);

void initHeaderContent(HeaderContent **hc, char *str){
    HeaderContent *h = *hc;
    __allocLines(str, &h);
    __allocSentences(str, &h);
    __fill_content(str, &h);
    (*hc) = h;
}

void __allocLines(char *str, HeaderContent **hc){
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
}


void __allocSentences(char *str, HeaderContent **hc){
    HeaderContent *h = *hc;
    char *temp = calloc(strlen(str), sizeof(char));
    strcpy(temp, str);
    char *separator ="\n";
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
    char *separator ="\n";
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
    //array = malloc(sizeof(char*)*20); // todo
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

void tokenizeStr(char *str){
    char *separator ="\n";
    char *content = strtok(str, separator);

    int numberOfLines = 0;
    while(content != NULL){
        puts("--------------\n");
        puts(content);
        printf("%ld\n", strlen(content));
        content = strtok(NULL, separator);
        numberOfLines++;
    }
    printf("no of lines %d\n", numberOfLines);

}

int main(){
    char *str = calloc(1024, sizeof(char));
    FILE *htmlData = fopen("text.txt", "r");

    char line[100];
    while (fgets(line, 100, htmlData) != 0) {
        strcat(str, line);
    }
    fclose(htmlData);
    // puts(str);
    //tokenizeStr(str);
    HeaderContent *headerContent;
    headerContent = malloc(sizeof(struct t_hcontent));
    initHeaderContent(&headerContent, str);

    char **splittedLine = malloc(sizeof(char*) * 20);
    getSplittedLine(headerContent, splittedLine, 0);
    puts("hahah\n");
    puts(splittedLine[1]);
    return 0;
}