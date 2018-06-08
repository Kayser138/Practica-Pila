#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);

    ejemplo = pila_crear();

    printf("Creamos una pila nueva");
    pila_t* pila0 = pila_crear();

    print_test("Verificamos que esta vacia con la funcion creada", pila_esta_vacia(pila0));
    //Agregamos un elemnto para comprobar como funciona
    void** valor;
    int* aux;
    int i= 1;
    aux=&i;
    valor=aux;
    print_test("Se agrega un nuevo elemento a la pila", pila_apilar(pila0,valor));
    print_test("Verificamos que la pila tiene un elemento", !pila_esta_vacia(pila0));

    //Vemos el primer elemento
    print_test("Como hay un elemento, no debe dar NULL", pila_ver_tope(pila0)!=NULL);
    pila_ver_tope(pila0);

    //Comprobamos que la funcion de desencolar funciona correctamente
    print_test("Hay un elemento, asi que desapilar devolvera no NULL", pila_desapilar(pila0)!=NULL);
    print_test("No hay mas elementos, desapilar debe dar NULL", pila_desapilar(pila0)==NULL);

    //Hacemos la prueba de volumen
    for(i=0; i<100; i++){
        aux=&i;
        valor=aux;
        print_test("Agregamos un nuevo elemento", pila_apilar(pila0, valor));
    }
    print_test("Verificamos que la pila tiene elementos", !pila_esta_vacia(pila0));

    for(i=100; i>0; i--){
        print_test("Quitamos un elemento de la pila", pila_desapilar(pila0)!=NULL);
    }
    print_test("No hay mas elementos, desencolar debe dar NULL", pila_desapilar(pila0)==NULL);
    return;
 }