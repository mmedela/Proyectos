#ifndef _PILA_H
#define _PILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


/* Se trata de una pila que contiene datos de tipo char
 La pila en sí está definida en el .c.  */

struct pila;  // Definición completa en pila.c.
typedef struct pila pila_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void);

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila);

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila);

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, long int valor);

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve 0.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, 0 en caso contrario.
long int pila_ver_tope(const pila_t *pila);

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// 0.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
long int pila_desapilar(pila_t *pila);

// pre:la pila fue creada.
//pos: se duplico o redujo a la mitad la capacidad dce la pila.
long int* pila_redimensionar(pila_t* pila, size_t capacidad_nuevo);

//pre:la pila fue creada.
//pos:se devolvio la cantidad de elementos apilados.
size_t pila_largo(pila_t* pila);
#endif
