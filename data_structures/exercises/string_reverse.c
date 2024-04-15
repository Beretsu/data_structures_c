#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack_array.h"

//example of apliction of a stack
void reversee(char *string){
    int index = 0;
    while(string[index]){
        push(string[index]);
        index++;
    }
    index = 0;
    while(!isEmpty()){
        string[index] = Top();
        pop();
        index++;
    }
}

void reverse(char *string, int size){
    for(int i = 0; i < size; i++){
        push(string[i]);
    }
    for(int i = 0; i < size; i++){
        string[i] = Top();
        pop();
    }
}

int main(){
    char string[51];
    printf("Enter a string\n");
    fgets(string, 51, stdin);
    reversee(string);
    printf("output: %s\n", string);
    return 0;
}
