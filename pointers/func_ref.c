#include <stdio.h>
#include <stdlib.h>
//unlike calling by value, calling by reference allows to modify variables outside of that particular function, because a pointer poins to that variable.
//in calling by value a copy(formal argument) of the argument passed is created to be used in the function, therefore any changes to that copy, will not reflect in the original argument(actual argument)
void increment(int* p){
++*p;
}
int main()
{
    int a = 10;
    increment(&a);
    printf("a=%d\n",a);
    return 0;
}
