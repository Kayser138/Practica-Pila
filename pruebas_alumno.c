#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_alumno() {
    
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL\n", ejemplo == NULL);

    ejemplo = pila_crear();

    printf("Creamos una pila nueva\n");
    pila_t* pila0 = pila_crear();

    print_test("Verificamos que esta vacia con la funcion creada\n", pila_esta_vacia(pila0));
    //Agregamos un elemnto para comprobar como funciona
    void* valor;
    int i= 1;
    valor= &i;
    print_test("Se agrega un nuevo elemento a la pila\n", pila_apilar(pila0,valor));
    print_test("Verificamos que la pila tiene un elemento con la funcion de pila esta vacia\n", !pila_esta_vacia(pila0));

    //Vemos el primer elemento
    print_test("Como hay un elemento, pila ver tope debe mostrar el valor\n", pila_ver_tope(pila0) == valor);

    //Comprobamos que la funcion de desencolar funciona correctamente
    print_test("Hay un elemento, asi que desapilar devolvera el valor ingresado:\n", pila_desapilar(pila0)== valor);
    print_test("No hay mas elementos, desapilar debe dar NULL\n", pila_desapilar(pila0)== NULL);

    //Hacemos la prueba de volumen
    size_t volumen = 1000;
    int* vector_datos = malloc (volumen * sizeof(int));
    for(int i=0; 1<volumen; i++){
        vector_datos[i]=i;
    }

    //Verificamos que los datos se guardan correctamente
    bool des_apila_bien = true;
    for(int i=0; i<volumen;i++){
        pila_apilar(pila0, &vector_datos[i]);
        if (pila_ver_tope(pila0) != &vector_datos[i]){
            des_apila_bien = false;
            break;
        }
    }
    print_test("Vemos si el TDA apila correctamente los datos \n", des_apila_bien);

    print_test("Verificamos que la pila tiene elementos\n", !pila_esta_vacia(pila0));

    //Ahora vamos a desapilar los valores
    des_apila_bien = true;
    for(size_t i=volumen-1;i>-1; i--){
        if (pila_desapilar(pila0) != &vector_datos[i]){
            des_apila_bien = false;
            break;
        }
        if(i==0) break;
    }
    print_test("Comprobamos que salieron todos los elementos de forma correcta \n", des_apila_bien);

    print_test("No hay mas elementos, desencolar debe dar NULL\n", pila_desapilar(pila0)==NULL);

    //Finalmente eliminamos la pila
    pila_destruir(pila0);

    free(vector_datos);
    return;
 }