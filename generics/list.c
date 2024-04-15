#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    void *value;
    struct node *next;
};

struct node* insertHead(struct node *head, void *value, size_t size){
    struct node *temp = malloc(sizeof(struct node));
    temp->value = malloc(size);
    temp->next = head;
    for(int i = 0; i < size; i++){
        *(char*)(temp->value+i) = *(char*)(value+i);
    }
    return temp;
}

struct node* deleteNode(struct node *head, void *value, int (*func)(void*, void*)){
    if(!head) return head;
    if(!func(value, head->value)){
        struct node *neww = head->next;
        free(head->value);
        free(head);
        return neww;
    }
    struct node *temp = head;
    struct node *temp2;
    while(temp->next){
        temp2 = temp->next;
        if(!func(value, temp2->value)){
            temp->next = temp2->next;
            free(temp2->value);
            free(temp2);
            return head;
        }
        temp = temp->next;
    }
}

void genericPrint(struct node *head, void (*func)(void*)){
    while(head){
        func(head->value);
        head = head->next;
    }
}

void charPrint(void *value){
    printf("%c ", *(char*)value);
}

void stringPrint(void *value){
    printf("%s ", (char*)value);
}

void printInt(void *value){
    printf("%d ", *(int*) value);
}

int main(){
    char *arr[] = {"chuy", "petra", "simon", "memo", "pepe"};
    struct node *head = insertHead(NULL, *arr, sizeof(char*));
    head = insertHead(head, *(arr+1), sizeof(char*));
    head = insertHead(head, *(arr+2), sizeof(char*));
    head = insertHead(head, *(arr+3), sizeof(char*));
    head = insertHead(head, *(arr+4), sizeof(char*));
    head = deleteNode(head, "chuy", (int (*)(void *, void *))strcmp);
    genericPrint(head, stringPrint);
    return 0;
}
