#pragma once
#include <stdbool.h>

/*
return: 
true - file is binary
false - file is text

throws: error if there's no such extension
*/

#define BINARY_CONTENT ".png;.jpeg;.ico"
#define TEXT_CONTENT ".html;.css;.json;.js"

bool isFileBinary(char *filename);