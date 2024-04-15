#include <stdio.h>
#include <stdlib.h>

struct node{
    void *valor;
    struct node *next;
};

struct node *top = NULL;

void push(void *value, size_t elementSize){
    struct node *temp = malloc(sizeof(struct node));
    temp->valor = malloc(elementSize);
    for(int i = 0; i < elementSize; i++){
        *(char*)(temp->valor+i) = *(char*)(value+i);
    }
    temp->next = top;
    top = temp;
}

void pop(){
    if(top){
        struct node* temp = top;
        top = top->next;
	free(temp->valor);
        free(temp);
	// cant free valor and return it
	// so this implementation doesn't
	// return anything
    }else{
        printf("error: no element to pop");
    }
}

void* Top(){
    if(top){
        return top->next;
    }
    printf("there is no element on the stack");
    return NULL;
}

int isEmpty(){
    if(top){
        return 0;
    }
    return 1;
}

int main()
{
    int n, i, *p;

    n = 0;
    for (i=0;i<5;i++) {
	    push((void *) &n, sizeof(int));
	    n++;
    }
    for (i=0;i<5;i++) {
	    p = (int *) Top();
	    printf("%d\n", *p);
	    // for this implementation
	    // pop frees valor, so we must
	    // not pop until we don't need
	    // valor anymore
	    pop();
    }
    return 0;
}
