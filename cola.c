#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo_t {
    void* dato;
    struct nodo_t* siguiente;
} nodo_t;

struct cola{
    nodo_t* primerNodo;
};

cola_t* cola_crear (void){
    cola_t *cola = malloc (sizeof(cola_t));
    if (cola == NULL){
        free(cola);
        return NULL;
    };
    cola->primerNodo = NULL;
    return cola;
}

void cola_destruir (cola_t *cola, void destruir_dato(void*)){
    //este nodo va a guardar siempre el elemento siguiente al que estamos parados, o null.
    nodo_t *nodo_siguiente;
    nodo_t *nodo_actual;

    if(cola->primerNodo == NULL){
        //entonces la cola no tiene elementos => hay que liberar la memoria que la cola consumio
        free(cola);
    } else {
        //la cola por lo menos tiene un elemento.
        nodo_actual = cola->primerNodo;
        nodo_siguiente = cola->primerNodo->siguiente;

        if (destruir_dato != NULL){
            do {
                destruir_dato (&nodo_actual->dato);
                nodo_actual = nodo_siguiente;
                if(nodo_actual != NULL){
                    nodo_siguiente = nodo_siguiente->siguiente;
                }
            } while(nodo_actual != NULL);
        } else
        if (destruir_dato == NULL) return;
        
        free(cola);
    }
    return;
}

bool cola_esta_vacia (const cola_t *cola){
    if (cola->primerNodo == NULL) return true;
    return false;
}

bool cola_encolar (cola_t *cola, void* valor){
    if (cola_esta_vacia(cola)){
        nodo_t* nuevoNodo = malloc(sizeof(nodo_t));
        if (nuevoNodo == NULL) return false;
        nuevoNodo->dato= valor;
        nuevoNodo->siguiente= NULL;
        printf("El nuevo nodo se creo, y tiene de valor: %d \n", *(int*)nuevoNodo->dato);
        cola->primerNodo = nuevoNodo;
        return true;
    }//Ahora vemos que hacer si tenemos otros elementos
    nodo_t *nodoAux = cola->primerNodo;  
    while (nodoAux->siguiente != NULL){
        nodoAux = nodoAux->siguiente;
    }
    nodo_t* nuevoNodo = malloc(sizeof(nodo_t));
    if (nuevoNodo == NULL) return false;
    nuevoNodo->dato= valor;
    nuevoNodo->siguiente= NULL;
    nodoAux->siguiente= nuevoNodo;
    printf("El nuevo nodo se creo, y tiene de valor: %d \n", *(int*)nuevoNodo->dato);
    return true;
}

void* cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(&*cola)) return NULL;
    return &cola->primerNodo->dato;
}

void* cola_desencolar(cola_t* cola){
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t *primer_nodo = cola->primerNodo;
    nodo_t *nodoAux = cola->primerNodo->siguiente;

    //matamos la referencia a nodos internos de la cola
    primer_nodo->siguiente = NULL;
    //devolvemos el valor del nodo
    printf("Se desencolo el valor: %d \n", *(int*)primer_nodo->dato);
    void* dato_desencolado = primer_nodo->dato;

    //la cola ahora apunta al nodo siguiente de lo que era el primer elemento.
    free (primer_nodo);
    cola->primerNodo = nodoAux;

    return dato_desencolado;
}