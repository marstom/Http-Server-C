#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#define QUEUE_EMPTY INT32_MIN


typedef struct node{
    int *client_socket;
    struct node *next;
}node;

typedef struct {
    node *head;
    node *tail;
}queue;


void enqueue(int *client_socket);
int *dequeue();
