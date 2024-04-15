#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(){

    printf("\t\t\tMENU\n");
    printf("1. Agregar contacto\n");
    printf("2. Editar contacto\n");
    printf("3. Eliminar contacto\n");
    printf("4. Buscar contacto\n");
    printf("5. Listar agenda\n");
    printf("6. Salir\n");
    printf("Elige el numero correspondiente a la opcion que deseas: ");
    int opcion;
    scanf("%d", &opcion);
    return opcion;
}

void agregarContacto(int numDeContactos, int* contactosCreados, char (*agenda)[3][30]){
    if(*contactosCreados<numDeContactos){
        printf("Ingresa el nombre del contacto: ");
        scanf("%s", (*(agenda+*contactosCreados))[0]);
        _Bool noPase;
        do{
            noPase = 0;
            for(int i = 0; i < *contactosCreados; i++){
                if(!strcmp((*(agenda+*contactosCreados))[0], (*(agenda+i))[0])){
                    printf("Ese nombre ya existe, prisiona 's' si deseas continuar o presiona cualquier otra tecla para re introducir el nombre: ");
                    char opcion;
                    scanf(" %c", &opcion);
                    if(opcion == 's'){
                        break;
                    }else{
                        printf("Escribe el nuevo nombre: ");
                        scanf("%s", (*(agenda+*contactosCreados))[0]);
                        noPase = 1;
                        break;
                    }
                }
            }
        }while(noPase);
        printf("Ingresa su numero de telefono: ");
        scanf("%s", (*(agenda+*contactosCreados))[1]);
        printf("Ingresa su correo electronnico: ");
        scanf("%s", (*(agenda+*contactosCreados))[2]);
        ++*contactosCreados;
    }else{
        printf("Ya no se pueden agregar mas contactos porque la agenda esta llena. borra contactos si quieres agregar mas.\n");
    }
}

void modificarContacto(int *contactosCreados, char (*agenda)[3][30], void (*funcion)(int*, int, char (*agenda)[3][30])){
    if(*contactosCreados){
        printf("Introduce el nombre del contacto: ");
        char nombre[15];
        scanf("%s", nombre);
        int cuantos = 0;
        int indice = 0;
        for(int i = 0; i < *contactosCreados; i++){
            if(!strcmp((*(agenda+i))[0], nombre)){
                if(cuantos == 0){
                    indice = i;
                }
                cuantos++;
            }
        }
        if(cuantos>1){
            int indices[cuantos];
            int w = 0;
            for(int i = 0; i<*contactosCreados; i++){
                if(!strcmp((*(agenda+i))[0], nombre)){
                    indices[w] = i;
                    w++;
                }
            }
            int opcion = 0;
            _Bool bandera = 0;
            do{
                bandera = 0;
                printf("Existen %d %s en la agenda. A cual de ellos deseas modificar:\n", cuantos, nombre);
                for(int i = 0; i < cuantos; i++){
                    printf("%d. %s\t%s\t%s\n", i+1, (*(agenda+indices[i]))[0], (*(agenda+indices[i]))[1], (*(agenda+indices[i]))[2]);
                }
                printf("%d. Regresar al menu principal\n", cuantos+1);
                scanf("%d", &opcion);
                if(opcion<1 || opcion>cuantos+1){
                    printf("Esa opcion no existe. Vuelve a intentarlo\n");
                    bandera = 1;
                }else{
                    if(opcion == cuantos+1){
                        break;
                    }else{
                        funcion(contactosCreados, indices[opcion-1], agenda);
                    }
                }
            }while(bandera);
        }else{
            if(cuantos==1){
                funcion(contactosCreados, indice, agenda);
            }else{
                printf("El contacto no se encontro\n");
            }
        }
    }else{
        printf("la agenda esta vacia. primero agrega contactos\n");
    }
}

void editarContacto(int *contactosCreados, int indice, char (*agenda)[3][30]){
    printf("Escribe el nuevo nombre: ");
    scanf("%s", (*(agenda+indice))[0]);
    printf("Escribe su telefono: ");
    scanf("%s", (*(agenda+indice))[1]);
    printf("Escribe su correo: ");
    scanf("%s", (*(agenda+indice))[2]);
    printf("El contacto fue editado\n");
}

void eliminarContacto(int *contactosCreados, int indice, char (*agenda)[3][30]){
    strcpy((*(agenda+indice))[0], (*(agenda+indice+1))[0]);
    strcpy((*(agenda+indice))[1], (*(agenda+indice+1))[1]);
    strcpy((*(agenda+indice))[2], (*(agenda+indice+1))[2]);
    printf("El contacto fue eliminado\n");
    --*contactosCreados;
}

void buscarContacto(int contactosCreados, char (*agenda)[3][30]){
    if(contactosCreados){
        printf("Intoduce el nombre del contacto: ");
        char nombre[15];
        scanf("%s", nombre);
        _Bool imprime = 1;
        for(int i= 0; i < contactosCreados; i++){
            if(!strcmp((*(agenda+i))[0], nombre)){
                if(imprime){
                    printf("\t\t\tBusqueda\n");
                    printf("NOMBRE \t TELEFONO \t CORREO ELECTRONICO\n");
                    imprime = 0;
                }
                printf("%s\t%s\t%s\n", (*(agenda+i))[0], (*(agenda+i))[1], (*(agenda+i))[2]);
            }else if(i == contactosCreados-1 && imprime){
                printf("%s no eixte en la agenda\n", nombre);
            }
        }
    }else{
        printf("la agenda esta vacia. Primero agrega contactos.\n");
    }
}

void listarAgenda(int contactosCreados, char (*agenda)[3][30]){
    if(contactosCreados){
        printf("\t\t\tAgenda\n");
        printf("NOMBRE \t TELEFONO \t CORREO ELECTRONICO\n");
        for(int i = 0; i < contactosCreados; i++){
            printf("%s\t%s\t%s\n", (*(agenda+i))[0], (*(agenda+i))[1], (*(agenda+i))[2]);
        }
    }else{
        printf("La agenda esta vacia. Primero agrega contactos\n");
    }
}

int main()
{
    int numDeContactos;
    int contactosCreados = 0;
    printf("De que tamano sera la agenda?: ");
    scanf("%d", &numDeContactos);
    char agenda[100][3][30];
    int opcion;
    do{
        opcion = menu();
        switch(opcion){
            case 1:
                agregarContacto(numDeContactos, &contactosCreados, agenda);
                break;
            case 2:
                modificarContacto(&contactosCreados, agenda, editarContacto);
                break;
            case 3:
                modificarContacto(&contactosCreados, agenda, eliminarContacto);
                break;
            case 4:
                buscarContacto(contactosCreados, agenda);
                break;
            case 5:
                listarAgenda(contactosCreados, agenda);
                break;
            case 6:
                printf("Adios\n");
                break;
            default:
                printf("Esa opcion no existe. Vuleve a intentar\n");
        }
    }while(opcion!=6);
    return 0;
}
