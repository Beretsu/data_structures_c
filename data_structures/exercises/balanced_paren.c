#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack_array.h"
//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P
//this code determines if opening and closing paretheses are balanced, just like with code, every opening parentheses must have a closing one
//and follow the rules of the las opened must be the first to close.

//x:size of string
int isValid(char *string, int x){
    for(int i = 0; i < x; i++){
        if(string[i] == '(' || string[i] == '[' || string[i] == '{'){
            push(string[i]);
        }else if(string[i] == ')' || string[i] == ']' || string[i] == '}'){
            if(isEmpty() || string[i] - Top() > 2){//is opening different to string[i] type. look at ascii table
                return 0;//is not valid
            }else{
                pop();
            }
        }
    }
    if(isEmpty()){
        return 1;//is valid
    }
}

int main()
{
    char string[] = "([()]{()})";
    if(isValid(string, strlen(string))){
        printf("yes\n");
    }else{
        printf("no");
    }
    return 0;
}
