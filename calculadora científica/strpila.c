
#include "strpila.h"
#define TAM_PILA_INICIAL  10
#define REDIMENSION        2

struct strpila {
    char** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

char** strpila_redimensionar(strpila_t* pila, size_t capacidad_nuevo){
    char** auxiliar = pila->datos;
        pila->capacidad = capacidad_nuevo;
        auxiliar = realloc(pila->datos,sizeof(char*) * pila->capacidad);
    return auxiliar;
}

strpila_t* strpila_crear(void){
    strpila_t* p = malloc(sizeof(strpila_t));
    if (p != NULL){
        p->cantidad = 0;
        p->capacidad = TAM_PILA_INICIAL;
        p->datos = malloc(sizeof(char*) * p->capacidad);
        while (p->datos == NULL){
            p->datos = malloc(sizeof(char*) * p->capacidad);
        }
    }
    return p;
}

char* strpila_ver_tope(const strpila_t *pila){
    char *resul = NULL;
    if (pila->cantidad != 0){
        resul = pila->datos[pila->cantidad - 1];
    }
    return resul;
}

bool strpila_esta_vacia(const strpila_t *pila){
    return ((pila->cantidad) == 0);
}

char* strpila_desapilar(strpila_t *pila){
    char *resul = NULL;
    char** aux = NULL;
    if (pila->cantidad == 0) {
        return 0;
    }
    pila->cantidad--;
    if ((pila->cantidad == (pila->capacidad)/REDIMENSION)&&(pila->capacidad > TAM_PILA_INICIAL)){
        aux = strpila_redimensionar(pila, (pila->capacidad)/REDIMENSION);
        pila->datos = aux;
    }
    resul = pila->datos[pila->cantidad];

    return resul;
}

bool strpila_apilar(strpila_t *pila, char* valor){
    if(pila->cantidad == pila->capacidad){
        pila->datos = strpila_redimensionar(pila, (pila->capacidad)*REDIMENSION);
    }
    if (pila->datos == NULL){
        return false;
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

size_t strpila_largo(strpila_t* pila){

    return pila->cantidad;
}

void strpila_destruir(strpila_t *pila){
    free(pila->datos);
    free(pila);
}
