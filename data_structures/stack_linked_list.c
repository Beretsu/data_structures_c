#include <stdio.h>
#include <stdlib.h>
//linkedList implementation of stack
typedef struct node{
    int value;
    struct node *next;
}node;

node *top = NULL;
//we add nodes to the head of the list because its more efficient in terms of time O(1) compared to O(n) for adding nodes to the tail
void push(int x){
    node *newNode = malloc(sizeof(node));
    newNode->value = x;
    newNode->next = top;
    top = newNode;
}

void pop(){
    if(top){
        node *temp = top;
        top = top->next;
        free(temp);
    }else{
        printf("error: no element to pop\n");
    }
}

int Top(){
    if(top){
        return top->value;
    }
    printf("no element in the stack\n");
}

int isEmpty(){
    if(top){
        return 0;
    }
    return 1;
}

int main()
{

    return 0;
}
