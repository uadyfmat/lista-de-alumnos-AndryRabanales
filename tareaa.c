#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Alumno {//Este codigo declara el tipo de dato struct Alumno coomo(Alumno)
    char *alumno;///////Declaramos los dato de char, tipo puntero porque no sabemos la cantidad de caracteres.
    int creditos;////// 
    int semestre;//////   
} alumno;//////////////nombre para referirnos a struct alumno

struct nodo {/////////// declaramos la cabecera llamada struct nodo
    alumno *alumnos;////declaramos un puntero hacia struct Alumno
    struct nodo *ptr;///declaramos un puntero hacia al siguiente nodo
};

typedef struct nodo NODO;////definimos struct nodo como "NODO"
typedef NODO * nodoptr;/////definimos "NODO *" como nodoptr

// FIRMAS
alumno* crearAlumno(char *, int, int);////En esta funcion agregaremos todos los datos solicidados y retornara una dir de memoria
void imprimirAlumno(alumno *);///////////En esta 
void imprimirDireccion(alumno *);
void imprimirNodoDireccion(nodoptr lista);
NODO* crearNodo(alumno *);
int insertarNodoOrdenadoCreditos(nodoptr *, NODO *);
void imprimirLista(nodoptr);

int main() {
    //crear 5 instancias de estructuras Alumno
    //obtenemos la direccion de memoria de cada una
    alumno *nombre1 = crearAlumno("Andry Rabanales", 70, 5);//se devuelve la dir de nuevoAlumno a la variable nombre 1
    alumno *nombre2 = crearAlumno("Carlos Ek", 90, 4);//
    alumno *nombre3 = crearAlumno("Russel Bonilla", 30, 6);//Le agregamos las instancias de alumno
    alumno *nombre4 = crearAlumno("Emiliano Arceo", 110, 5);//
    alumno *nombre5 = crearAlumno("Mario Irabien", 80, 3);//

//////////////////////////////////////////////////////////////////////
//////////CREAMOS LOS NODOS ENLAZADOS CON LOS ALUMNOS////////////////
/////////////////////////////////////////////////////////////////////



//Es un puntero de tipo struct nodo y apunta a sus intancias.
    NODO *lista = NULL; //creamos la cabecera de struct nodo
    //crear la lista con las 5 instancias de Alumno
                            //(direccion Nula, direccion del nodo creado)
                            //NO HA ENLAZADO NINGUN NODO, HASTA PASAR A LA FUNCION DE INSERTAR-NODO-ORDENADO
    insertarNodoOrdenadoCreditos(&lista, crearNodo(nombre1));//METE LAS DIRECCIONES DE STRUCT ALUMNO
                             //(NODO1, NUEVO NODO'NODO2')
    insertarNodoOrdenadoCreditos(&lista, crearNodo(nombre2));// Aqui lista ya tiene la direccion de NODO1
    insertarNodoOrdenadoCreditos(&lista, crearNodo(nombre3));
    insertarNodoOrdenadoCreditos(&lista, crearNodo(nombre4));
    insertarNodoOrdenadoCreditos(&lista, crearNodo(nombre5));
                    /*          ^              */
                     /*        /|\             */
                    /*          |              */
//////////////////////////////////////////////////////////////////////
///FINALIZANDO INSERTAR-NODO-FINAL, ya esta todo enlazado entre si////
/////////////////////////////////////////////////////////////////////


    //insertar de forma ordenada de acuerdo al número de créditos (descendente)
    // se va a guardar la cabecera(El alumno con mas creditos) en temp
    NODO *temp = lista;//Lista es la direccion de la cabecera(el primero nodo de la lista, la entrada)
    while (temp != NULL) {
        imprimirDireccion(temp->alumnos);
        temp = temp->ptr;// ahora temp es el siguiente nodo
    }
    printf("\n");
    imprimirNodoDireccion(lista);
    printf("\nImpresion de la lista de Alumnos(Creditos ascendientes)\n\n");
    //imprimir la lista
    imprimirLista(lista);

    return 0;
}
//////////////////////////////////////////////////////////////////////
/////////////////CREA LA ESTRUCTURA DE ALUMNO//////////////////////// 
/////////////////////////////////////////////////////////////////////

/*Indicamos con alumno * que se devuelve un ptr de ese tipo*/
 alumno* crearAlumno(char *nombre, int creditos, int semestre) {///se puede usar el puntero porque los datos ingresados son cadenas con termiancion '\0'
    alumno *nuevoAlumno = (alumno *)malloc(sizeof(alumno));/////creamos los bytes necesitados con malloc,(char,int,int)
    // luego indicamos que esta direccion sera de tipo struct ya que es necesario indicar de que tipo es los bytes ocupados(struct), finalmente creamos un puntero que apunta a esta nueva copia.
    nuevoAlumno->alumno = strdup(nombre);//generamos una copia del puntero nombre(Le ingresamos Andry Rabanales)
    nuevoAlumno->creditos = creditos;
    nuevoAlumno->semestre = semestre;
    return nuevoAlumno;// devolvemos el puntero de nuevoAlumno
}
                
void imprimirAlumno(alumno *al) {
    printf("Alumno: %s\n", al->alumno);
    printf("Creditos: %d\n", al->creditos);
    printf("Semestre: %d\n", al->semestre);
    printf("\n");
}

void imprimirDireccion(alumno *al) {
    printf("Se ha creado una estructura Alumno en la direccion \"%p\"\n", (void *)al);
}

//////////////////////////////////////////////////////////////////////
////////////////////////CREA TODOS LOS NODOS/////////////////////////
/////////////////////////////////////////////////////////////////////

            //dir del alumno creado
NODO* crearNodo(alumno *al) {
    NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));//creamos un puntero que apunta a las instancias de struct nodo,ademas de crearlo en el heap
    nuevoNodo->alumnos = al;
    nuevoNodo->ptr = NULL;
    return nuevoNodo;
}

        //nodoptr *caveza es una variable lista capaz de acceder a las estructuras alumnos
        //A esta le ingresamos la direccion de lista.
        //En este punto ya tenemos la estructura hecho, pero no ordenado, es hora de comparar
                  //( direcciones de struct NODO,dir del nuevo nodo)
int insertarNodoOrdenadoCreditos(nodoptr *cabeza, NODO *nuevoNodo) {
    //Se pregunta si el primer valor es el primero a analizar...
    if (*cabeza == NULL || (*cabeza)->alumnos->creditos <= nuevoNodo->alumnos->creditos) {//(*lista) es un doble puntero(ahor apunta a los Nodos)
        nuevoNodo->ptr = *cabeza;// Le ingresamos a NODO1 la direccion de Lista, el cual su valor de lista es NULL
        *cabeza = nuevoNodo;//Lista era antes null, y ahora contiene la direccion de NODO1
        return 1;
    } else {
        NODO *temp = *cabeza;
        while (temp->ptr != NULL && temp->ptr->alumnos->creditos > nuevoNodo->alumnos->creditos) {
            temp = temp->ptr;
        }
        nuevoNodo->ptr = temp->ptr;//
        temp->ptr = nuevoNodo;
        return 1;
    }
    return 0;
}

void imprimirLista(nodoptr lista) {
    NODO *temp = lista;
    while (temp != NULL) {
        imprimirAlumno(temp->alumnos);
        temp = temp->ptr;
    }
}

void imprimirNodoDireccion(nodoptr lista){
    NODO *temp = lista;
    while (temp !=NULL)
    {
    printf("Se ha creado un Nodo en la lista de alumnos en %p\n",(void*)temp);
    temp= temp->ptr;
    }

    
}
