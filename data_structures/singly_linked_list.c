#include <stdio.h>
#include <stdlib.h>

//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P

struct node{
    int value;
    struct node *next;
};

struct node* insertEnd(struct node *head, int n){
    struct node *temp = malloc(sizeof(struct node));
    temp->value = n;
    temp->next = NULL;
    struct node *temp2 = head;
    if(temp2){
        while(temp2->next){
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }else{
        head = temp;
    }
    return head;
}

struct node* insertBeginning(struct node *head, int n){
    struct node *temp = malloc(sizeof(struct node));
    temp->value = n;
    temp->next = head;
    return temp;
}

struct node* insertAt(struct node *head, int pos, int n){
    if(pos < 0){
        return NULL;//not a valid option
    }
    if(pos == 0){
        struct node *temp = malloc(sizeof(struct node));
        temp->value = n;
        temp->next = head;
        return temp;
    }
    if(head){
        int count = 0;
        struct node *temp2 = head;
        while(temp2){
            count++;
            temp2 = temp2->next;
        }
        if(pos <= count){
            temp2 = head;
            for(int i = 0; i < pos-1; i++){
                temp2 = temp2->next;
            }
            struct node *temp = malloc(sizeof(struct node));
            temp->value = n;
            temp->next = temp2->next;
            temp2->next = temp;
            return head;
        }
    }
    return NULL;
}

struct node* deleteNode(struct node *head, int index){
    if(index < 0){
        return NULL;
    }
    struct node *temp;
    if(index == 0){
        temp = head->next;
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
            temp2->next = temp->next;
            free(temp);
            return head;
        }
    }
    return NULL;
}

struct node* reverse(struct node *head){
    struct node *prev = NULL, *current = head, *next;
    while(current){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
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
    if(!head){
        return;
    }
    reverseRecursivePrint(head->next);
    printf("%d\n", head->value);
}

struct node* recursiveReverse(struct node *head){
    struct node *p;
    if(head->next == NULL){
        p = head;
        return p;
    }
    p = recursiveReverse(head->next);
    struct node *temp = head->next;
    temp->next = head;
    head->next = NULL;
    return p;
}

void print(struct node *head){
    while(head){
        printf("%d\n", head->value);
        head = head->next;
    }
}

int main(){
    struct node *head = NULL;
    head = insertBeginning(head, 0);
    head = insertEnd(head, 1);
    head = insertEnd(head, 2);
    head = insertEnd(head, 3);
    head = insertEnd(head, 4);
    head = insertEnd(head, 5);
    head = insertBeginning(head, -1);
    head = recursiveReverse(head);
    print(head);
    return 0;
}
