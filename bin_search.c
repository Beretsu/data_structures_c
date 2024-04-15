#include <stdio.h>
#include <stdlib.h>

//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwL3ldWlrii6YeLszojgH77j

int binarySearch(int *array, int length, int key){
    int low =0, high = length-1, current;
    while(low <= high){
        current =low + (high - low)/2; // same as (high+low)/2, but betterbecause it aoids overflow.
        if(array[current] == key){
            return current;
        }else if(key < array[current]){
            high = current-1;
        }else{
            low = current+1;
        }
    }
    return -1; // if element is not found
}

int recursiveBinarySearch(int *arr, int low, int high, int value){
    if(low > high){
        return -1;
    }
    int midle = low + (high - low)/2;
    if(value == arr[midle]){
        return midle;
    }
    if(value > arr[midle]){
        return recursiveBinarySearch(arr, midle+1, high, value);
    }
    return recursiveBinarySearch(arr, low, midle, value);
}
//returns the fist ocurrance of the key if flag == 0, else it returns the last ocurrance
int OcurranceBinarySearch(int *array, int length, int key, int flag){
    int low = 0, high = length-1, current, result = -1;
    while(low <= high){
        current = low + (high - low)/2; // same as (high+low)/2, but better because it avoids overflow.
        if(array[current] == key){//in case it has found the element it continues looking for adyacent elements until it finds the selected ocurrance if it exists, else it returns the only ocurrance
            result = current;
            if(flag){
                low = current+1;
            }
            else{
                high = current-1;
            }
        }else if(key < array[current]){
            high = current-1;
        }else{
            low = current+1;
        }
    }
    return result;
}
//it memorize where the fist ocurrance of the key is and if there is a fist ocurrance, it memorizes the last ocurrance, theen it returns the difference between the last and the first -1
int countOcurrance(int *arr, int length, int key){
    int first = OcurranceBinarySearch(arr, length, key, 0);
    int last;
    if(first != -1){
        last = OcurranceBinarySearch(arr, length, key, 1);
        return last-first+1;
    }
    return -1;
}
//this refers to a circular list. it returns the number of times the array is rotated. example: {7, 8, 9, 2, 3, 4, 5} is rotated 3 times. in this case 2 is the pivot.
//pivot has the property that it's the only one where the number before it is greater than its self.
//the numer of times the list is rotated coincides with the inndex of the pivot.
//this algorithm follows the logic of binary search.
//it doesent work if there are repeated elements. if that is the case there is no better option than linear search
int numRotations(int *arr, int length){
    if(arr[0] < arr[length-1] || length == 1){
        return 0;//the list is sorted
    }
    int start = 0, end = length-1, middle;
    while(start <= end){
        middle = start + (end-start)/2;
        if(arr[middle] < arr[(middle+length-1)%length]){//"(middle+length-1)%length" gives us the previous element to middle, for a circular array
            return middle;
        }else if(arr[middle] < arr[end]){
            end = middle-1;
        }else{
            start = middle+1;
        }
    }
    return -1;
}
//finds a key in a rotated array, divides the array in 2 and it searches the subarray if the array is sorted, we know if the arraay is sorted if the middle element is lesser than the last element in the case of the right sub array
//and if the middle element is greater than the first element in the case of the left subarray.
//at least one subarray is always sorted, if the element we are searching for is in the subaray tha is not sorted, we cut the subarray and we repeat the proces
//it doesent work if there are repeated elements. if that is the case there is no better option than linear search
int rotatedSearch(int *arr, int length, int key){
    int low = 0, high = length-1, middle;
    while(low <= high){
        middle = low +(high-low)/2;
        if(arr[middle] == key){
            return middle;
        }
        if(arr[middle] < arr[high]){
            if(key > arr[middle] && key <= arr[high]){
                low = middle+1;
            }else{
                high = middle-1;
            }
        }else{
            if(key < arr[middle] && key >= arr[low]){
                high = middle-1;
            }else{
                low = middle+1;
            }
        }
    }
    return -1;
}

int main(){
    int array[] = {1,2,3,4,5,6,7,8,9,12,12,12,12,12,16,17,18,20};
    int size = sizeof(array) / sizeof(array[0]);
    int toSearch = 20;
    int a = recursiveBinarySearch(array, 0, size-1, toSearch);
    printf("recursiveBinarySearch for %d: %d\n", toSearch, a);
    int tofind = 12;
    printf("the fist ocurrance of %d is: %d\n", tofind, OcurranceBinarySearch(array, size, tofind, 0));
    printf("number of ocurrances for %d is: %d\n", tofind, countOcurrance(array, size, tofind));
    int arr[] = {1, 0, 1, 1, 1, 1, 1, 1, 1};
    //it doesent work if the elements are repeated
    printf("number of rotations for arr is: %d\n", numRotations(arr, size));
    printf("searched 0 in a rotated list: %d\n", rotatedSearch(arr, sizeof(arr) / sizeof(arr[0]), 0));
    return 0;
}
