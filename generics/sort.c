#include <stdio.h>
#include <stdlib.h>

void memcopy(void* destiny, void* origin, size_t elementSize){
    for(int i = 0; i < elementSize; i++){
        *((char*)destiny+i) = *((char*)origin+i);
    }
}

void swap(void* a, void* b, size_t elementSize){
    void* swap = malloc(elementSize);
    for(int i = 0; i < elementSize; i++){
        *((char*)swap+i) = *((char*)a+i);
    }
    for(int i = 0; i < elementSize; i++){
        *((char*)a+i) = *((char*)b+i);
    }
    for(int i = 0; i < elementSize; i++){
        *((char*)b+i) = *((char*)swap+i);
    }
    free(swap);
}

void selectionSort(void* arr, size_t elementSize, int len, int (*cmp)(void*, void*)){
    for(int i = 0; i < len-1; i++){
        int min = i;
        for(int j = i+1; j < len; j++){
            if(cmp(arr+j*elementSize, arr+min*elementSize) > 0){ //void* arithmetic is a gcc extention, it is not c standard
                min = j;
            }
        }
        swap(arr+elementSize*i, arr+min*elementSize, elementSize);
    }
}

int isLesser(int* a, int* b){
    return *b - *a;
}

int isGreater(int* a, int* b){
    return *a - *b;
}

void intPrint(void* arr, size_t elementsize, size_t len){
    for(int i = 0; i < len; i++){
        printf("%d\n", *(int*)((char*)arr+i*elementsize));
    }
}

void bubbleSort(void* arr, size_t elementsize, size_t len, int (*cmp)(void*, void*)){
    for(int i = 0; i < len-1; i++){
        int flag = 0;
        for(int j = 0; j < len-i-1;j++){
            void* a = arr+j*elementsize;
            void* b = arr+(j+1)*elementsize;
            if(cmp(a, b) > 0){
                swap(a, b, elementsize);
                flag = 1;
            }
        }
        if(!flag){
            break;
        }
    }
}

void insertionSort(void* arr, size_t elementsize, size_t len, int (*cmp)(void*, void*)){
    for(int i = 1; i < len; i++){
        void* temp = malloc(elementsize);
        for(int j = 0; j < elementsize; j++){
            *((char*)temp+j) = *((char*)arr+i*elementsize+j);
        }
        int hole = i;
        while(hole > 0 && cmp(arr+(hole-1)*elementsize, temp) > 0){
            for(int j = 0; j < elementsize; j++){
                *((char*)arr+hole*elementsize+j) = *((char*)arr+(hole-1)*elementsize+j);
            }
            hole--;
        }
        for(int j = 0; j < elementsize; j++){
            *((char*)arr+hole*elementsize+j) = *((char*)temp+j);
        }
        free(temp);
    }
}

void merge(void* arr, size_t elementSize, void* left, size_t leftlen, void* right, size_t rightlen, int (*cmp)(void*, void*)){
    int masterCount = 0, leftCount = 0, rightCount = 0;
    while(leftCount < leftlen && rightCount < rightlen){
        if(cmp(left+leftCount*elementSize, right+rightCount*elementSize) >= 0){
            for(int i = 0; i < elementSize; i++){
                *((char*)arr+masterCount*elementSize+i) = *((char*)left+leftCount*elementSize+i);
            }
            leftCount++;
        }else{
            for(int i = 0; i < elementSize; i++){
                *((char*)arr+masterCount*elementSize+i) = *((char*)right+rightCount*elementSize+i);
            }
            rightCount++;
        }
        masterCount++;
    }
    while(leftCount < leftlen){
        for(int i = 0; i < elementSize; i++){
            *((char*)arr+masterCount*elementSize+i) = *((char*)left+leftCount*elementSize+i);
        }
        leftCount++;
        masterCount++;
    }
    while(rightCount < rightlen){
        for(int i = 0; i < elementSize; i++){
            *((char*)arr+masterCount*elementSize+i) = *((char*)right+rightCount*elementSize+i);
        }
        rightCount++;
        masterCount++;
    }
}

void mergeSort(void* arr, size_t elementSize, size_t len, int (*cmp)(void*, void*)){
    if(len < 2){
        return;
    }
    int mid = len/2;
    void* left = malloc(mid*elementSize);
    void* right = malloc((len-mid)*elementSize);
    for(int i = 0; i < mid; i++){
        for(int j = 0; j < elementSize; j++){
            *((char*)left+i*elementSize+j) = *((char*)arr+i*elementSize+j);
        }
    }
    for(int i = mid; i < len; i++){
        for(int j = 0; j < elementSize; j++){
            *((char*)right+(i-mid)*elementSize+j) = *((char*)arr+i*elementSize+j);
        }
    }
    mergeSort(left, elementSize, mid, cmp);
    mergeSort(right, elementSize, len-mid, cmp);
    merge(arr, elementSize, left, mid, right, len-mid, cmp);
    free(left);
    free(right);
}

int partition(void* arr, size_t elementSize, int start, int end, int (*cmp)(void*, void*)){
    int pIndex = start;
    for(int i = start; i < end; i++){
        if(cmp(arr+i*elementSize, arr+end*elementSize) <= 0){
            swap(arr+i*elementSize, arr+pIndex*elementSize, elementSize);
            pIndex++;
        }
    }
    swap(arr+end*elementSize, arr+pIndex*elementSize, elementSize);
    return pIndex;
}

int randomizedPartition(void* arr, size_t elementSize, int start, int end, int (*cmp)(void*, void*)){
    int ran = rand()%(end+1-start)+start;//generates a number between start to end
    swap(arr+ran*elementSize, arr+end*elementSize, elementSize);
    return partition(arr, elementSize, start, end, cmp);
}

void quickSort(void* arr, size_t elementSize, int start, int end, int (*cmp)(void*, void*)){
    if(start < end){ //this takes care for when there is onlyy one element left , and when there is no valid index to the side of pIndex
        int pIndex = randomizedPartition(arr, elementSize, start, end, cmp);
        quickSort(arr, elementSize, start, pIndex-1, cmp);
        quickSort(arr, elementSize, pIndex+1, end, cmp);
    }
}

int main(){
    int arr[] = {3,4,5,6,7,87,98,6,5,3,4,5,22,4,6,2,8};
    int (*greatp)(void *, void *), (*lessp)(void *, void *);

    greatp = (int (*)(void *, void *))isGreater;
    lessp = (int (*)(void *, void *))isLesser;
    selectionSort(arr, sizeof(int), sizeof(arr)/sizeof(int), lessp);
    //bubbleSort(arr, sizeof(arr[0]), sizeof(arr)/ sizeof(arr[0]), greatp);
    //insertionSort(arr, sizeof(arr[0]), sizeof(arr)/ sizeof(arr[0]), greatp);
    //mergeSort(arr, sizeof(arr[0]), sizeof(arr)/sizeof(arr[0]), lessp);
    //quickSort(arr, sizeof(arr[0]), 0, sizeof(arr)/sizeof(arr[0])-1, greatp);
    intPrint(arr, sizeof(int), sizeof(arr)/sizeof(int));
    return 0;
}
