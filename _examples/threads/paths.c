#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main(int argc, char const *argv[]){
    printf("Args: %s\n", argv[1]);
    printf("Abs: %s\n", realpath(argv[1], NULL));
    return 0;
}
