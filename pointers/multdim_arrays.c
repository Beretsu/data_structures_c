#include <stdio.h>
#include <stdlib.h>
void func(int (*arr)[3]){ // = arr[][3]. its not an array variable block, its a pointer. the array has to be of size [][3], otherwise it wont work
printf("******************\n");
    for(int i = 0; i<2;i++){
        for(int j = 0; j<sizeof(*arr)/sizeof(**arr);j++){
            printf("%d\n", *(*(arr+i)+j));//= arr[i][j][k]
        }
    }
    printf("*******************\n");
}
void func2(int (*arr)[3][4]){// = arr[][3][4]. its not an array variable block, its a pointer. the array has to be of size [][3][4], otherwise it wont work
    printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
    for(int i =0;i<2;i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<4; k++){
                printf("%d\n", arr[i][j][k]);
            }
        }
    }
    printf(";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n");
}
int main()
{
    int a[] = {1,2,3,4,5};
    int* p = a; // pointer for a 1dimentional array points to an int, the first element of the array
    // int b[2][3]={{1,2,3},{3,2,1}}; // esto vuelve loco al programa, no enitendo porque
    int b[2][3];
    b[0][0] = 1;
    b[0][1] = 2;
    b[0][2] = 3;
    b[1][0] = 4;
    b[1][1] = 5;
    b[1][2] = 6;
    // pointer for 2dimentional array points to the first array. A block of memory of 3 integers (an array block, a variable array name)
    int (*p2)[3] = b; //it must be declared like this. this is a type of pointer to point to an array block of (in this case 3) elements
    int (*p3)[3] = &b; // this and the past line are the same thing
    int* ps = *b;
    int** ptop = &ps;
    printf("size of p2: %d. value: %ld\n",sizeof(p2), p2); // same as &b[0] or &*b or &*p2 but not the same as b (although they behave similar). this is not an array block
    printf("size of b: %d. value: %ld\n",sizeof(b), b); // not the same as p2 because theyr size is different and b cannot be changed unlike p2. this is an array block of 3
    printf("size of *p2: %d. value: %ld\n",sizeof(*p2),*p2); // same as b[0] or p2[0] or *b or *&*b but not the same as ps or &b[0][0]. this is an array block
    printf("size of *b: %d. value: %ld\n",sizeof(*b), *b); // same as b[0] or p2[0] or*p2 or *&*p2 but not the same as ps or &b[0][0]. this is an array block
    printf("size of ps: %d. value: %ld\n",sizeof(ps), ps); // same as &b[0][0]. this is not an array block
    printf("size of **p2: %d. value: %d\n",sizeof(**p2),**p2);//same as p2[0][0] or b[0][0] or **b
    printf("size of **b: %d. value: %d\n",sizeof(**b), **b); //same as p2[0][0] or b[0][0] or **p2
    printf("%ld\n",*(b+1)); //b[1] or p2[1] or *(p2+1). new_address= current_address + (number * size_of(data type))(in this case it adds 12 because b points to a data type of 12 bytes(b[0])
    printf("size of *(b+1)+2: %d. value: %ld\n",sizeof(*(b+1)+2), *(b+1)+2); // in this case it first adds 12, because b points to a data type of size 12 that is:b[0], then it direferences an it ads 2(4) to the adress, because b[1] points to an int, and because we are adding 2.
    printf("size of **(b+1)+2: %d. value: %d\n",sizeof(**(b+1)+2), **(b+1)+2);
    printf("%ld\n",&b[1][2]);
    printf("%d\n",b[1][2]);
    for(int i = 0; i<2;i++){
        for(int j = 0; j<3;j++){
            printf("%d\n", b[i][j]);
        }
    }
    func(b);
    //b[i][j] = *(b[i]+j) = *(*(b+i)+j)
    //--------------------------threedientional array-----------------
    printf("__________________________________Threedimentional arrays_____________________________\n");
    int c[2][3][4]={{{1,2,3,4},{4,3,2,1},{5,6,7,8}},{{8,7,6,5},{6,7,8,9},{0,9,8,7}}};
    int (*pp)[3][4] = c; //pointer to an array of 2 elements that each contain 3 arrays that contain 4 ints. array block name
    for(int i =0;i<2;i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<4; k++){
                printf("%d\n", c[i][j][k]);
            }
        }
    }
    printf("urrrrrrrrrrrrurrrrru----func-------");
    func2(c);
    //c[i][j][k] = *(c[i][j]+k) = *(*(c[i]+j)+k) == *(*(*(c+i)+j)+k)
}
