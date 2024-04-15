#include <stdio.h>
#include <stdlib.h>

/*a program's memory is divided in 4: code(text), global/static, stack, and heap.
the not global/static information in a program is allocated in the stack as it runs. the stack deallocates
the memory from the stack once the running function finishes running. all kinds of memory except for the heap are fixed
and not controllable for the user. If we want to have controll over the memory, we allocate memory in the heap, and since
the stack memory is fixed, we also need to allocate any large data in the heap, to avoid
stackoverflow(stack running out of memory). having control over memory could mean controlling when the memory gets deallocated*/

int main()
{
    int a; //goes on the stack
    int* p;
    p = (int*)malloc(sizeof(int));/*allocates memory int the heap, we have to specify how much memory to allocate
                                    it returns a pointer of type void (void*), we have to cast it to be able to use the momory.
                                    in this case we cast it to ponter to an int, to store an int
                                    */
    *p = a; // the only way to acces memory in the heap is throw a pointer
    free(p);//whenever we stop needing the data, it is important to free the memory in the heap to avoid memory leak.
    p = (int*)malloc(5*sizeof(int)); // to store an array we have to specify the size in bytes of the array block
    //if malloc cant allocate memory, it returns NULL. the size cannot be smaller or equal to 0 (unsigned int)
    //p =(int[5]){1,2,3,4,5}; no. i dont know what this is
    //int p[] = {3,4,3,2,2}; no se puede
    //void pointer cant be dereferenced. to do so it has to be casted
    p[0] = 4;
    p[1] = 0;
    p[2] = 3;
    p[3] = 8;
    p[4] = 2;
    printf("size of p: %d. value: %ld\n",sizeof(p),p);
    for(int i = 0; i<5; i++)
    {
        printf("%d\n",p[i]);
    }
    free(p);
    char* b = (char*)calloc(8, sizeof(char));//its just like malloc(), but it recieves as parameters the number of elemnts, and the size of the data types.
    //unlike malloc, calloc sets all values in memory to 0.
    b[0]='D';
    b[1]='i';
    b[2]='l';
    b[3]='l';
    b[4]='i';
    b[5]='a';
    b[6]='n';
    b[7]='\0';
    int o = 0;
    while(*(b+o)!='\0'){
        printf("%c",*(b+o));
        o++;
    }
    printf("\n");
    free(b);//freeing up the memory from the heap. once we free the memory, we are still able to acces it and modify it, that can be dangerous
    int n;
    printf("inserta n num");
    scanf("%d",&n);
    int array[n];
    for(int i = 0;i<n;i++){
        array[n]=i+1;
        printf("%d\n",array[n]);
    }
    int *pp = (int*)malloc(n* sizeof(int));
    for(int i =0; i<n;i++){
        *(pp+i)= i+1;
        printf("%d\n",*(pp+i));
    }
    pp = (int*)realloc(pp, 2*n*sizeof(int));// changes the size of the memory allocated. recieves as parameters the pointer to the momory to resize, and the desired size
    //if desired size is ==0, then it does the same as the free() function. if the desired size is to large it copies de data from where it si located in memory, and it reallocates it somewhere where it fits
    for(int i =0; i<2*n;i++){
        *(pp+i)= i+1;
        printf("%d\n",*(pp+i));
    }
    free(pp);
    int* y = realloc(NULL,5*sizeof(int));//same as malloc
    free(y);
    return (0);
}
