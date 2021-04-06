/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h> 

#include <sys/socket.h>
#include <sys/un.h>


#include<arpa/inet.h> 
#include<netinet/in.h> 
#include<netdb.h>

#include <pthread.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


void* 
myturn(void *arg){
    int *iptr=  (int *)malloc(sizeof(int));
    *iptr = 5;
    for(int i=0; i<5; i++){
        sleep(1);
        puts("My turn!");
        (*iptr)++;
    }
    return iptr;

}

void*
yourturn(void *arg){
    for(int i=0; i<2; i++){
        sleep(1);
        puts("@Your turn#");
    }
    return NULL;
}

int 
main(){
    
    pthread_t newthread;
    int *result;

    int v = 5;
    pthread_create(&newthread, NULL, myturn, &v);
    //pthread_create(&newthread, NULL, yourturn, NULL);
    yourturn(NULL);
    pthread_join(newthread, &result);
    printf("thread done : v=%d\n", (void*)*result);
    return 0;
}
