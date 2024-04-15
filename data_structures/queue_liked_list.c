#include <stdio.h>
#include <stdlib.h>
// guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
typedef struct node{
    int data;
    struct node *next;
}node;
// since we will be addig elements to the tail of the list, and removing elements from the head. in order to make things more efficient
//we'll keep track of both the rear node and the front node. to make operation O(1).
node *front = NULL;
node *rear = NULL;

int isEmpty(){
    if(front){
        return 0;
    }
    return 1;
}

void enqueue(int x){
    node *temp = malloc(sizeof(node));
    temp->data = x;
    temp->next = NULL;
    if(isEmpty()){
        front = temp;
        rear = temp;
    }else{
        rear->next = temp;
        rear = temp;
    }
}

int dequeue(){
    if(isEmpty()){
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    node *temp = front;
    int re = front->data;
    front = front->next;
    free(temp->data);
    free(temp);
    return re;
}

int Front(){
    if(isEmpty()){
        printf("The queue is empty, the operation cant be done\n");
        return 0;
    }
    return front->data;
}



void print(){
    if(!isEmpty()){
        node *temp = front;
        while(temp){
            printf("%d ", temp->data);
            temp = temp->next;
        }
    }else{
        printf("The queue is empty. the operation cant be done\n");
    }
}

int main()
{
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6);
    enqueue(7);
    enqueue(8);
    enqueue(9);
    enqueue(10);
    dequeue();
    enqueue(11);
    dequeue();
    dequeue();
    enqueue(12);
    enqueue(13);
    print();
    printf("\n----\n");
    printf("%d\n", dequeue());
    printf("%d", Front());
    return 0;
}
