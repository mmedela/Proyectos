#include "vector.h"
#include <stdio.h>
// Funciones del alumno.
// ...
// Funciones implementadas por la catedra.

typedef struct nodo{


}nodo_t;

typedef struct vector {
    size_t tam;
    int* datos;
} vector_t;

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));
    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(int));
    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }
    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}

size_t vector_largo(vector_t* vector){
    return vector->tam;
}

void vector_destruir(vector_t* vector){
    free(vector->datos);
    free(vector);
}

bool vector_obtener(vector_t* vector, size_t pos, int* valor){
    if ((int)vector->tam - 1 < (int)pos){
        return false;
    }
    *valor = vector->datos[pos];
    return true;
}
bool vector_guardar(vector_t* vector, size_t pos, int valor){
    if((int)vector->tam - 1 < (int)pos){
        return false;
    }
    vector->datos[pos] = valor;
    return true;
    }
