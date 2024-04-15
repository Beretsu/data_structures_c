#include <stdio.h>
#include <stdlib.h>
//since the data of the sumDoneWrong function is cleared whenever it finishes execution, returning a pointer to a locar variable of that function is not correct.
/*int* sumDoneWrong(int* a, int* b){
    int c = *a+*b;
    return &c;
}*/
//this is correct because we are returning an adress in the heap it is not deallocated at the end of execution of the function.
int* sumDoneRight(int* a, int* b){
    int* c = (int*)malloc(sizeof(int));
    *c= *a+*b;
    return c;
}
int main()
{
    int a = 2, b=4;
    //int* p = sumDoneWrong(&a,&b);
    //printf("%d\n",*p);
    int* pp = sumDoneRight(&a,&b);
    printf("%d\n", *pp);
    return 0;
}
