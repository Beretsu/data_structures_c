#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print(const char* c){// const is like final in java. it prevents the value to be modified. this is relevant here because
//arrays as arguments in functions are called by reference
    while(*c!='\0'){
        printf("%c",*c);
        c++;
    }
    printf("\n");
}
int main()
{
    //string are char arrays in c. to store a string, the array must be of suficient size; length of the string+1,
    //thats because it must end with a null character '\0' to notify that the string has ended.

    //en este caso no terminamos el string con un '\0' y por ese motivo nos imprime caracteres basura, ya que no sabe dond ese acaba el string
    char arr[20];
    arr[0] = 'j';
    arr[1] = 'u';
    arr[2] = 'a';
    arr[3] = 'n';
    //arr[4] = '\0'; //si descomentamos esta linea el problema se arregla
    printf("%s\n", arr);
    char palabra[]= "palabra"; //this is a string literal. it implicitly adds '\0' at the end. there is no need to specify the size of the array when
    // declaring string literals. its size is length of the string+1.
    //palabra = "nueva"; //this cant be done.
    char arreglo[]= {'p','a','n','c','h','o','\0'}; // asi es necesario poner el '\0' manualmente
    printf("%s\n", arreglo);
    int len = strlen(arreglo); // = 6. excluye a '\0'. string fuctions expect a '\0' in a char array
    int tamano = sizeof(arreglo); // =7
    printf("len: %d, tamano: %d\n", len, tamano);
    printf("%c\n", *(arreglo +2)); // *(arreglo +2) == arreglo[2]
    char* p = arreglo;
    printf("%c\n", p[2]); //p[2] == *(p+2);
    //se puede cambiar el valor de p, pero no se puede cmbiar el valor de arreglo
    print(arreglo);
    char* f = "Pedro";// in cases where string literals is used somewhere else other than in a char array it is a constant. like in this case
    print(f);
    printf("hola"); //and like in this case
    return 0;
}
