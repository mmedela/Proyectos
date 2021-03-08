/*
TP:         PILA
Entrega:    2
Fecha:      10-may-2020
Alumno:     Miguel Lederkremer
Padrón:     61719
Correctora: Mile Marchese
*/

#include "pila.h"

#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 2
#define FACTOR_AMPLIACION 2
#define FACTOR_REDUCCION 2
#define AGRANDAR true
#define ACHICAR false
#define CAPACIDAD_MINIMA 4

struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t *pila_crear(void) {
    pila_t *pila = malloc(sizeof(pila_t));

    if (!pila) {
        return NULL;
    }
    pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void *));

    if (!pila->datos) {
        free(pila);
        return NULL;
    }
    pila->capacidad = CAPACIDAD_INICIAL;
    pila->cantidad = 0;
    return pila;
}

void pila_destruir(pila_t *pila) {
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
    return (pila->cantidad == 0);
}

bool pila_redimensionar(pila_t *pila, size_t cap_nueva) {
    void **nuevos_datos = realloc(pila->datos, cap_nueva * sizeof(void *));
    if (nuevos_datos == NULL) {
        return false;
    }
    pila->datos = nuevos_datos;
    pila->capacidad = cap_nueva;
    return true;
}

bool pila_apilar(pila_t *pila, void *valor) {
    if (pila->cantidad + 1 > pila->capacidad) {
        if (pila_redimensionar(pila, pila->capacidad*FACTOR_AMPLIACION)==false){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila) {
    if (pila->cantidad == 0) {
        return NULL;
    }
    size_t posicion = pila->cantidad - 1;
    return pila->datos[posicion];
}

void *pila_desapilar(pila_t *pila) {
    if (pila->cantidad == 0) {
        return NULL;
    }
    bool esta_muy_vacia = (pila->cantidad - 1 < pila->capacidad / CAPACIDAD_MINIMA);
    bool esta_al_minimo = (pila->capacidad <=CAPACIDAD_INICIAL);
    if (esta_muy_vacia && !esta_al_minimo) {
        if (!pila_redimensionar(pila, pila->capacidad/FACTOR_REDUCCION)) return NULL;
    }
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}
