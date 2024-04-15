#include <stdio.h>
#include <stdlib.h>

int main()
{
    //these int will be stored as a block of 5 consecutive ints
    int a[5];
    int* p = &a[0];
    printf("%ld\n",p);//prints adress of a[0]
    printf("%ld\n",p+1);//prints adress of a[1]
    //a++; this cant be done.
    //a = *p; this cant be done ether. a cannot be reasigned
    //p++; this can be done
    //the name of the arrays gives us the adress of the fist element of the array.
    printf("%ld\n",a);//prints adress of a[0]
    printf("%ld\n",a+1);//prints adress of a[1]
    printf("%ld\n",&a[0]);//prints adress of a[0]
    //a == &a[0]
    //&a[i] == a+i
    //*a == a[0]
    //a[i] == *(a+i)
    //a[]={2,4,5,8,1}; it cant be done anymore after declaration
    return 0;
}
