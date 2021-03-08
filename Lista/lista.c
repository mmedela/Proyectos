//#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct nodo{

    void* dato;
    struct nodo* prox;
}nodo_t;

typedef struct lista{

    nodo_t* primero;
    nodo_t* ultimo;
    size_t tamanio;
}lista_t;

typedef struct lista_iter{

    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
}lista_iter_t;

lista_t *lista_crear(void){

    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->tamanio = 0;

    return lista;
}

bool lista_esta_vacia(const lista_t *lista){

    return (lista->tamanio == 0);
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if(!nodo_nuevo) {
        return false;
    }
    nodo_nuevo->prox = NULL;
    nodo_nuevo->dato = dato;
    if (lista->tamanio == 0){
        lista->primero = nodo_nuevo;
    }else{
        lista->ultimo->prox = nodo_nuevo;
    }
    lista->ultimo = nodo_nuevo;
    lista->tamanio++;
    return true;
}

bool lista_insertar_primero(lista_t *lista, void *dato){

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if(!nodo_nuevo) return false;

    if (lista->tamanio == 0){
        lista->ultimo = nodo_nuevo;
        nodo_nuevo->prox = NULL;
    }else{
        nodo_nuevo->prox = lista->primero;
    }
    lista->primero = nodo_nuevo;
    nodo_nuevo->dato = dato;
    lista->tamanio++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){

    if (lista->tamanio == 0) return NULL;

    void* dato_aux = lista->primero->dato;
    nodo_t* nodo_aux = lista->primero;
    if(lista->tamanio == 1) lista->ultimo = NULL;

    lista->primero = lista->primero->prox;
    lista->tamanio--;
    free(nodo_aux);
    return dato_aux;
}

void *lista_ver_primero(const lista_t *lista){

    if(lista->tamanio == 0) return NULL;
    return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){

    if(lista->tamanio == 0) return NULL;
    return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){

    return lista->tamanio;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    if(destruir_dato != NULL){
        while(lista->tamanio > 0){
            destruir_dato(lista_borrar_primero(lista));
        }
    }else{
        while(lista->tamanio > 0){
            lista_borrar_primero(lista);
        }
    }
    free(lista);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
lista_iter_t *lista_iter_crear(lista_t *lista){

    lista_iter_t* iterator = malloc(sizeof(lista_iter_t));
    if(!iterator) return NULL;
    iterator->lista = lista;
    iterator->actual = lista->primero;
    iterator->anterior = NULL;
    return iterator;
}

bool lista_iter_avanzar(lista_iter_t *iter){

    if(iter->actual == NULL) return false;
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){

    if(!iter->actual)return NULL;

    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){

    return (iter->actual == NULL);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (!nodo_nuevo) return false;
    nodo_nuevo->dato = dato;
    if(iter->anterior != NULL) iter->anterior->prox = nodo_nuevo;
    else iter->lista->primero = nodo_nuevo;
    nodo_nuevo->prox = iter->actual;
    if (nodo_nuevo->prox == NULL) iter->lista->ultimo = nodo_nuevo;
    iter->actual = nodo_nuevo;
    iter->lista->tamanio++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){

    if (lista_iter_al_final(iter)) return NULL;
    nodo_t* nodo_aux = iter->actual;
    void* dato_aux = iter->actual->dato;
    if (!(iter->actual->prox)){

        iter->lista->ultimo = iter->anterior;
    }
    if (!(iter->anterior)){

        iter->lista->primero = iter->actual->prox;
    }else{

        iter->anterior->prox = iter->actual->prox;
    }
    iter->actual = iter->actual->prox;
    iter->lista->tamanio--;
    free(nodo_aux);
    return dato_aux;

}

void lista_iter_destruir(lista_iter_t *iter){

    free(iter);
}


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){

    nodo_t* nodo_actual = lista->primero;
    //if(iter->actual == NULL) return false;
    //iter->anterior = iter->actual;
   // iter->actual = iter->actual->prox;
    while (!(nodo_actual == NULL) && (visitar(nodo_actual->dato, extra))){

       nodo_actual = nodo_actual->prox;
    }
}
