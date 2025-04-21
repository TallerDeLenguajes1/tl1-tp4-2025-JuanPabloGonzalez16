#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Tarea{
    int duracion;
    char * descripcion;
    int id;
}Tarea;

typedef struct Nodo{
    Tarea tarea;
    struct Nodo * siguiente;
}Nodo;
Nodo * crearLista();
Nodo * crearNodo(Tarea tarea);
void insertar(Nodo **Start , Nodo *nodo);
void mostrarElementos(Nodo *Start);
Nodo * encontrarElemento(Nodo * Start, char *palabra);
Nodo * borrarElemento(Nodo ** Start, char *palabra);
void consultarID(Nodo ** L1, Nodo ** L2,int id);
void consultarPalabraClave(Nodo **L1,Nodo **L2,char *palabra);

int main(){
    int opcion;
    Tarea tarea;
    char palabra[30];
    int longitud;
    int indice = 1000;
    Nodo * TareasPendientes = crearLista();
    Nodo * TareasRealizadas = crearLista();
    //Agregar Tareas a la lista de pendientes
    do{
        printf("Ingrese la descripcion de su tarea:");
        scanf("%s",&palabra);
        longitud = strlen(palabra) + 1;
        tarea.descripcion = (char*)malloc(sizeof(char) * longitud);
        strcpy(tarea.descripcion,palabra);
        fflush(stdin);
        printf("\nIngrese los minutos que le tomara:");
        scanf("%d",&tarea.duracion);
        tarea.id = indice;
        Nodo * Nuevo = crearNodo(tarea);
        insertar(&TareasPendientes,Nuevo);
        indice ++;
        printf("\nIngrese:\n1)Para insertar mas nodos\n0)Para salir\n");
        scanf("%d",&opcion);
    }while(opcion != 0);
    mostrarElementos(TareasPendientes);

    //Aqui implementare una interfaz para indicar que tareas deben ser pasadas a la lista Realizadas//
    int seguir;
    Tarea tareaCopia;
    printf("\nIngrese:\n1)Si quiere seguir agregando tareas a realizadas\n0)Si desea salir\n");
    scanf("%d",&seguir);
    do{
        fflush(stdin);
        printf("\nIngrese La Tarea Que Debe Ser Transferida a la Lista de Tareas Realizadas:");
        // Codigo // //Que transferira la tarea a la lista TareasRealizadas//
        scanf("%s",&palabra);
        longitud = strlen(palabra) + 1;
        fflush(stdin);

        //1)Encontrar el elemento En La Lista De Tareas Pendientes
        Nodo * pendiente = encontrarElemento(TareasPendientes,palabra);
        printf("\nNodo encontrado\nTarea: %s - ID: %d - Duracion: %d minutos\n",pendiente->tarea.descripcion,pendiente->tarea.id,pendiente->tarea.duracion);
        //2)Insertar el elemento en la lista de Tareas Realizadas
        tareaCopia.duracion = pendiente->tarea.duracion;
        tareaCopia.id = pendiente->tarea.id;
        int len = strlen(pendiente->tarea.descripcion) + 1;
        tareaCopia.descripcion = (char*)malloc(len * sizeof(char));
        strcpy(tareaCopia.descripcion, pendiente->tarea.descripcion);
        
        // Crear nuevo nodo con la copia
        Nodo * nodoCopia = crearNodo(tareaCopia);
        insertar(&TareasRealizadas, nodoCopia);
        //3)Borrar El elemento de la lista de Tareas Pendientes 
        TareasPendientes = borrarElemento(&TareasPendientes,palabra);
        printf("\nIngrese:\n1)Si quiere seguir agregando tareas a realizadas\n0)Si desea salir\n");
        scanf("%d",&seguir);
    }while(seguir != 0);
    printf("Tareas Realizadas:\n");
    mostrarElementos(TareasRealizadas);
    printf("Tareas Pendientes:\n");
    mostrarElementos(TareasPendientes);
    int opcion3;
    int id;
    char palabraClave[30];
    printf("Ingrese:\n1)Si quiere buscar Tareas por id\n2)Si quiere buscar Tareas por Palabra\n0)Si desea salir\n");
    scanf("%d",&opcion3);
    do{
        fflush(stdin);
        switch(opcion3){
            case 1: printf("Ingrese la id:\n");
                    scanf("%d",&id);
                    consultarID(&TareasPendientes,&TareasRealizadas,id);
            break;
            case 2: printf("Ingrese la palabra:\n");
                    scanf("%s",&palabraClave);
                    consultarPalabraClave(&TareasPendientes,&TareasRealizadas,palabraClave);
            break;
        }
        printf("Ingrese:\n1)Si quiere buscar Tareas por id\n2)Si quiere buscar Tareas por Palabra\n0)Si desea salir\n");
        scanf("%d",&opcion3);
        fflush(stdin);
    }while(opcion3 != 0);
    return 0;
}
Nodo * crearLista(){
    return NULL;
}
Nodo * crearNodo(Tarea tarea){
    Nodo * nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->tarea = tarea;
    nuevo->siguiente = NULL;
    return nuevo;
}
void insertar(Nodo **Start , Nodo *nodo){
    nodo->siguiente = *Start;
    *Start = nodo;
}
void mostrarElementos(Nodo *Start){
    Nodo * Aux = Start;
    while(Aux != NULL){
        printf("Descripcion de la tarea: %s - ID: %d - Duracion: %d Minutos\n",Aux->tarea.descripcion,Aux->tarea.id,Aux->tarea.duracion);
        Aux = Aux->siguiente;
    }
}
Nodo * encontrarElemento(Nodo * Start, char *palabra){
    Nodo * Aux;
    Aux = Start;
    while(Aux != NULL && (strcmp(Aux->tarea.descripcion,palabra) != 0)){
        Aux = Aux->siguiente;
    }
    return Aux;
}
Nodo * borrarElemento(Nodo ** Start, char *palabra) {

        Nodo * actual = *Start;
        Nodo * anterior = NULL;
    
        while (actual != NULL && strcmp(actual->tarea.descripcion, palabra) != 0) {
            anterior = actual;
            actual = actual->siguiente;
        }
    
        if (actual != NULL) {
            if (anterior == NULL) {
                // El nodo a borrar es el primero
                *Start = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            free(actual);
        }
    
        return *Start;
}
void consultarID(Nodo ** L1, Nodo ** L2,int id){
    Nodo * Pendientes = *L1;
    Nodo * Realizadas = *L2;
    Nodo * encontradaPendiente = NULL;
    Nodo * encontradaRealizada = NULL;

    // Buscar en la lista de pendientes
    while(Pendientes != NULL && encontradaPendiente == NULL){
        if(Pendientes->tarea.id == id){
            encontradaPendiente = Pendientes;
        }
        Pendientes = Pendientes->siguiente;
    }

    // Buscar en la lista de realizadas
    while(Realizadas != NULL && encontradaRealizada == NULL){
        if(Realizadas->tarea.id == id){
            encontradaRealizada = Realizadas;
        }
        Realizadas = Realizadas->siguiente;
    }

    // Mostrar resultados
    if(encontradaPendiente != NULL){
        printf("Su Tarea Corresponde A La Lista De Pendientes\nTarea: %s - ID: %d - Duracion: %d\n",
               encontradaPendiente->tarea.descripcion,
               encontradaPendiente->tarea.id,
               encontradaPendiente->tarea.duracion);
    }

    if(encontradaRealizada != NULL){
        printf("Su Tarea Corresponde A La Lista De Realizadas\nTarea: %s - ID: %d - Duracion: %d\n",
               encontradaRealizada->tarea.descripcion,
               encontradaRealizada->tarea.id,
               encontradaRealizada->tarea.duracion);
    }

    if(encontradaPendiente == NULL && encontradaRealizada == NULL){
        printf("Su tarea no se encontro\n");
    }
}
void consultarPalabraClave(Nodo **L1, Nodo **L2, char *palabra) {
    Nodo *Pendientes = *L1;
    Nodo *Realizadas = *L2;
    Nodo *encontradoPendiente = NULL;
    Nodo *encontradoRealizada = NULL;

    
    while (Pendientes != NULL && encontradoPendiente == NULL) {
        if (strstr(Pendientes->tarea.descripcion, palabra) != NULL) {
            encontradoPendiente = Pendientes; 
        }
        Pendientes = Pendientes->siguiente;
    }

    
    while (Realizadas != NULL && encontradoRealizada == NULL) {
        if (strstr(Realizadas->tarea.descripcion, palabra) != NULL) {
            encontradoRealizada = Realizadas;
        }
        Realizadas = Realizadas->siguiente;
    }

    
    if (encontradoPendiente != NULL) {
        printf("La tarea corresponde a la lista de PENDIENTES:\n");
        printf("Tarea: %s - ID: %d - Duración: %d minutos\n",
               encontradoPendiente->tarea.descripcion,
               encontradoPendiente->tarea.id,
               encontradoPendiente->tarea.duracion);
    }

    if (encontradoRealizada != NULL) {
        printf("La tarea corresponde a la lista de REALIZADAS:\n");
        printf("Tarea: %s - ID: %d - Duración: %d minutos\n",
               encontradoRealizada->tarea.descripcion,
               encontradoRealizada->tarea.id,
               encontradoRealizada->tarea.duracion);
    }

    if (encontradoPendiente == NULL && encontradoRealizada == NULL) {
        printf("No se encontró ninguna tarea con esa palabra clave.\n");
    }
}