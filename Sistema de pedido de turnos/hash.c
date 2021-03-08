// MIGUEL LEDERKREMER - 61719 - ENTREGA NRO 2 - JUNIO 2020
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hash.h"
#include "lista.h"
#define INICIAL 97

#ifdef hash_destruir_dato_t
typedef void (*hash_destruir_dato_t)(void *);
#endif

struct hash {
    lista_t **listas;
    size_t cantidad;
    size_t capacidad;
    hash_destruir_dato_t destruir_dato;
};

typedef struct campo {
    char *clave;
    void *dato;
} campo_t;

struct hash_iter {
    const hash_t *hash;
    size_t pos;                // este indica cual de las listas
    lista_iter_t *iter_lista;  // este itera por cada lista
};

//FUNCIONES AUXILIARES
char *strdup(const char *clave) {
    char *palabra = malloc(sizeof(char) * (strlen(clave) + 1));
    if (palabra == NULL)
        return NULL;
    strcpy(palabra, clave);
    return palabra;
}

lista_t **tabla_crear(size_t tam) {
    lista_t **tabla = malloc(tam * sizeof(lista_t *));
    int i;
    for (i = 0; i < tam; i++) {
        tabla[i] = lista_crear();
        if (!tabla[i]) break;
    }
    // si no se pudieron crear todas las listas destruye las creadas
    if (i != tam) {
        for (; i > 0; i--) {
            lista_destruir(tabla[i], NULL);
            if (tabla[i]) break;
        }
        return NULL;
    }
    return tabla;
}

void liberar_campo(campo_t *campo) {
    free(campo->clave);
    free(campo);
}

size_t funcion_de_hash(size_t capacidad, const char *clave) {
    size_t largo = strlen(clave);
    unsigned int n = 0;
    for (unsigned int i = 0; i < largo; i++) {
        n = 31 * n + (unsigned int)clave[i];
    }
    return n % capacidad;
}

lista_iter_t *obtener_lista_iter(const hash_t *hash, const char *clave) {
    size_t ubicacion = funcion_de_hash(hash->capacidad, clave);
    lista_t *lista = hash->listas[ubicacion];
    lista_iter_t *iter = lista_iter_crear(lista);
    campo_t *actual = NULL;
    while (!lista_iter_al_final(iter)) {
        actual = lista_iter_ver_actual(iter);
        if (strcmp(clave, actual->clave) == 0) {
            break;
        }
        lista_iter_avanzar(iter);
    }
    return iter;
}

bool buscar_siguiente(hash_iter_t *iter) {
    size_t actual = iter->pos;
    for (size_t pos = actual; pos < iter->hash->capacidad; pos++) {
        if (!lista_esta_vacia(iter->hash->listas[pos])) {
            iter->pos = pos;
            // creo un iterador para la lista q tiene el primer elemento
            iter->iter_lista = lista_iter_crear(iter->hash->listas[pos]);
            if (iter->iter_lista == NULL) return false;
            return true;
        }
    }
    return false;
}

campo_t *crear_campo(const char *clave, void *dato) {
    campo_t *campo = malloc(sizeof(campo_t));
    if (campo == NULL) return NULL;
    char *clave_aux = strdup(clave);
    campo->dato = dato;
    campo->clave = clave_aux;
    return campo;
}

bool redimensionar(hash_t *hash, size_t nuevotam) {
    lista_t **nueva_tabla = tabla_crear(nuevotam);
    if (!nueva_tabla) return false;
    int i = 0;
    campo_t *campo;
    while (i < hash->capacidad) {  // para cada posicion recorro la lista, transfiero y la destruyo
        while (!lista_esta_vacia(hash->listas[i])) {
            campo = (campo_t *)lista_borrar_primero(hash->listas[i]);
            size_t ubicacion = funcion_de_hash(nuevotam, campo->clave);
            lista_insertar_ultimo(nueva_tabla[ubicacion], campo);
        }
        lista_destruir(hash->listas[i], NULL);
        i++;
    }
    hash->capacidad = nuevotam;
    free(hash->listas);
    hash->listas = nueva_tabla;
    return true;
}

// PRIMITIVAS Y FUNCIONES DEL HASH

hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t *hash = malloc(sizeof(hash_t));
    if (!hash)
        return NULL;
    hash->listas = tabla_crear(INICIAL);
    if (!hash->listas) {
        free(hash);
        return NULL;
    }
    hash->cantidad = 0;
    hash->capacidad = INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    bool resultado = true;
    lista_iter_t *lista_iter = obtener_lista_iter(hash, clave);
    campo_t *campo = lista_iter_ver_actual(lista_iter);
    if (campo) {
        //si ya existia la clave reemplaza el dato
        if (hash->destruir_dato != NULL)
            hash->destruir_dato(campo->dato);
        campo->dato = dato;
    } else {
        //si no agrega el campo
        campo_t *nuevo_campo = crear_campo(clave, dato);
        if (!nuevo_campo) return false;
        resultado = lista_iter_insertar(lista_iter, (void *)nuevo_campo);
        hash->cantidad++;
        if (hash->cantidad / hash->capacidad >= 2) {
            resultado = redimensionar(hash, hash->capacidad * 2);
        }
    }
    lista_iter_destruir(lista_iter);
    return resultado;
}

void *hash_borrar(hash_t *hash, const char *clave) {
    void *dato = NULL;
    lista_iter_t *lista_iter = obtener_lista_iter(hash, clave);
    campo_t *campo = lista_iter_ver_actual(lista_iter);
    if (campo) {
        dato = campo->dato;
        liberar_campo(campo);
        lista_iter_borrar(lista_iter);
        hash->cantidad--;
    }
    lista_iter_destruir(lista_iter);
    if (hash->cantidad / hash->capacidad <= 0.5 && hash->capacidad > INICIAL)
        redimensionar(hash, hash->capacidad / 2);
    return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave) {
    void *dato = NULL;
    lista_iter_t *lista_iter = obtener_lista_iter(hash, clave);
    campo_t *campo = lista_iter_ver_actual(lista_iter);
    if (campo) {
        dato = campo->dato;
    }
    lista_iter_destruir(lista_iter);
    return dato;
}

bool hash_pertenece(const hash_t *hash, const char *clave) {
    bool pertenece = true;
    lista_iter_t *lista_iter = obtener_lista_iter(hash, clave);
    if (lista_iter_al_final(lista_iter)) pertenece = false;
    lista_iter_destruir(lista_iter);
    return pertenece;
}

size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

void hash_destruir(hash_t *hash) {
    for (int i = 0; i < hash->capacidad; i++) {
        while (!lista_esta_vacia(hash->listas[i])) {
            campo_t *campo = (campo_t *)lista_borrar_primero(hash->listas[i]);
            if (hash->destruir_dato != NULL)
                hash->destruir_dato(campo->dato);
            liberar_campo(campo);
        }
        lista_destruir(hash->listas[i], NULL);
    }
    free(hash->listas);
    free(hash);
}

/* INSTRUCCIONES PARA EL ITERADOR
El objetivo del iterador es permitir recorrer todos los elementos 
de la tabla de hash, sin importar el orden en que se encuentren. 

Cada vez que se pide ver el elemento actual, se deben devolver 
tanto la clave como el dato, ya que el usuario no sabe cuál es 
ninguno de los dos.

Al crear el iterador, tiene que quedar apuntando al “primer” elemento 
que hay en el hash. Para ello, tiene que verificar cuál es el primer 
balde que contiene una lista no-vacía, y de esa lista crear un iterador.

Al avanzar el iterador de hash, debe avanzar el iterador de la lista actual,
 y en el caso de que llegue al final, buscar la siguiente lista no vacía.

Debe indicar que llegó al final cuando ya no queden listas por recorrer.
*/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t *hash_iter = malloc(sizeof(hash_iter_t));
    if (hash_iter == NULL) return NULL;
    hash_iter->pos = 0;
    //busco la primera lista no vacia del hash
    hash_iter->hash = hash;
    if (buscar_siguiente(hash_iter))
        return hash_iter;
    // si el hash esta vacio, apunto el iterador a 0
    hash_iter->iter_lista = NULL;
    return hash_iter;
}

bool hash_iter_avanzar(hash_iter_t *iter) {
    if (iter->iter_lista == NULL)
        return false;
    lista_iter_avanzar(iter->iter_lista);
    if (!lista_iter_al_final(iter->iter_lista)) return true;
    lista_iter_destruir(iter->iter_lista);
    iter->pos++;
    if (buscar_siguiente(iter)) {
        return true;
    }
    iter->iter_lista = NULL;
    return false;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (iter->iter_lista == NULL || lista_iter_al_final(iter->iter_lista)) return NULL;
    campo_t *campo = (campo_t *)lista_iter_ver_actual(iter->iter_lista);
    return campo->clave;
}

bool hash_iter_al_final(const hash_iter_t *iter) {
    if (iter->iter_lista != NULL)
        if (!lista_iter_al_final(iter->iter_lista)) {
            return false;
        }
    for (size_t pos = iter->pos + 1; pos < iter->hash->capacidad; pos++) {
        if (!lista_esta_vacia(iter->hash->listas[pos])) {
            return false;
        }
    }
    return true;
}

void hash_iter_destruir(hash_iter_t *iter) {
    if (iter->iter_lista) lista_iter_destruir(iter->iter_lista);
    free(iter);
}
