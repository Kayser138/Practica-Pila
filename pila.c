#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

//Tomo a consideracion que el tipo size_t se define como el valor absoluto, iniciando desde el 0

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// compilar: gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -g -o pruebas *.c
// valgrind: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

pila_t* pila_crear (void){
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }

    pila->capacidad = 10;
    pila->cantidad = 0;

    pila->datos = malloc(sizeof(void*) *pila->capacidad); //verificar con un if.

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }  
    return pila;
}

void pila_destruir (pila_t *pila){
    for (size_t i=0;i <= pila->capacidad; i++){
        free (pila->datos);
    }
    free (pila);
}

bool pila_esta_vacia (const pila_t *pila){
    if (pila->datos[0] == NULL) return true;
    return false;
}

bool pila_apilar (pila_t *pila, void *valor){
    size_t nuevo_tope = pila->cantidad + 1;
    if (nuevo_tope > pila->capacidad) { //Si el tamaño de la pila es menor al nuevo tope, aumento la capacidad
        void* r = realloc((void*) pila,sizeof(pila->datos) *((pila->capacidad) * 2));
        if(r) {
            pila->datos = r; 
            pila->capacidad *= 2;
        } else {
            return false;
        }//cint c repl
        pila->datos[nuevo_tope] = &valor;
        pila->capacidad = nuevo_tope;
        return true;
    }
    else {
        pila->datos[pila->cantidad -1] = &valor;
        pila->cantidad = nuevo_tope;
        return true;
    }
}

void* pila_ver_tope (const pila_t *pila){
size_t pos = (pila->capacidad - (pila->capacidad - pila->cantidad)-1) ;
if (pila_esta_vacia(pila)) return NULL;
return pila->datos[pos];
}

void* pila_desapilar (pila_t *pila){
    void **aux= NULL;
    if (pila_esta_vacia(&*pila)) return aux;
    else {
        aux= pila->datos[pila->cantidad];
        free (pila->datos[pila->cantidad]);
        pila->cantidad -= 1;
    } 
    if (pila->cantidad < (pila->capacidad/2)){
        void* r= realloc ((void *) pila, sizeof (pila->datos)*((pila->capacidad) /2));
        if(r) {
            pila->datos = r; 
            pila->capacidad /= 2;
        }
    }
    return aux;
}