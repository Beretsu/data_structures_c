#include <stdio.h>
#include <stdlib.h>
//guide: https://www.youtube.com/playlist?list=PL2_aWCzGMAwLz3g66WrxFGSXvSsvyfzCO
//array to store memory for memoizationFibonacci
int mem[100];

int factorial(int n){
    if(n == 0){
        return 1;
    }
    return n * factorial(n-1);
}
//example of a bad case to use recursion. some operations repeat.
int inefficientFibonacci(int n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return 1;
    }
    return inefficientFibonacci(n-1) + inefficientFibonacci(n-2);
}
//same as above function, but storing values that have already been calculate, this way we prevent redundancy(momoization).
//its space complexity is still worse than an iterative implementation.
int memoizationFibonacci(int n){
    //part of the logic for this function is in the main function
    if(mem[n] != -1){
        return mem[n];
    }
    mem[n] = memoizationFibonacci(n-1) + memoizationFibonacci(n-2);
    return mem[n];
}
//iterative implementation of Fibonacci. best implementation
int fibonacci(int n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return 1;
    }
    int f0 = 0;
    int f1 = 1;
    int f = 0;
    for(int i = 1; i < n; i++){
        f = f0+f1;
        f0 = f1;
        f1 = f;
    }
    return f;
}
//x: base, //n: exponential
//calculates exponentials
int powr(int x, int n){
    if(n == 0){
        return 1;
    }
    if(n%2==0){
        int e = powr(x, n/2);
        return e*e;
    }else{
        return x * powr(x, n-1);
    }
}
//calculates modulo of numbers elevated to an exponential
//done this way because doing otherwise could overflow the data type, in this case "int".
//x:base, n:exponential, m:modulo
int powmodulo(int x, int n, int m){
    if(n == 0){
        return 1;//this is not correct. but i dont whant to take care of this case
    }
    if(n%2==0){
        int y = powmodulo(x, n/2, m);
        return y*y%m;
    }
    return x%m*powmodulo(x, n-1, m)%m;
}

int main(){
    //this is to set the memory for memoizationFabonacci to empty. -1 signifies empty.
    for(int i = 0; i < 100; i++){
        mem[i] = -1;
    }
    int toFactorialize = 5;
    printf("factorial of %d is: %d\n",toFactorialize, factorial(toFactorialize));
    int toFibonace = 40;
    printf("fibonacci of %d is %d\n",toFibonace, fibonacci(toFibonace));
    printf("%d\n", memoizationFibonacci(toFibonace));
    int base = 5, exponential = 5;
    printf("%d to the power %d is: %d\n", base, exponential, powr(base,exponential));
    printf("powModulo: %d\n", powmodulo(2, 4, 2));
    return 0;
}
