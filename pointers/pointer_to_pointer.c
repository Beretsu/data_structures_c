#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 5;
    int* p = &x;
    *p = 6;
    int** q= &p; // to point to a pointer you nedd a data type pointer to pointer.
    int*** r = &q;
    printf("%d\n",*p);//prints 6
    printf("%ld\n",*q);//adress of x 225, value of p
    printf("%d\n",*(*q));//6 value of x
    printf("%ld\n",*(*r));// value of p, adress of x
    printf("%d\n",*(*(*r)));// value in x
    **q = *p +2;
    printf("%d\n", **q);
    return 0;
}
