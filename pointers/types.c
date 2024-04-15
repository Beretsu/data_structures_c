#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 1025;
    int* p = &a;
    printf("size of int is %d bytes\n", sizeof(int));
    printf("adress in p = %ld, value = %d\n", p, *p);
    printf("adress in p+1 = %ld, value = %d\n", p+1, *(p+1)); //garbage value
    char* pchar;
    pchar = (char*)p; //type casting for pointers
    printf("size of char is %d byttes\n", sizeof(char));
    printf("adress in pchar = %ld, value = %d\n",pchar, *pchar);
    printf("adress in (pchar+1) is %ld, value = %d\n",pchar+1,*(pchar+1));
    //1025 = 00000000 00000000 00000100 00000001
    //                          =4       =1
    //pointer types determine howtha data is read. in the examle above we casted an int pointer to a char, and the data was inerpreted differently
    //this happens even if the data types are of the same size, like in the ccase of int, and float.
    //since a char is pnly 1 byte long, when we cast, pchar only dereferences the first byte.
    void* pvoid;
    //is used for generic pointer types. it has to be casted
    return 0;
}
