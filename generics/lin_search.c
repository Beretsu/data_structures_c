#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int num;
    int den;
}fraction;

int genericSearch(void *array, int arraylen, size_t elementSize, void *key, int (*cmp)(void*, void*)){
    for(int i = 0; i < arraylen; i++){
        void * currentElement = array + elementSize*i;
        if(cmp(currentElement, key)){
            return i;
        }
    }
    return -1;
}

int fractionCmp(fraction *element1, fraction *element2){
    float a = (float)element1->num / (float)element1->den;
    float b = (float)element2->num / (float)element2->den;
    if(a == b){
        return 1;
    }
    return 0;
}

int anotherSearch(void *array, int arraylen, size_t elementSize, void* key){
    for(int i = 0; i < arraylen; i++){
        void *currentElement = array + elementSize*i;
        if(!memcmp(currentElement, key, elementSize)){
            return i;
        }
    }
    return -1;
}

int main()
{
    fraction lista[] = {{1,2}, {1,3}, {1,4}, {5,25}, {2,4}, {2,5}, {3,6}, {4,9}};
    fraction key = {3,6};
    int a = genericSearch(lista, sizeof(lista)/sizeof(lista[0]), sizeof(lista[0]), &key,
		    (int (*)(void *, void *))fractionCmp);
    printf("%d\n", a);
    int b = anotherSearch(lista, sizeof(lista)/sizeof(lista[0]), sizeof(lista[0]), &key);
    printf("%d\n", b);
    return 0;
}
