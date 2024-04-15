#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[] = {2, 3, 4, 5, 6, 7};
    void *arrv = arr;
    printf("%u, %u \n",arrv, arrv+1);
    return 0;
}
