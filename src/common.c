#include "common.h"

void err_n_die(const char *fmt, ...){
    int errno_save;
    va_list ap;
    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    fprintf(stdout, "\n");
    fflush(stdout);
    if(errno_save != 0 ){
        fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);
    // die now!
    exit(1);
}


char *bin2hex(const unsigned char *binary_var, size_t len){
    char *result;
    char *hexits = "0123456789ABCDEF";

    if(binary_var == NULL || len <= 0)
        return NULL;
    
    int resultlength = (len*3)+1;

    result = malloc(resultlength);
    bzero(result, resultlength);

    for(int i=0; i<len; i++){
        result[i*3] = hexits[binary_var[i] >> 4];
        result[(i*3) +1] = hexits[binary_var[i] & 0x0F];
        result[(i*3) +2] = ' ';
    }
    return result;
}