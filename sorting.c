#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwKedT2KfDMB9YA5DgASZb3U
//inefficient algorithm, but very intuitive.
//it iterates the whole list and then swaps the smallest element with the element in the beggining of the list
//then it repeats the procces, but this time it iterates starting from the next element to the last minimal element swaped
//O(n^2)
void selectionSort(int *arr, int len){
    for(int i = 0; i < len-1; i++){
        int min = i;
        for(int j = i+1; j < len; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}
//it compares the initial(b) element to its next element(b), and if b is greater than a it swappes them, then it repeats the proces, but this time
// b becomes the element to compare to its next element. at the end the greatest element in the list "bubbles up"(moves) to the end of the list
//then it repeats the proces, but iterating one less time.
//its prety ineficient O(n^2). posibly a littlebit better than selectionSort
void bubbleSort(int *arr, int len){
    for(int i = 0; i < len-1; i++){
        int flag = 0;
        for(int j = 0; j < len-1-i; j++){
            if(arr[j] > arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = 1;
            }
        }
        if(!flag){
            break;
        }
    }
}
//it moves all greater numbers to the left of i to its right and it marks where the last element to move was, so that i can take its place in that hole that was created.
// inefficient, but defenitly better than bubble sort and selection sort. time complexity O(n^2).
void insertionSort(int *arr, int length){
    for(int i = 1; i < length; i++){
        int value = arr[i];
        int hole = i;
        while(hole > 0 && arr[hole-1] > value){
            arr[hole] = arr[hole-1];
            hole--;
        }
        arr[hole] = value;
    }
}
//it merges 2 lists into 1 comparing left "i" element and right "j" element, and positioning the lesser element first.
void merge(int *destiny, int *left, int lenl, int* right, int lenr){
    int i = 0, j = 0, k = 0;
    while(i < lenl && j < lenr){
        if(left[i] <= right[j]){
            destiny[k] = left[i];
            i++;
        }else{
            destiny[k] = right[j];
            j++;
        }
        k++;
    }
    while(i < lenl){
        destiny[k] = left[i];
        i++;
        k++;
    }
    while(j < lenr){
        destiny[k] = right[j];
        j++;
        k++;
    }
}
//it divides the list into 2 iterativly until the whole list is divided into 1's, then it calls the merge function.
//very efficient in terms of time O(nlogn), but not efficient in terms of space O(n).
void mergeSort(int *arr, int length){
    if(length < 2){
        return;
    }
    int mid = length/2;
    int left[mid], right[length-mid];
    for(int i = 0; i < mid; i++){
        left[i] = arr[i];
    }
    for(int i = mid; i < length; i++){
        right[i-mid] = arr[i];
    }
    mergeSort(left, mid);
    mergeSort(right, length-mid);
    merge(arr, left, mid, right, length-mid);
}
// pushes all lesser element to last element(the pivot) to the left, and then puts the pivot next to the last lesser element to it.
//at the end all lesser element are at its left, and all greater are at its right. In no particular order.
// it returns the index of where the pivot was set.
int partition(int *arr, int start, int end){
    int partitionIndex = start;
    for(int i = start; i < end; i++){
        if(arr[i] <= arr[end]){
            int temp = arr[partitionIndex];
            arr[partitionIndex] = arr[i];
            arr[i] = temp;
            partitionIndex++;
        }
    }
    int temp = arr[partitionIndex];
    arr[partitionIndex] = arr[end];
    arr[end] = temp;
    return partitionIndex;
}
//this makes the quickSort algorithm most efficient by randomizing the pivot so that if the list is already sorted or kind of sorted
//it doesent iterate every element without making cuts. whith this implementation the algorithm average case time complexity is of O(nlogn)
int randomizedPartition(int *arr, int start, int end){
    int pindex = rand()%(end+1-start)+start;
    int temp = arr[pindex];
    arr[pindex] = arr[end];
    arr[end] = temp;
    return partition(arr, start, end);
}
//it call the partition method recursevly each time it makes the divides smaller by cutting the list at the place where the last pivot was set.
//at the end the list is cut to the point where there is only one element. at which point the elements are sorted.
//its an in place algorithm, making it very efficient in terms of space, and in average case,  it is also efficient in terms of time
void quickSort(int *arr, int start, int end){
    if(start < end){
        int pindex = randomizedPartition(arr, start, end);
        quickSort(arr, start, pindex-1);
        quickSort(arr, pindex+1, end);
    }
}

int main()
{
    int a[] = {2,4,2,1,7,4,3,3,0, 9,4,6,2,5,7,3,2,5,8,85,224,24,6,7,2,1,4,7,8,90,1,3};
    //seed to make the rand function actually random
    srand(time(NULL));
    quickSort(a,0, sizeof(a)/sizeof(a[0])-1);
    for(int i = 0; i < sizeof(a)/sizeof(a[0]); i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
