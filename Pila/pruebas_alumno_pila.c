#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_vacia(){
    pila_t* pila = NULL;
    print_test("Puntero inicializado a NULL", pila == NULL);
    pila = pila_crear();
    print_test("Puntero a pila inicializado", pila != NULL);
    print_test("La pila esta vacia (pila_esta_vacia)", pila_esta_vacia(pila));
    print_test("La pila esta vacia (pila_ver_tope)", !pila_ver_tope(pila));
    print_test("La pila esta vacia (pila_desapilar)", !pila_desapilar(pila));
    print_test("la pila permite NULLs", pila_apilar(pila, NULL));
    pila_destruir(pila);
}
void pruebas_pila_volumen(){
    pila_t* pila = NULL;
    print_test("Puntero inicializado a NULL", pila == NULL);
    pila = pila_crear();
    bool todo_ok;
    int vector_volumen [10000];
    for(int i = 0; i < 10000; i++){
        vector_volumen[i] = i;
        todo_ok = pila_apilar(pila, &vector_volumen[i]);
        if (!todo_ok){
            break;
        }
    }
    print_test("se apilaron 10.000 elementos", todo_ok);
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    todo_ok = true;
    for(int i = 10000 -1; i >= 0; i--){
        if (*(int*)pila_desapilar(pila) != i){
            todo_ok = false;
            break;
        }
    }
    print_test ("se desapilaron 10.000 elementos", todo_ok);
    print_test("La pila quedo vacia", pila_esta_vacia(pila));
    pila_destruir(pila);
}

void pruebas_pila_uso_basico(){
    pila_t* pila = NULL;
    print_test("Puntero inicializado a NULL", pila == NULL);
    pila = pila_crear();
    int vector_nums[12];
    for (int i = 0; i < 12; i++) {
        vector_nums[i] = i;
        print_test("Apilo el elemento i", pila_apilar(pila, &vector_nums[i]));
        print_test("Leo el elemento i", (int*)pila_ver_tope(pila) == &vector_nums[i]);
    }
     print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    int *a;
    for(int i = 11; i>=0; i--){
        a = (int*)pila_desapilar(pila) ;
       if(*a!=vector_nums[i])a = NULL;
        print_test("Se desapilo la pila(pila_desapilar)",a!=NULL);
    }
    pila_destruir(pila);
}


void pruebas_pila_alumno() {

    pruebas_pila_uso_basico();
   /* pruebas_pila_volumen();
    pila_t* pila_vacia = NULL;
    pila_vacia = pila_crear();
    pila_destruir(pila_vacia);*/
}
