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
Fill array with response body lines array
[[Http1.1, POST, file/file.png],
[Cookie, asdf, ....]
:return number of alloacated lines
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
