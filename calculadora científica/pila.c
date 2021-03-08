
#include "pila.h"
#define TAM_PILA_INICIAL  10
#define REDIMENSION        2


struct pila {
    long int* datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

long int* pila_redimensionar(pila_t* pila, size_t capacidad_nuevo){
    long int* auxiliar = pila->datos;
        pila->capacidad = capacidad_nuevo;
        auxiliar = realloc(pila->datos,sizeof(long int) * pila->capacidad);
    return auxiliar;
}

pila_t* pila_crear(void){
    pila_t* p = malloc(sizeof(pila_t));
    if (p != NULL){
        p->cantidad = 0;
        p->capacidad = TAM_PILA_INICIAL;
        p->datos = malloc(sizeof(long int) * p->capacidad);
        while (p->datos == NULL){
            p->datos = malloc(sizeof(long int) * p->capacidad);
        }
    }
    return p;
}

long int pila_ver_tope(const pila_t *pila){
    long int resul = 0;
    if (pila->cantidad != 0){
        resul = pila->datos[pila->cantidad - 1];
    }
    return resul;
}

bool pila_esta_vacia(const pila_t *pila){
    return ((pila->cantidad) == 0);
}

long int pila_desapilar(pila_t *pila){
    long int resul = 0;
    long int* aux = NULL;
    if (pila->cantidad == 0) {
        return 0;
    }
    pila->cantidad--;
    if ((pila->cantidad == (pila->capacidad)/REDIMENSION)&&(pila->capacidad > TAM_PILA_INICIAL)){
        aux = pila_redimensionar(pila, (pila->capacidad)/REDIMENSION);
        pila->datos = aux;
    }
    resul = pila->datos[pila->cantidad];

    return resul;
}

bool pila_apilar(pila_t *pila, long int valor){
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

size_t pila_largo(pila_t* pila){

    return pila->cantidad;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}
