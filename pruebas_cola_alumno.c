#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

 void pruebas_cola_alumno(){ //Vemos que las funciones creadas cumplan con lo pedido
    printf("Creamos una cola \n");
    cola_t* cola0 = cola_crear();

    print_test("Verificamos que esta vacia con la funcion creada \n", cola_esta_vacia(cola0));
    //Agregamos un elemnto para comprobar como funciona
    void* valor;
    int aux= 1;
    valor= &aux;
    print_test("Se agrega un nuevo elemento a la cola \n", cola_encolar(cola0,valor));
    print_test("Verificamos que la cola tiene un elemento \n", !cola_esta_vacia(cola0));

    //Vemos el primer elemento
    print_test("Como hay un elemento, no debe dar NULL \n", cola_ver_primero(cola0)!=NULL);

    //Comprobamos que la funcion de desencolar funciona correctamente
    print_test("Hay un elemento, asi que desencolar devolvera no NULL \n", cola_desencolar(cola0)!=NULL);
    print_test("No hay mas elementos, desencolar debe dar NULL \n", cola_desencolar(cola0)==NULL);

    //Hacemos la prueba de volumen
    for(int i=0; i<100; i++){
        valor = malloc(sizeof(int));
        *((int*)valor) = i;
        printf("Valor a agregar: %d \n", i);
        print_test("Agregamos un nuevo elemento \n", cola_encolar(cola0, valor));

    }
    print_test("Verificamos que la cola tiene elementos \n", !cola_esta_vacia(cola0));

    for(int i=0; i<100; i++){
        print_test("Quitamos un elemento de la cola \n", cola_desencolar(cola0)!=NULL);
    }
    print_test("No hay mas elementos, desencolar debe dar NULL \n", cola_desencolar(cola0)==NULL);
    
    free (valor);

    return;
 }