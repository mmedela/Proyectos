// TP LISTA
// MIGUEL LEDERKREMER - PADRON 61719
// CORRECTORA MILE MARCHESE
// 2DA ENTREGA
// 28-MAY-2020

#include "lista.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct nodo {
    void *dato;
    struct nodo *prox;
};

typedef struct nodo nodo_t;

struct lista {
    struct nodo *prim;
    struct nodo *ult;
    size_t largo;
};

struct lista_iter {
    lista_t *lista;
    struct nodo *act;
    struct nodo *ant;
};

nodo_t *nodo_lista_crear(void *dato, struct nodo *prox) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (!nodo) {
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = prox;
    return nodo;
}

lista_t *lista_crear() {
    lista_t *lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista) { return (lista->prim == NULL); }

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_lista_crear(dato, lista->prim);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->ult = nodo;
    }
    lista->prim = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_lista_crear(dato, NULL);
    if (!nodo) {
        return false;
    }
    if (!lista_esta_vacia(lista)) {
        lista->ult->prox = nodo;
    } else {
        lista->prim = nodo;
    }
    lista->ult = nodo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    void *dato = lista->prim->dato;
    nodo_t *aux = lista->prim;
    lista->prim = lista->prim->prox;
    free(aux);
    lista->largo--;
    if (!lista->largo) {
        lista->ult = NULL;
    }
    return dato;
}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t *lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) { return lista->largo; }

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
    nodo_t *nodo_actual, *nodo_prox;
    nodo_actual = lista->prim;
    while (nodo_actual != NULL) {
        nodo_prox = nodo_actual->prox;
        if (destruir_dato) {
            destruir_dato(nodo_actual->dato);
        }
        free(nodo_actual);
        nodo_actual = nodo_prox;
    }
    free(lista);
}

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->lista = lista;
    iter->act = lista->prim;
    iter->ant = NULL;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return false;
    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;
    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return (!iter->act);
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}
bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nodo = nodo_lista_crear(dato, iter->act);
    if (!nodo) return false;
    if (!iter->ant) {
        nodo->prox = iter->lista->prim;
        iter->lista->prim = nodo;
        if (!nodo->prox) {
            iter->lista->ult = nodo;
        }
    } else {
        iter->ant->prox = nodo;
        nodo->prox = iter->act;
        if (!iter->act) {
            iter->lista->ult = nodo;
        }
    }
    iter->act = nodo;
    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return NULL;
    nodo_t *actual = iter->act;
    void *dato = iter->act->dato;
    // CASO BORDE BORRAR ULTIMO
    if (actual->prox == NULL) {
        iter->lista->ult = iter->ant;  // si ademas era el primero esto es null
    }
    // CASO BORDE BORRAR PRIMERO
    if (iter->ant == NULL) {
        iter->lista->prim =
            actual->prox;                // si ademas era el ultimo esto es null
    } else {                             // SI NO ERA PRIMERO
        iter->ant->prox = actual->prox;  // si era ultimo esto es NULL
    }
    // PARA TODOS LOS CASOS
    iter->act = actual->prox;
    free(actual);
    iter->lista->largo--;
    return dato;
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t *nodo = lista->prim;
    while (nodo) {
        if (!visitar(nodo->dato, extra)) break;
        nodo = nodo->prox;
    }
}