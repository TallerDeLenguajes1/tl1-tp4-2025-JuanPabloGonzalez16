#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct{
    int duracion;
    int id;
    char * descripcion;
}typedef Tarea;
typedef struct Nodo{
    Tarea Tarea;
    struct Nodo * siguiente;
}Nodo;
Nodo * crearLista();
Nodo * crearNodo(Tarea tarea);
void insertarNodo(Nodo ** start, Nodo*nodo);
void mostrarLista(Nodo ** start);
Nodo * realizadas(Nodo ** start);
int main(){
    int opcion;
    char palabra[30];
    int tamanio;
    int id = 1000;
    Nodo * TareasPendientes = crearLista();
    Nodo * TareasRealizadas = crearLista();
    Tarea tarea;
    
    do{
        printf("Ingrese la descripcion de su tarea:");
        scanf("%s",palabra);
        tamanio = strlen(palabra) + 1;
        tarea.descripcion = (char*)malloc(sizeof(char)* tamanio);
        strcpy(tarea.descripcion,palabra);
        printf("\nIngrese la duracion:");
        scanf("%d",&tarea.duracion);
        tarea.id = id;
        fflush(stdin);
        
        insertarNodo(&TareasPendientes,crearNodo(tarea));
        printf("\nIngrese 1 para poner mas tareas:\n");
        scanf("%d",&opcion);
        id++;
    }while(opcion == 1);
    mostrarLista(&TareasPendientes);
    
    return 0;

}
Nodo * crearLista(){
    return NULL;
}
Nodo * crearNodo(Tarea tarea){
    Nodo * nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->Tarea = tarea;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}
void insertarNodo(Nodo ** start, Nodo*nodo){
    nodo->siguiente = *start;
    *start = nodo;
}
void mostrarLista(Nodo **start){
    Nodo * Aux;
    Aux = *start;
    while(Aux != NULL){
        printf("Id de la tarea : %d\n",Aux->Tarea.id);
        printf("Duracion de la tarea : %d\n",Aux->Tarea.duracion);
        printf("Descripcion de la tarea: %s\n",Aux->Tarea.descripcion);
        Aux = Aux->siguiente;
    }
}
/*2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
transferidas a la lista de tareas realizadas.*/
Nodo * realizadas(Nodo ** start){
    Nodo * Aux;
    int opcion;
    Aux = *start;
   
}