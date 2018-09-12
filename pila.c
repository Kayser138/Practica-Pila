#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

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

/* FUNCION AUXILIAR */
bool redimensionar(pila_t* pila, size_t tam_nuevo) {
    void* pila_tam_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void*));
    if (pila_tam_nuevo == NULL) {
        return false;
    }
    pila->datos = pila_tam_nuevo;
    pila->capacidad = tam_nuevo;
    return true;
}

// compilar: gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -g -o pruebas *.c
// valgrind: valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

const size_t tam_inicial = 10;

pila_t* pila_crear (void){
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }

    pila->capacidad = tam_inicial;
    pila->cantidad = 0;

    pila->datos = malloc(sizeof(void*) *pila->capacidad); //verificar con un if.

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }  
    return pila;
}

void pila_destruir (pila_t *pila){
    if (pila != NULL){
        for (size_t i=0;i <= pila->capacidad; i++){
            free (pila->datos);
        }
    }
    free (pila);
}

bool pila_esta_vacia (const pila_t *pila){
    if (pila == NULL) return true;
    if (pila->cantidad > 0) return false;
    return true;
}

bool pila_apilar (pila_t *pila, void *valor){
    size_t nuevo_tope = pila->cantidad + 1;
    if (nuevo_tope > pila->capacidad) { //Si el tamaño de la pila es menor al nuevo tope, aumento la capacidad
        pila->capacidad *= 2;
        redimensionar(pila, pila->capacidad);
        }
    pila->datos[pila->cantidad -1] = &valor;
    pila->cantidad = nuevo_tope;
    return true;
}

void* pila_ver_tope (const pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[pila->cantidad];
}

void* pila_desapilar (pila_t *pila){
    void *aux;
    if (pila_esta_vacia(pila)) return NULL;
    else {
        aux= pila->datos[pila->cantidad];
        free (pila->datos[pila->cantidad]);
        pila->cantidad -= 1;
    } 
    if (pila->cantidad <= (pila->capacidad/4) && (pila->capacidad/4) > tam_inicial){
            pila->capacidad /= 2;
            redimensionar(pila, pila->capacidad);
        }
    return aux;
}