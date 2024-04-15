#include <stdio.h>
#include <stdlib.h>

struct node{
    void *value;
    struct node *next;
};

struct node *rear = NULL;
struct node *front = NULL;

int isEmpty(){
    if(front){
        return 0;
    }
    return 1;
}

void enqueue(void *value, size_t size){
    struct node *temp = malloc(sizeof(struct node));
    temp->value = malloc(size);
    for(int i = 0; i < size; i++){
        *(char*)(temp->value+i) = *(char*)(value+i);
    }
    temp->next = NULL;
    if(isEmpty()){
        rear = front = temp;
    }else{
        rear->next = temp;
        rear = temp;
    }
}

void dequeue(){
    if(isEmpty()){
        printf("there is nothing to dequeue\n");
	return;
    }
    struct node *temp = front;
    front = front->next;
    free(temp->value);
    free(temp);
    // can't free value and return it
    // so this implementation doesn't
    // return anything
}

void* Front(){
    if(isEmpty()){
        printf("the queue is empty");
        return NULL;
    }
    return front->value;
}
