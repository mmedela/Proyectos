#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define TAM_PILA_INICIAL  10
#define REDIMENSION        2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

void** pila_redimensionar(pila_t* pila, size_t capacidad_nuevo){
    void** auxiliar = pila->datos;
        pila->capacidad = capacidad_nuevo;
        auxiliar = realloc(pila->datos,sizeof(void*) * pila->capacidad);
    return auxiliar;
}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
pila_t* pila_crear(void)
{
    pila_t* p = malloc(sizeof(pila_t));
    if (p != NULL){
        p->cantidad = 0;
        p->capacidad = TAM_PILA_INICIAL;
        p->datos = malloc(sizeof(void*) * p->capacidad);
        while (p->datos == NULL){
            p->datos = malloc(sizeof(void*) * p->capacidad);
        }
    }
    return p;
}

bool pila_esta_vacia(const pila_t *pila){
    return ((pila->cantidad) == 0);
}

void* pila_desapilar(pila_t *pila){
    void* resul = NULL;
    void** aux = NULL;
    if (pila->cantidad == 0) {
        return NULL;
    }
    pila->cantidad--;
    resul = pila->datos[pila->cantidad];
    if ((pila->cantidad == (pila->capacidad)/REDIMENSION)&&(pila->capacidad > TAM_PILA_INICIAL)){
        aux = pila_redimensionar(pila, (pila->capacidad)/REDIMENSION);
        pila->datos = aux;
    }
    return resul;
}
void* pila_ver_tope(const pila_t *pila){
    void* resul = NULL;
    if (pila->cantidad != 0){
        resul = pila->datos[pila->cantidad - 1];
    }
    return resul;
}

bool pila_apilar(pila_t *pila, void* valor){
    if(pila->cantidad == pila->capacidad){
        pila->datos = pila_redimensionar(pila, (pila->capacidad)*REDIMENSION);
    }
    if (pila->datos == NULL){
        return false;
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}
// ...
void* transformar(void* dato){

    int* a = malloc(sizeof(int));
    *a = *(int*)dato;
    *a = *a + 1;
    return (void*)a;
}
pila_t* transformar_pila(pila_t* original, void* (*transformar)(void*)){

    if(!original) return NULL;

    pila_t* pila_trans = NULL;
    bool todo_ok = false;
    if(pila_esta_vacia(original)){

        pila_trans = pila_crear();
        if(!pila_trans)return NULL;
        return pila_trans;
    }
    void* dato = pila_desapilar(original);

    pila_trans = transformar_pila(original, transformar);

    if(pila_trans){

        todo_ok = pila_apilar(pila_trans, transformar(dato));

    }
    pila_apilar(original, dato);
    if(!todo_ok){

        while(!pila_esta_vacia(pila_trans)){

            free(pila_desapilar(pila_trans));
        }
        pila_destruir(pila_trans);
        return NULL;
    }
    return pila_trans;
}
    int main (){
     pila_t* prueba = pila_crear();
    for(int i = 0; i < 6; i++){

        int* a = malloc(sizeof(int));
        *a = i;
        pila_apilar(prueba, (void*)a);
    }
    pila_t* aux = transformar_pila(prueba, transformar);
    for(int i = 0; i < 6; i++){

        printf("%i ", *(int*)pila_desapilar(aux));
    }
    printf("\n");
    for(int i = 0; i < 6; i++){

        printf("%i ", *(int*)pila_desapilar(prueba));
    }
    return 0;
    }
