#include <stdio.h>
#include <stdlib.h>
//guide : https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
//struct to be the nodes of the list
typedef struct ints{
    int value;
    struct ints *next;
}ints;
//struct to be de nodes of the stack
typedef struct node{
    ints *value;
    struct node *next;
}node;

node *top = NULL;
ints *head = NULL;
//insert element to the list
ints* insertBeginning(int n){
    ints *temp = malloc(sizeof(struct ints));
    temp->value = n;
    temp->next = head;
    head = temp;
}

void push(ints *x){
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

ints* Top(){
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

void reverse(){
    if(head){
        ints *temp = head;
        while(temp){
            push(temp);
            temp = temp->next;
        }
        temp = Top();
        head = temp;
        pop();
        while(!isEmpty()){
            temp->next = Top();
            pop();
            temp = temp->next;
        }
        temp->next = NULL;
    }
}

void print(){
    ints *temp = head;
    while(temp){
        printf("%d\n", temp->value);
        temp = temp->next;
    }
}

int main()
{
    head = insertBeginning(1);
    head = insertBeginning(2);
    head = insertBeginning(3);
    head = insertBeginning(4);
    head = insertBeginning(5);
    print();
    printf("-----after reversal-----\n");
    reverse();
    print();
    return 0;
}
