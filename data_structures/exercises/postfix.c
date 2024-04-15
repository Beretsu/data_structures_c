#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../stack_array.h"
// guide https://www.youtube.com/playlist?list=PL2_aWCzGMAwI3W_JlcBbtYTwiQSsOTa6P

//resolve a postfix expresion
int postfix(char *string, int size){
    for(int i = 0; i < size; i++){
        if(string[i] >= '0' && string[i] <= '9'){
            //capture operand and push it
            int num = 0;
            while(string[i] >= '0' && string[i] <= '9'){
                num = num * 10 + string[i] - '0';
                i++;
            }
            push(num);
        }
        if(string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/'){
            int op2 = Top();
            pop();
            int op1 = Top();
            pop();
            int res;
            if(string[i] == '+'){
                res = op1 + op2;
            }else if(string[i] == '-'){
                res = op1 - op2;
            }else if(string[i] == '*'){
                res = op1 * op2;
            }else{
                res = op1 / op2;
            }
            push(res);
        }
    }
    int result = Top();
    pop();
    return result;
}
//resolve prefix expression
int prefix(char *string){
    int size = strlen(string);
    for(int i = size-1; i > -1; i--){
        if(string[i] >= '0' && string[i] <= '9'){
            //capture operand and push it
            int num = 0;
            int mult = 1;
            while(string[i] >= '0' && string[i] <= '9'){
                num = num + mult * (string[i] - '0');
                mult *= 10;
                i--;
            }
            push(num);
        }
        if(string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/'){
            int op1 = Top();
            pop();
            int op2 = Top();
            pop();
            int res;
            if(string[i] == '+'){
                res = op1 + op2;
            }else if(string[i] == '-'){
                res = op1 - op2;
            }else if(string[i] == '*'){
                res = op1 * op2;
            }else{
                res = op1 / op2;
            }
            push(res);
        }
    }
    int result = Top();
    pop();
    return result;
}
//determines wich operator has  greater hierarchy for a postfix expresion
int topHasHigherPrecedencePost(char c){
    if(c == '+' || c == '-'){
        return 1;
    }else{
        if(Top() == '*' || Top() == '/'){
            return 1;
        }else{
            return 0;
        }
    }
}
//determines wich operator has  greater hierarchy for a prefix expresion
//it is different to precedence for post, because contrary to postfix expresions, prefix expresions rightmost operator has higher precedence
int topHasHigherPrecedencePre(char c){
    if((Top() == '*' || Top() == '/') && (c == '+' || c == '-')){
        return 1;
    }
    return 0;
}
//converts an infix extrsion to post fix or prefix depending on wich function enters as the las parameter
void infixTo(char *storage, char *string, int (*func)(char)){
    int size = strlen(string);
    int index = 0;
    for(int i = 0; i < size; i++){
        if(string[i] >= '0' && string[i] <= '9'){
            storage[index] = string[i];
            index++;
        }else if(string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/'){
            storage[index] = ' ';
            index++;
            while(!isEmpty() && Top() != '(' && func(string[i])){
                storage[index] = Top();
                pop();
                index++;
                storage[index] = ' ';
                index++;
            }
            push(string[i]);
        }else{
            if(string[i] == '('){
                push(string[i]);
            }else if(string[i] == ')'){
                while(Top() != '('){
                    storage[index] = ' ';
                    index++;
                    storage[index] = Top();
                    pop();
                    index++;
                }
                pop();
            }
        }
    }
    while(!isEmpty()){
        storage[index] = ' ';
        index++;
        storage[index] = Top();
        pop();
        index++;
    }
    storage[index] = '\0';
}
//simply calls infixTo function passing topHasHigherPrecedencePost as parameter so that it converts infix expresions to postfix
void infixToPostfix(char *storage, char *string){
    infixTo(storage, string, topHasHigherPrecedencePost);
}
//reverses the expresion and substitutes opening parentheses for closing ones and veceversa
void reverseExpretion(char *string){
    int size = strlen(string) - 1;
    int start = 0;
    char temp;
    while(size > start){
        if(string[start] == '('){
            string[start] = ')';
        }else if(string[start] == ')'){
            string[start] = '(';
        }
        temp = string[start];
        string[start] = string[size];
        string[size] = temp;
        if(string[start] == '('){
            string[start] = ')';
        }else if(string[start] == ')'){
            string[start] = '(';
        }
        size--;
        start++;
    }
}
//it first reverses the expretion, then it converts proceses the string calling infixTo with the apropiate parameter to conver to prefix,
//then it reverses the string again. in the end the infix expresion is converted to prefix
void infixToPrefix(char *storage, char *string){
    int size = strlen(string);
    char temp[size+1];
    strcpy(temp, string);
    reverseExpretion(temp);
    infixTo(storage, temp, topHasHigherPrecedencePre);
    reverseExpretion(storage);
}

int main()
{
    char string[] = "6 9 7 5 4 3 4 - - - - - -";// postfix expresion
    printf("postfix %s = %d\n", string, postfix(string, strlen(string)));
    char stringg[] = "- * 21 3 - 2 * 3 * 2 5";//prefix expresion
    int res = prefix(stringg);
    printf("prefix %s = %d\n",stringg, res);
    char strin[] = "21*3-2-3*2*5";
    char storage[50];
    infixToPostfix(storage, strin);
    printf("%s in postfix is = %s\n", strin, storage);
    char wewe[] = "21 * ((3 - 2) - 3) * 2 * 5";
    char stor[51];
    infixToPrefix(stor, wewe);
    printf("%s in prefix is = %s", wewe, stor);
    return 0;
}
