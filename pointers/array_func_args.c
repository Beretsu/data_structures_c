#include <stdio.h>
#include <stdlib.h>
int sumOfElements(int a[],int size){//(int* a) == (int a[]) in the case of an array as function argument
    //arrays as funtion arguments are always called by reference. creating a pointer to the first element of the array and passing it as an argument
    //arrays can be really large, so it doesent make sense to copy the array, for that reason arrays are always called by reference
    printf("FUNCTION size of a: %d, size of a[0]: %d\n", sizeof(a), sizeof(a[0]));
    //size of a is not the same here as it is in main. the reason is; when an array is sent as an argument to a function
    //a pointer to the first element in the array is sent, not the variable "a" that is the name of the array. the variable is not the same as a pointer
    //even though is returns an adress. So the way to know the length of the array is to use the "sizeof()" function with the original variable of the array.
    //the length of an array has to be sent to the function.
    int sum = 0;
    for(int i = 0; i<size;i++){
        sum+=a[i];
    }
    return sum;
}
int sumOfElements2(int* a, int size){
    //this is the same as the function above
    int sum = 0;
    for(int i = 0; i<size; i++){
        sum+=*(a+i);// we can use a[i] as well
    }
    return sum;
}
int main()
{
    int a[]={1,2,3,4,5};
    int* p =a;
    printf("%ld\n",&a);
    printf("%ld\n",a);
    printf("%ld\n",p);
    printf("%ld\n",*p);
    printf("%d\n",*(p+3));
    printf("%ld\n",sizeof(&a)); //size = 8. just like a pointer
    printf("%ld\n",sizeof(p)); // size 8. pointer
    printf("%ld\n",sizeof(*p)); // size 4, because its retrieving an int
    printf("%ld\n",sizeof(a));// size 20. returns the size of the array in bytes
    printf("%ld\n",sizeof(*a));// size 4. retrieves an int
    printf("MAIN size of a: %d, size of a[0]: %d\n", sizeof(a), sizeof(a[0]));
    int size = sizeof(a)/sizeof(a[0]);
    int total = sumOfElements2(a, size);
    printf("sum of all elements = %d\n",total);
    return 0;
}
