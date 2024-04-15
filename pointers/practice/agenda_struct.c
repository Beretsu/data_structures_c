#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct contacto{
    char nombre[15];
    char telefono[15];
    char correo[30];
    struct contacto *next;
}contacto;

void migets(char* var, int buf){
    fgets(var, buf, stdin);
    char *p;
    if(p = strchr(var, '\n')){
        *p = '\0';
    }
}

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

contacto* agregarContacto(contacto *head, int pos){
    contacto *temp = (contacto*)malloc(sizeof(contacto));
    temp->next = NULL;
    printf("Introduce el nombre del contacto: ");
    migets(temp->nombre, 15);
    _Bool noPase = 0;
    do{
        noPase = 0;
        contacto *iterador = head;
        while(iterador){
            if(!strcmp(temp->nombre, iterador->nombre)){
                printf("%s ya existe en la agenda. presiona 's', o 'S' si deseas dejarlo asi, o presiona cualquier otra tecla para re- introducir el nombre: ");
                char opcion;
                opcion = getchar();
                char c;
                while((c = getchar()) != '\n' && c != EOF);
                if(tolower(opcion)!='s'){
                    printf("Reescrible el nombre: ");
                    migets(temp->nombre, 15);
                    noPase = 1;
                }
                break;
            }
            iterador = iterador->next;
        }
    }while(noPase);
    printf("Introduce el telefono del contacto: ");
    migets(temp->telefono, 15);
    printf("Introduce el correo del contacto: ");
    migets((*temp).correo, 30);
    if(pos == 0){
        if(head){
            temp->next = head;
            head = temp;
        }else{
            head = temp;
        }
    }else if(pos < 0 ){
        contacto *temp2 = head;
        if(temp2){
            while(temp2->next){
                temp2 = temp2->next;
            }
            temp2->next = temp;
        }else{
            head = temp;
        }
    }else{
        int contador = 0;
        contacto *temp2 = head;
        while(temp2){
            contador++;
            temp2 = temp2->next;
        }
        if(pos <= contador){
            temp2 = head;
            for(int i = 0; i < pos-1; i++){
                temp2 = temp2->next;
            }
            temp->next = temp2->next;
            temp2->next = temp;
        }else{
            printf("No se puede agregar un contacto en esa posicion, la lista tiene que crecer a %d contactos para ello\n", pos);
        }
    }
    return head;
}

contacto* agregarContactoAlFinal(contacto *head){
    return agregarContacto(head, -1);
}

void modificarContacto(contacto **head, void (*funcion)(contacto**, char*, int)){
    if(*head){
        printf("Introduce el nombre del contacto: ");
        char nombre[15];
        migets(nombre, 15);
        int conteo = 0;
        contacto *temp = *head;
        while(temp){
            if(!strcmp(temp->nombre, nombre)){
                conteo++;
            }
            temp = temp->next;
        }
        temp = *head;
        if(conteo > 1){
            _Bool bandera = 0;
            do{
                bandera = 0;
                int n = 0;
                printf("Existen %d %s en la agenda, a cual de ellos deseas modificar?\n", conteo, nombre);
                while(temp){
                    if(!strcmp(temp->nombre, nombre)){
                        n++;
                        printf("%d. %s\t%s\t%s\n", n, temp->nombre, temp->telefono, temp->correo);
                        if(n == conteo){
                            break;
                        }
                    }
                    temp = temp->next;
                }
                printf("%d Regresar al menu principal\n", conteo+1);
                printf("Elige el numero correspondiente a la opcion que deseas: ");
                scanf("%d", &n);
                char c;
                while((c = getchar()) != '\n' && c != EOF);
                if(n>conteo+1 || n<1){
                    printf("Esa opcion no existe. Vuelve a intentarlo\n");
                    bandera = 1;
                }else if(n == conteo+1){
                    break;
                }else{
                    funcion(head, nombre, n);
                }
            }while(bandera);
        }else{
            if(conteo == 1){
                funcion(head, nombre, 1);
            }else{
                printf("El contacto no existe en la agenda\n");
            }
        }
    }else{
        printf("La agenda esta vacia, primero agrega contactos\n");
    }
}

void editarContacto(contacto **head, char* nombre, int indice){
    int conteo = 0;
    contacto *temp = *head;
    while(temp){
        if(!strcmp(temp->nombre, nombre)){
            conteo++;
            if(conteo == indice){
                printf("Introduce el nuevo nombre: ");
                migets(temp->nombre, 15);
                printf("Introduce el nuevo telefono: ");
                migets(temp->telefono, 15);
                printf("Introduce el  nuevo correo del contacto: ");
                migets(temp->correo, 30);
                break;
            }
        }
        temp = temp->next;
    }
}

void eliminarContacto(contacto **head, char *nombre, int indice){
    int conteo = 0;
    int conteo2 = 0;
    contacto *temp = *head;
    while(temp){
        conteo2++;
        if(!strcmp(temp->nombre, nombre)){
            conteo++;
            if(conteo == indice){
                if(conteo2 == 1){
                    *head = (*head)->next;
                    free(temp);
                    break;
                }
                contacto *tempMinus1 = *head;
                for(int i = 0; i < conteo2-2; i++){
                    tempMinus1 = tempMinus1->next;
                }
                tempMinus1->next = temp->next;
                free(temp);
                break;
            }
        }
        temp = temp->next;
    }
}

void buscarContacto(contacto *head){
	printf("Introduce el nombre del contacto a buscar: ");
	char nombre[15];
	migets(nombre, 15);
	contacto *temp = head;
	int conteo = 0;
	if(temp){
		while(temp){
			if(!strcmp(temp->nombre, nombre)){
				conteo++;
				printf("%s\t%s\t%s\n", temp->nombre, (*temp).telefono, temp->correo);
			}
			temp = temp->next;
		}
		if(!conteo){
			printf("Ese contacto no existe en la agenda\n");
		}
	} else {
		printf("La agenda esta vacia, primero agrega contactos\n");
	}
}

void listarAgenda(contacto *head){
    if(head){
        while(head){
            printf("%s\t%s\t%s\n", head->nombre, head->telefono, head->correo);
            head = head->next;
        }
    }else{
        printf("La agenda esta vacia, primero agrega contactos\n");
    }
}

int main()
{
    contacto *head = NULL;
    int opcion;
    do{
        opcion = menu();
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch(opcion){
            case 1:
                head = agregarContactoAlFinal(head);
                break;
            case 2:
                modificarContacto(&head, editarContacto);
                break;
            case 3:
                modificarContacto(&head, eliminarContacto);
                break;
            case 4:
                //buscarContacto(contactosCreados, agenda);
                break;
            case 5:
                listarAgenda(head);
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
