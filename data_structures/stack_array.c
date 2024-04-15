#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
//array implementation of stack
static int A[MAX_SIZE];// since when creating an array in c the size cannot be a variable. i usead a macro to indicate the size
static int top = -1; // -1 indicates that the stack is empty

void push(int x){
    if(top == MAX_SIZE-1){
        printf("Error: Stack Overflow\n");
    }else{
        A[++top] = x;
    }
}

void pop(){
    if(top == -1){
        printf("Error: No element to pop\n");
    }else{
        top--;
    }
}

int Top(){
    if(top > -1){
        return A[top];
    }
    printf("no element in the stack\n");
}

int isEmpty(){
    if(top == -1){
        return 1;
    }
    return 0;
}
