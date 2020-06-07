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
void getSplittedLine(HeaderContent *hc, char **array, int lineNumber);

size_t __allocLines(char *str, HeaderContent **hc);
void __allocSentences(char *str, HeaderContent **hc);
void __fill_content(char *str, HeaderContent **hc);
