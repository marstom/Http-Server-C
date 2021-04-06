/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define BIG 1000000000L
uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


/*
Whith thread it is verry slow
*/
void *countToBig(void *arg){
    for(uint32_t i=0; i< BIG; i++){
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}


int main(){
    pthread_t t;
    pthread_create(&t, NULL, countToBig, NULL);
    countToBig(NULL);
    pthread_join(t, NULL);
    printf("Done. counter = %u\n", counter);

    return 0;
}
