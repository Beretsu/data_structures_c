#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int genericSwap(void *element1, void *element2, size_t size){
    void *temp = malloc(size);
    memcpy(temp, element1, size);
    memcpy(element1, element2, size);
    memcpy(element2, temp, size);
    free(temp);
}

int main()
{
    int a = 3;
    int b = 5;
    printf("before swap a = %d, and b = %d\n", a, b);
    genericSwap(&a, &b, sizeof(int));
    printf("after swap a = %d, and b = %d\n", a, b);
    return 0;
}
