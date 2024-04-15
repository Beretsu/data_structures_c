#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 10;
    int* p = &a;
    printf("p holds the adress: %ld\n",p); //p is 2002
    printf("size of integer is %d bytes\n", sizeof(int));
    //when adding or substracting a value to a pointer, it substracts or adds the the size in bytes of the data type per each whole(1).
    //in this case it adds 4 because int's data size is 4 bytes in my machine.
    printf("adress p holds+1(p+1) is: %ld\n",p+1); //p+1 is 2006
    //this way we can acces memory wich is not allocated to the program. this can be dangerous.
    //the only allowed operations are addition and substraction
    return 0;
}
