#include <stdio.h>
#include <stdlib.h>
/*Most useful advice I ever read for deciphering C types: "Start at the name, read right when you can,
left when you must": char (*a[2])[14] - start at a, move right: "array of two", move left: "pointer to",
bracket complete so read right: "array of forteen", read left: "char"...
Put it together and we have "a is array of two pointers to arrays of forteen chars"*/
//source: https://stackoverflow.com/questions/1088622/how-do-i-create-an-array-of-strings-in-c
int main()
{
    int a;
    int b=10;
    int* p;// data type: pointer to int
    //int* p = &a;   can also be riten like this
    p=&a;//& returns its adress
    a=5;
    printf("%d\n",p); // adress of a: example: 204
    printf("%d\n", &a); //204
    printf("%d\n", &p); // adress of p: 64
    printf("%d\n", *p); //dereferencing prints a: 5
    *p = 8; // can modify a using the pointer. dereferencing
    printf("%d\n", a); //8
    //&p= 0; no se puede
    return 0;
}
