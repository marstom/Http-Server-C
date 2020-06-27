#pragma once
#include <stdlib.h>


typedef struct t_hcontent{
    char **lines;
}HeaderContent;

/*
Fill with data whole structure
:return number of lines
*/
size_t initHeaderContent(HeaderContent **hc, char *str);


/*
Grab selected line from response and split it (spaces) like this
["GET", "/www/index.html", "HTTP/1.1"]

:return number of alloacated strings
]
*/
size_t getSplittedLine(HeaderContent *hc, char **array, int lineNumber);

/*
Free header content lines
*/
void tearDownHeaderContent(HeaderContent **hc, size_t nuberOfLines);

size_t __allocLines(char *str, HeaderContent **hc);
void __allocSentences(char *str, HeaderContent **hc);
void __fill_content(char *str, HeaderContent **hc);
