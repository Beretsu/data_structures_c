#include <stdio.h>
#include <stdlib.h>
//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
int queue[10];
int rear = -1;// -1 is for when the queue is empty
int front = -1;// -1 is for when the queue is empty

int isEmpty(){
    if(rear == -1 && front == -1){
        return 1;
    }
    return 0;
}

int isFull(){ // not part of common operations
    if((rear+1)%(sizeof(queue)/sizeof(int)) == front){//when the next element to rear == front, the queue is full. the modulo is because this is a circular array
        return 1;
    }
    return 0;
}
//returns the value of the element of the top of the array
int Front(){
    if(isEmpty()){
        printf("The queue is empty\n");
        return 0;
    }
    return queue[front];
}
//adds an element to the queue
void enqueue(int x){
    if(isFull()){
        printf("the queue is full. The operation cant be done\n");
    }else if(isEmpty()){
        rear = 0;
        front = 0;
        queue[rear] = x;
    }else{
        rear = (rear+1)%(sizeof(queue)/sizeof(int));
        queue[rear] = x;
    }
}
//removes element from queue
int dequeue(){
    if(isEmpty()){
        printf("the queue is empty. the operation cant be done\n");
        return 0;
    }
    int temp = Front();
    if(rear == front){
        rear = -1;
        front = -1;
        return temp;
    }
    front = (front+1)%(sizeof(queue)/sizeof(int));
    return temp;
}

void print(){
    if(!isEmpty()){
        if(front <= rear){
            for(int i = front; i < rear+1; i++){
                printf("%d ", queue[i]);
            }
        }else{//case for when array is rotated
            for(int i = front; i < sizeof(queue)/ sizeof(int); i++){
                printf("%d ", queue[i]);
            }
            for(int i = 0; i < rear+1; i++){
                printf("%d ", queue[i]);
            }
        }
    }else{
        printf("the queue is empty there is nothing to print\n");
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
    return 0;
}
