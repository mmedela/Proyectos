#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct nodo{

    void* dato;
    struct nodo* siguiente;

}nodo_t;

typedef struct cola{

    nodo_t* nodo_primero;
    nodo_t* nodo_ultimo;

}cola_t;

cola_t* cola_crear(void){

    cola_t* cola = malloc(sizeof(cola_t));

    if (cola != NULL){

        cola->nodo_primero = NULL;
        cola->nodo_ultimo = NULL;
    }
    return cola;

}

bool cola_esta_vacia(const cola_t *cola){

    return ((cola->nodo_primero == NULL)&&(cola->nodo_ultimo == NULL));
}

bool cola_encolar(cola_t *cola, void* valor){

    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return false;
    nodo->dato = valor;
    nodo->siguiente = NULL;
    if (cola_esta_vacia(cola)) cola->nodo_primero = nodo;

    else cola->nodo_ultimo->siguiente = nodo;
    cola->nodo_ultimo = nodo;

    return true;
}

void* cola_ver_primero(const cola_t *cola){

    if (cola_esta_vacia(cola)){

        return NULL;
    }
    return cola->nodo_primero->dato;

}

void* cola_desencolar(cola_t *cola){

    void* respuesta = NULL;


    if (cola_esta_vacia(cola)){

        return respuesta;
    }
    nodo_t* aux = cola->nodo_primero;

    if (cola->nodo_primero->siguiente == NULL) cola->nodo_ultimo = NULL;

    cola->nodo_primero = cola->nodo_primero->siguiente;

    respuesta = aux->dato;

    free(aux);
/*
    if (cola_esta_vacia(cola)){

        cola->nodo_ultimo = NULL;
    }
*/
    return respuesta;

}



void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){

    void* dato_leido = NULL;
    bool cola_vacia = cola_esta_vacia(cola);

    while (!cola_vacia){

        dato_leido = cola_desencolar(cola);

        if (destruir_dato != NULL){

            destruir_dato(dato_leido);
        }
        cola_vacia = cola_esta_vacia(cola);
    }
    free(cola);
}
