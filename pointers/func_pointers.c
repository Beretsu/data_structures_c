#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void printHello(){
    printf("hello\n");
}
int add(int a, int b){
    return a+b;
}
void copion(void (*p)()){ // recieves a function that has no return value, and recieves no arguments.
    p();//callback function
}
int forQsort(const void* a, const void* b){
    int aa = *((int*)a);
    int bb = *((int*)b);
    return aa-bb;
}
int acendingCompare(int a,int b){
    return a-b;
}
int decendingCompare(int a, int b){
    return b-a;
}
int acendingAbsoluteCompare(int a,int b){
    return abs(a)-abs(b);
}
//callback function compares 2 ints. returns 1 if first element is higher, 0 if elements are equal, and -1 if first element is smaller.
void sort(int a[],int n, int (*compare)(int,int)){
    //simple bubble sort
    printf("sorting\n");
    int i, j, temp;
    for(i=0;i<n-1; i++){
        for(j=0;j<n-1;j++){
            if(compare(a[j],a[j+1])>0){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
int main(){
    int (*p)(int,int);//pointer to function that must take 2 ints as arguments and return an int
    //int *p(int,int); ...this would be a function declaration. not the same as the above line
    p = &add; //we can also avoid the '&' simbol, and it would be the same
    int c = (*p)(5,8);//we can also just call the function like this: p(5,8); it would be the same
    printf("%d\n", c);
    void (*ph)();
    ph = printHello;
    ph();
    copion(ph);
    int arr[] = {4,-5,3,0,-9,5,0,-3,5,-8,0,-1,-4,6,4,3,0,-6,-3,-8,-1,4,5,6,-9,-1,4,2,8,7};
    sort(arr, sizeof(arr)/sizeof(int),acendingAbsoluteCompare);
    for(int i = 0; i<sizeof(arr)/sizeof(int); i++){
        printf("%d", arr[i]);
    }
    printf("\n");
    qsort(arr, sizeof(arr)/sizeof(int), sizeof(int),forQsort);
    for(int i = 0; i<sizeof(arr)/sizeof(int); i++){
        printf("%d", arr[i]);
    }
    return 0;
}
