#include <stdio.h>
#include <stdlib.h>
// guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
//this type of list is used for when ist very common to acces previous nodes
struct node{
    int value;
    struct node *next;
    struct node *prev;
};

struct node* getNewNode(int x){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->value = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct node* insertAtHead(int x, struct node *head){
    struct node *newNode = getNewNode(x);
    if(!head){
        return newNode;
    }
    head->prev = newNode;
    newNode->next = head;
    return newNode;
}

struct node* insertAtEnd(int x, struct node *head){
    struct node *newNode = getNewNode(x);
    struct node *temp = head;
    if(temp){
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }else{
        head = newNode;
    }
    return head;
}

struct node* insertAtIndex(int x, int index, struct node *head){
    if(index < 0){
        return head;
    }
    if(index == 0){
        struct node *temp = getNewNode(x);
        if(head){
            head->prev = temp;
            temp->next = head;
            return temp;
        }
        return temp;
    }
    if(head){
        int count = 0;
        struct node *temp = head;
        while(temp){
            count++;
            temp = temp->next;
        }
        if(index <= count){
            temp = head;
            for(int i = 0; i < index-1; i++){
                temp = temp->next;
            }
            struct node *temp2 = getNewNode(x);
            temp2->prev = temp;
            if(temp->next){
                temp2->next = temp->next;
                temp->next->prev = temp2;
            }
            temp->next = temp2;
            return head;
        }
    }
    return head;
}

struct node* deleteNode(int index, struct node *head){
    if(index < 0){
        return head;
    }
    struct node *temp;
    if(index == 0){
        temp = head->next;
        temp->prev = NULL;
        free(head);
        return temp;
    }
    if(head){
        int count = 0;
        struct node *temp2 = head;
        while(temp2){
            count++;
            temp2 = temp2->next;
        }
        if(index < count){
            temp2 = head;
            for(int i = 0; i < index-1; i++){
                temp2 = temp2->next;
            }
            temp = temp2->next;
            if(temp->next){
                temp->next->prev = temp2;
            }
            temp2->next = temp->next;
            free(temp);
            return head;
        }
    }
    return head;
}

struct node* reverse(struct node *head){
    struct node *prev, *next;
    while(head){
        next = head->next;
        head->next = head->prev;
        head->prev = next;
        prev = head;
        head = next;
    }
    return prev;
}

void recursivePrint(struct node *head){
    if(head){
        printf("%d\n", head->value);
        recursivePrint(head->next);
    }
}

void reverseRecursivePrint(struct node *head){
    if(head){
        reverseRecursivePrint(head->next);
        printf("%d\n", head->value);
    }
}

struct node* recursiveReverse(struct node *head){
    if(head->next == NULL){
        head->prev = NULL;
        return head;
    }
    struct node *p = recursiveReverse(head->next);
    struct node *temp = head->next;
    temp->next = head;
    head->prev = temp;
    head->next = NULL;
    return p;
}

void forwardPrint(struct node *head){
    while(head){
        printf("%d\n", head->value);
        head = head->next;
    }
}

void reversePrint(struct node *head){
    if(head){
        while(head->next){
            head = head->next;
        }
        while(head){
            printf("%d\n", head->value);
            head = head->prev;
        }
    }
}

int main(){
    struct node *head = NULL;
    struct node *temp;
    head = insertAtEnd(1, head);
    head = insertAtEnd(2, head);
    head = insertAtEnd(3, head);
    head = insertAtEnd(4, head);
    head = insertAtIndex(9, 4, head);
    head = recursiveReverse(head);
    forwardPrint(head);
    return 0;
}
