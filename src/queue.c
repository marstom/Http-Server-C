#include "queue.h"

/*
This is shared data structure, not thread safe
operation on this MUST be atomic
*/
node* head = NULL;
node* tail = NULL;

//3.33

void enqueue(int *client_socket){
    // create new node
    node *newnode = malloc(sizeof(node));
    newnode->client_socket = client_socket;
    newnode->next = NULL;
    if(tail == NULL){
        head = newnode;
    }else{
        tail->next = newnode;
    }
    tail = newnode;
}

int *dequeue(){
    if (head == NULL) return NULL;
    node *tmp = head;
    int *result = tmp->client_socket;
    head = head->next;
    if (head == NULL){
        tail = NULL;
    }
    free(tmp);
    return result;
}
