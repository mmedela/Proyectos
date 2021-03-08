#define _POSIX_C_SOURCE 200809L
#include "abb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lista.h"
#include "pila.h"

#define HIJO_IZQ 1
#define HIJO_DER 2
#define HIJO_IZQ_NUEVO -1
#define HIJO_DER_NUEVO -2
#define RAIZ 3
#define VACIO 0

typedef struct nodo {
    struct nodo* izq;
    struct nodo* der;
    char* clave;
    void* dato;
} nodo_t;

struct abb {
    struct nodo* raiz;
    size_t cant;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
};

struct abb_iter {
    const abb_t* arbol;
    pila_t* pila;
};

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t* abb = malloc(sizeof(abb_t));
    if (!abb) return NULL;
    abb->raiz = NULL;
    abb->cant = 0;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;
    return abb;
}

nodo_t* nodo_crear(abb_t* arbol, const char* clave, void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    char* clave_copia = strdup(clave);
    nodo->clave = clave_copia;
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    arbol->cant++;
    return nodo;
}

size_t abb_cantidad(abb_t* arbol) {
    return arbol->cant;
}

/* devuelve:
    el padre del nodo           si la clave existe 
    el padre q deberia tener    si la clave no existe
    NULL                        si el nodo es raiz 
en *tipo devuelve el tipo de hijo:
    1 HIJO_IZQ          existe es hijo izq
    2 HIJO_DER          existe es hijo der
    3 RAIZ              existe y el nodo es raiz
    0 VACIO             NO existe - el arbol está vacío (hay q llamar  la función con *tipo=0)
    -1 HIJO_IZQ_NUEVO   NO existe  - deberia ser hijo izq
    -2 HIJO_DER_NUEVO   NO existe  - deberia ser hijo der
*/
nodo_t* rec_padre_buscar(nodo_t* nodo, nodo_t* padre, const char* clave, abb_comparar_clave_t cmp, int* tipo) {
    if (!nodo) {
        *tipo *= -1;
        return padre;  // si no encontro el nodo devuelve NULL
    }
    if (cmp(clave, nodo->clave) == 0) {
        if (!padre) {
            *tipo = RAIZ;
        }
        return padre;
    }
    if (cmp(clave, nodo->clave) > 0) {
        *tipo = HIJO_DER;
        return rec_padre_buscar(nodo->der, nodo, clave, cmp, tipo);
    }
    if (cmp(clave, nodo->clave) < 0) {
        *tipo = HIJO_IZQ;
        return rec_padre_buscar(nodo->izq, nodo, clave, cmp, tipo);
    }
    return NULL;  // solo porque me lo pide el compilador
}

bool abb_pertenece(const abb_t* arbol, const char* clave) {
    int tipo = 0;  //si el arbol esta vacio tipo quedará en 0 o sea no pertenece
    rec_padre_buscar(arbol->raiz, NULL, clave, arbol->cmp, &tipo);
    return (tipo > 0);
}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato) {
    if (arbol->cant == 0) {
        nodo_t* nuevo = nodo_crear(arbol, clave, dato);
        if (!nuevo) return false;
        arbol->raiz = nuevo;
        return true;
    }
    int tipo = 0;
    nodo_t* nodo = arbol->raiz;
    nodo_t* padre = rec_padre_buscar(nodo, NULL, clave, arbol->cmp, &tipo);
    //si encontró la clave reemplaza el dato
    if (tipo == HIJO_IZQ) {
        nodo = padre->izq;
    }
    if (tipo == HIJO_DER) {
        nodo = padre->der;
    }
    if (tipo == RAIZ) {
        nodo = arbol->raiz;
    }
    if (tipo > 0) {
        if (arbol->destruir_dato)
            arbol->destruir_dato(nodo->dato);
        nodo->dato = dato;
        return true;
    }
    // si llegó acá es porque tipo<=0 : es una clave nueva
    nodo_t* nuevo = nodo_crear(arbol, clave, dato);
    if (!nuevo) return false;
    if (tipo == HIJO_IZQ_NUEVO) {
        padre->izq = nuevo;
    }
    if (tipo == HIJO_DER_NUEVO) {
        padre->der = nuevo;
    }
    return true;
}

nodo_t* abb_obtener_nodo(const abb_t* arbol, const char* clave) {
    int tipo = 0;
    nodo_t* nodo;
    nodo_t* padre = rec_padre_buscar(arbol->raiz, NULL, clave, arbol->cmp, &tipo);
    switch (tipo) {
        case HIJO_IZQ:
            nodo = padre->izq;
            break;
        case HIJO_DER:
            nodo = padre->der;
            break;
        case RAIZ:
            nodo = arbol->raiz;
            break;
        default:
            return NULL;
    }
    return nodo;
}

void* abb_obtener(const abb_t* arbol, const char* clave) {
    nodo_t* nodo = abb_obtener_nodo(arbol, clave);
    if (!nodo) return NULL;
    return nodo->dato;
}

void destruir_este(nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
    free(nodo->clave);
    if (destruir_dato) destruir_dato(nodo->dato);
    free(nodo);
}

void destruir_nodos(nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
    if (nodo == NULL) return;
    destruir_nodos(nodo->izq, destruir_dato);
    destruir_nodos(nodo->der, destruir_dato);
    destruir_este(nodo, destruir_dato);
}

void abb_destruir(abb_t* arbol) {
    destruir_nodos(arbol->raiz, arbol->destruir_dato);
    free(arbol);
}

void hijo_vuela(abb_t* arbol, char* clave_hijo, nodo_t* nuevo_hijo) {
    int tipo = 0;
    nodo_t* padre = rec_padre_buscar(arbol->raiz, NULL, clave_hijo, arbol->cmp, &tipo);
    switch (tipo) {
        case HIJO_IZQ:
            padre->izq = nuevo_hijo;
            break;
        case HIJO_DER:
            padre->der = nuevo_hijo;
            break;
        case RAIZ:
            arbol->raiz = nuevo_hijo;
            break;
    }
}

nodo_t* menor_hijo_mayor(nodo_t* nodo) {
    nodo_t* reemplazo = nodo->der;
    while (reemplazo->izq != NULL) {
        reemplazo = reemplazo->izq;
    }
    return reemplazo;
}

void* abb_borrar(abb_t* arbol, const char* clave) {
    nodo_t* nodo = abb_obtener_nodo(arbol, clave);
    if (!nodo) return NULL;
    void* dato = nodo->dato;
    if (!nodo->izq && !nodo->der) {  // sin hijos
        hijo_vuela(arbol, nodo->clave, NULL);
    } else if (nodo->izq && !nodo->der) {  // un hijo izq
        hijo_vuela(arbol, nodo->clave, nodo->izq);
    } else if (!nodo->izq && nodo->der) {  // un hijo der
        hijo_vuela(arbol, nodo->clave, nodo->der);
    } else if (nodo->izq && nodo->der) {  // dos hijos
        // ubico el menor de sus hijos mayores, remmplazo clave, asigno dato, destruyo reemplazo (no el dato)
        nodo_t* reemplazo = menor_hijo_mayor(nodo);
        char* clave_reemplazo = strdup(reemplazo->clave);
        nodo->dato = reemplazo->dato;
        //no puedo usar abb_borrar para el reemplazo porque me borraria el dato, q no puedo duplicar como la clave
        if (reemplazo->der) {
            hijo_vuela(arbol, reemplazo->clave, reemplazo->der);
        } else {
            hijo_vuela(arbol, reemplazo->clave, NULL);
        }
        destruir_este(reemplazo, NULL);
        free(nodo->clave);
        nodo->clave = clave_reemplazo;
        arbol->cant--;
        return dato;
    }
    destruir_este(nodo, arbol->destruir_dato);
    arbol->cant--;
    return dato;
}

void abb_iterar(nodo_t* nodo, bool visitar(const char* clave, void* dato, void* extra), void* extra, bool* seguir) {
    if (!nodo) return;
    if (!*seguir) return;
    abb_iterar(nodo->izq, visitar, extra, seguir);
    if (!*seguir) return;
    *seguir = visitar(nodo->clave, nodo->dato, extra);
    if (!*seguir) return;
    abb_iterar(nodo->der, visitar, extra, seguir);
}

void abb_in_order(abb_t* arbol, bool visitar(const char* clave, void* dato, void* extra), void* extra) {
    bool seguir = true;
    abb_iterar(arbol->raiz, visitar, extra, &seguir);
}

bool apilar_nodo_e_hijos_izq(pila_t* pila, nodo_t* nodo) {
    while (nodo) {
        if (!pila_apilar(pila, (void*)nodo)) return false;
        nodo = nodo->izq;
    }
    return true;
}

abb_iter_t* abb_iter_in_crear(const abb_t* arbol) {
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;
    iter->pila = pila_crear();
    if (!iter->pila) return NULL;
    iter->arbol = arbol;
    if (!apilar_nodo_e_hijos_izq(iter->pila, arbol->raiz)) return NULL;
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t* iter) {
    nodo_t* nodo = (nodo_t*)pila_desapilar(iter->pila);
    if (!nodo) return false;
    if (!apilar_nodo_e_hijos_izq(iter->pila, nodo->der)) return NULL;
    return true;
}

const char* abb_iter_in_ver_actual(const abb_iter_t* iter) {
    if (abb_iter_in_al_final(iter)) return NULL;
    return ((nodo_t*)pila_ver_tope(iter->pila))->clave;
}

bool abb_iter_in_al_final(const abb_iter_t* iter) {
    return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->pila);
    free(iter);
}

// primitivas agregadas para este tp
//devuelve lista con los DATOS en un rango
void abb_rango_rec(nodo_t* nodo, const char* com, const char* fin, lista_t* lista) {
    if (!nodo) return;
    if (strcmp(nodo->clave, com) > 0) {  //solo va para la izq si la clave es mayor q com
        abb_rango_rec(nodo->izq, com, fin, lista);
    }
    bool sigue = strcmp(nodo->clave, fin) <= 0 || strcmp(fin, "") == 0;
    if ((strcmp(nodo->clave, com) >= 0) && sigue) {
        lista_insertar_ultimo(lista, nodo->dato);
    }
    if (sigue) {  //solo va para la der si no termino
        abb_rango_rec(nodo->der, com, fin, lista);
    }
}

lista_t* abb_rango(const abb_t* abb, const char* com, const char* fin) {
    lista_t* lista = lista_crear();
    if (!lista) return NULL;
    abb_rango_rec(abb->raiz, com, fin, lista);
    return lista;
}
