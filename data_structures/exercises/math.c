#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../stack_array.h" // for findFactors

// guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwLL-mEB4ef20f3iqWMGWa25
int isPrime(int n){
    int root = sqrt(n);
    for(int i = 2; i <= root; i++){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}

//find prime numbers upto n.
void SieveofEratosthenes(int *arr, int length){
    if(length > 2){
        arr[0] = 0;
        arr[1] = 0;
        for(int i = 2; i < length; i++){
            arr[i] = 1;
        }
        double root = sqrt(length-1);
        for(int i = 2; i < root; i++){
            if(arr[i] == 1){
                for(int j = 2; i*j < length; j++){
                    arr[i*j] = 0;
                }
            }
        }
    }else{
        for(int i = 0; i < length; i++){
            arr[i] = 0;
        }
    }
}

//find dividers
void findFactors(int *arr, int n){
    int root = sqrt(n);
    int count = 0;
    for(int i = 1; i <= root; i++){
        if(n%i == 0){
            arr[count] = i;
            if(i != root){
                push(n/i);
            }
            count++;
        }
    }
    while(!isEmpty()){
        arr[count] = Top();
        pop();
        count++;
    }
    arr[count] = -1;
}

void primeFactorization(int n){
    for(int i = 2; i < sqrt(n); i++){
        int count = 0;
        if(n%i == 0){
            while(n%i == 0){
                count++;
                n = n/i;
            }
            printf("%d^%d", i, count);
            if(n != 1){
                printf(" * ");
            }
        }
    }
    if(n!= 1){
        printf("%d", n);
    }
}

//euclid's algorithm O(log b)
int GreaterCommunDivisor(int a, int b){
    while(b){
        int remander = a%b;
        a = b;
        b = remander;
    }
    return b;
}

int main()
{
    int num = 23;
    int u = isPrime(num);
    if(u){
        printf("%d is a prime number", num);
    }
    int arr[53];
    int arrSize = sizeof(arr)/ sizeof(arr[0]);
    //finds prime numbers upto 52.
    SieveofEratosthenes(arr, arrSize);
    printf("prime numbers up to %d: ", arrSize-1);
    for(int i = 0; i < arrSize; i++){
        if(arr[i]){
            printf("%d ", i);
        }
    }
    int arr2[30];
    int num2 = 456;
    findFactors(arr2, num2);
    int c = 0;
    printf("\nfactors (dividers) of %d: ", num2);
    while(arr2[c]!=-1){
        printf("%d ", arr2[c]);
        c++;
    }
    printf("\nprime factorization of %d: ", num2);
    primeFactorization(456);
    return 0;
}
