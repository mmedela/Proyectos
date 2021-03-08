#ifndef _PILA_H
#define _PILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* Se trata de una pila que contiene datos de tipo char
 La pila en sí está definida en el .c.  */

struct strpila;  // Definición completa en pila.c.
typedef struct strpila strpila_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
strpila_t* strpila_crear(void);

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void strpila_destruir(strpila_t *pila);

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool strpila_esta_vacia(const strpila_t *pila);

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool strpila_apilar(strpila_t *pila, char* valor);

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve 0.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, 0 en caso contrario.
char* strpila_ver_tope(const strpila_t *pila);

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// 0.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
char* strpila_desapilar(strpila_t *pila);

// pre:la pila fue creada.
//pos: se duplico o redujo a la mitad la capacidad dce la pila.
char** strpila_redimensionar(strpila_t* pila, size_t capacidad_nuevo);

//pre:la pila fue creada.
//pos:se devolvio la cantidad de elementos apilados.
size_t strpila_largo(strpila_t* pila);
#endif
