#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int num, den;
}fraction;

int gBinarySearch(void *array, int length, size_t elementSize, void *key, int (*cmp)(void*, void*)){
    int low = 0, high = length - 1, currentIndex;
    while(low <= high){
        currentIndex = (low + high) / 2;
        void *currentElement = array + currentIndex * elementSize;
        if(cmp(currentElement, key) == 0){
            return currentIndex;
        }else if(cmp(currentElement, key) > 0){
            high = currentIndex - 1;
        }else{
            low = currentIndex +1;
        }
    }
    return -1;
}

int fractionCmp(fraction *element1, fraction *element2){
    float a = (float)element1->num / (float)element1->den;
    float b = (float)element2->num / (float)element2->den;
    return (a-b) * 100;
}

int main()
{
    fraction array[] = {{1,9}, {1,8}, {1,7}, {1,6}, {1,5}, {2,8}, {1,2}};
    fraction key = {4,16};
    int a = gBinarySearch(array, sizeof(array) / sizeof(array[0]), sizeof(array[0]), &key,
		    (int (*)(void *, void *)) fractionCmp);
    printf("%d\n", a);
    return 0;
}
