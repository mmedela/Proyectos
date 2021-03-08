#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

/*************************************************
                PRIMITIVAS LISTA
*************************************************/

//POS: Devuelve una lista creada, a menos que haya un error, en cuyo caso, devuelve NULL.
lista_t *lista_crear(void);

//PRE: La lista existe.
//POS: Devuelve true si la lista esta vacia y false en caso contrario.
bool lista_esta_vacia(const lista_t *lista);

//PRE: La lista existe.
//POS: Devuelve true en caso de haber podido insertar el dato como el primer elemento de la
//lista y false en caso de haber algun error.
bool lista_insertar_primero(lista_t *lista, void *dato);

//PRE: La lista existe.
//POS: Devuelve true en caso de haber podido insertar el dato como el ultimo elemento de la
//lista y false en caso de haber algun error.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

//PRE: La lista existe.
//POS: Si la lista esta vacia devuelve NULL, en caso contrario, borra el primer elemento de la
//lista y devuelve el dato almacenado en este.
void *lista_borrar_primero(lista_t *lista);

//PRE: La lista existe.
//POS: Se devolvio el dato almacenado en el primer elemento de la lista.
void *lista_ver_primero(const lista_t *lista);

//PRE: La lista existe.
//POS: Se devolvio el dato almacenado en el primer elemento de la lista.
void *lista_ver_ultimo(const lista_t* lista);

//PRE: La lista existe.
//POS: Se devolvio la cantidad de elementos en la lista.
size_t lista_largo(const lista_t *lista);

//PRE: La lista existe.
//POS: Destruye solo la lista si la funcion destruir_dato es NULL, en caso
// contrario, tambien se destruyen los datos almacenados en los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/*******************************************************
             PRIMITIVAS ITERADOR EXTERNO
*******************************************************/

//PRE: Debe esxidstir la lista.
//POS: Se creo un irterador externo para la lista "lista" y en caso de algun error se devuelve NULL.
lista_iter_t *lista_iter_crear(lista_t *lista);

//PRE: El iterador fue creado.
//POS: Se devilvio true en caso de haber avanzado una posicion en la lista o false en caso contrario.
bool lista_iter_avanzar(lista_iter_t *iter);

//PRE: El iterador fue creado.
//POS: Se devolvio el dato almacenado en el ultimo elemento de la lista leido por el iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//PRE: El iterador fue creado.
//POS: Devuelve true en caso de intentar leer un elemento fuera del rango de la lista y
// false en cualquie otro caso.
bool lista_iter_al_final(const lista_iter_t *iter);

//PRE: El iterador fue creado.
//POS: El iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

//PRE: El iteradot fue creado.
//POS: Devuelve true si logro insertar un nuevo elemento entre el leido y su anterior, o false en caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//PRE: El iterador fue creado.
//POS: Se elimino el ultimo elemento leido ṕor el iterador y se devolvio el dato almacenado en el mismo.
void *lista_iter_borrar(lista_iter_t *iter);

/*************************************************************************************
                            PRIMITIVA ITERADOR INTERNO
*************************************************************************************/
//PRE: La lista fue creada y existe la funcion visitar.
//POS: Se leyeron secuencialmente los elementos de la lista, hasta alcanzar la condicion de corte establecida por visitar.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

#endif // LISTA_H


