#pragma once
#include <stdlib.h>


typedef struct{
    char **lines;
    char **requestSplittedLine;
    size_t numberOfRequestSplittedLines;
    size_t numberOfRequestLines;
}HeaderContent;

/*
Fill with data whole structure
:return number of lines
*/
void initHeaderContent(HeaderContent **hc, char *str);


/*
Grab selected line from response and split it (spaces) like this
["GET", "/www/index.html", "HTTP/1.1"]

:return number of alloacated strings
]
*/
void getSplittedLine(HeaderContent *hc, int lineNumber);

/*
Free header content lines
*/
void tearDownHeaderContent(HeaderContent **hc);

size_t __allocLines(char *str, HeaderContent **hc);
void __allocSentences(char *str, HeaderContent **hc);
void __fill_content(char *str, HeaderContent **hc);
