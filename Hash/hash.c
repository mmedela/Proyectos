#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

#define TAM_INI_HASH 97
#define CANT_INI_HASH 0

#define FACTOR_REDIM 4
#define FACTOR_DE_CHOQUE    75

#define POS_INICIAL 0
#define SON_IGUALES 0

const char OCUPADO = 'o';
const char BORRADO = 'b';
const char VACIO =   'v';

typedef void (*hash_destruir_dato_t)(void *);

typedef struct nodo{

    char* clave;
    void* dato;
    char estado;
}nodo_t;


typedef struct hash{

    nodo_t* tabla_hash;
    size_t cant;
    size_t tam;
    hash_destruir_dato_t destruir_dato;
}hash_t;

typedef struct hash_iter{

    hash_t* hash;
    size_t actual;
}hash_iter_t;

unsigned long long hashear (void *key, int len ) {
    unsigned char *p = key;
    unsigned long long h = 0xcbf29ce484222325ULL;
    int i;

    for ( i = 0; i < len; i++ )
      h = ( h ^ p[i] ) * 0x100000001b3ULL;

   return h;
}

long int posicion (char* key, size_t tam){

    return (hashear((void*)key, (int)strlen(key) + 1 ) % tam);
}

nodo_t* tabla_crear(size_t tamanio){

    nodo_t* tabla = malloc(tamanio*sizeof(nodo_t));
    if(!tabla) return NULL;
    for(int i = 0; i < tamanio; i++){

        tabla[i].estado = VACIO;
        tabla[i].clave = NULL;
        tabla[i].dato = NULL;

    }
    return tabla;
}

size_t buscar_siguiente(const hash_t* hash, size_t actual){

    size_t siguiente = actual + 1, tam = hash->tam;
    bool termine = false;
    while(siguiente < tam && !termine){

        if(hash->tabla_hash[siguiente].clave != NULL){

            termine = true;
            siguiente--;
        }
        siguiente++;
    }
    if(termine)return siguiente;
    return tam;
}

hash_t* hash_crear(hash_destruir_dato_t destruir_dato){

    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash) return NULL;
    hash->cant = CANT_INI_HASH;
    hash->tam = TAM_INI_HASH;
    hash->destruir_dato = destruir_dato;
    hash->tabla_hash = tabla_crear(TAM_INI_HASH);
    if(!(hash->tabla_hash)){
        free(hash);
        hash = NULL;
    }
    return hash;
}

bool tabla_redimensionar(hash_t* hash){

    bool respuesta = true;
    size_t tam_nuevo = hash->tam * FACTOR_REDIM, tam_aux = hash->tam, i = POS_INICIAL, cant = hash->cant;
    nodo_t* tabla_nueva = tabla_crear(tam_nuevo);
    if(!tabla_nueva)return false;
    nodo_t* tabla_aux = NULL;
    tabla_aux = hash->tabla_hash;
    hash->tabla_hash = tabla_nueva;
    hash->tam = tam_nuevo;
    while((i < tam_aux) && respuesta){

        if(tabla_aux[i].estado == OCUPADO) respuesta = hash_guardar(hash, tabla_aux[i].clave, tabla_aux[i].dato);

        i++;
    }
    if(respuesta){
        i = POS_INICIAL;
        while (i < tam_aux){

            if(tabla_aux[i].clave) free(tabla_aux[i].clave);
            i++;
        }
        free(tabla_aux);
    }else{
        while(i > POS_INICIAL){

            if(tabla_nueva[i].clave) free(tabla_nueva[i].clave);
            i--;
        }
        free(tabla_nueva);
        hash->tam = tam_aux;
        hash->tabla_hash = tabla_aux;
    }
    hash->cant = cant;
    return respuesta;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){

    bool respuesta = true;

    if(!clave)return false;

    size_t len = strlen(clave);
    //if(len<1)return false;

    char* clave_aux = malloc((len + 1)*sizeof(char));

    if (!clave_aux) return false;

    strcpy(clave_aux, clave);

    long int pos = POS_INICIAL;
    if(len > 0)pos = posicion(clave_aux, hash->tam);
    free(clave_aux);
    bool existe = false;

    while((hash->tabla_hash[pos].estado != VACIO) && (!existe)){

        if(hash->tabla_hash[pos].clave != NULL) {

            if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES) {

                existe = true;
                pos--;
            }
        }
        pos++;
        if(pos == hash->tam) pos = POS_INICIAL;
    }
    if(hash->tabla_hash[pos].clave != NULL){

        if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES){

            if(hash->destruir_dato != NULL)hash->destruir_dato(hash->tabla_hash[pos].dato);
        }
    }else{
        hash->cant++;
        hash->tabla_hash[pos].estado = OCUPADO;
        hash->tabla_hash[pos].clave = malloc((len + 1)*sizeof(char));
        strcpy(hash->tabla_hash[pos].clave, clave);
    }
    hash->tabla_hash[pos].dato = dato;
    if(((100*hash->cant)/hash->tam) > FACTOR_DE_CHOQUE) respuesta = tabla_redimensionar(hash);
    return respuesta;
}

void* hash_borrar(hash_t *hash, const char *clave){

    if(hash->cant == 0) return NULL;
    if(!clave)return NULL;

    size_t len = strlen(clave);
    //if(len<1)return NULL;

    char* clave_aux = malloc((len + 1)*sizeof(char));

    if (!clave_aux) return NULL;

    strcpy(clave_aux, clave);

    long int pos = POS_INICIAL;
    if(len > 0)pos = posicion(clave_aux, hash->tam);
    free(clave_aux);
    if(hash->tabla_hash[pos].clave != NULL){

        if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES){

            free(hash->tabla_hash[pos].clave);
            hash->tabla_hash[pos].clave = NULL;
            hash->tabla_hash[pos].estado = BORRADO;
            hash->cant--;
            return hash->tabla_hash[pos].dato;
        }
    }
    long int aux = pos;
    pos++;
    while((hash->tabla_hash[pos].estado != VACIO) && (pos != aux)){

        if(hash->tabla_hash[pos].clave != NULL){

            if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES){

                free(hash->tabla_hash[pos].clave);
                hash->tabla_hash[pos].clave = NULL;
                hash->tabla_hash[pos].estado = BORRADO;
                hash->cant--;
                return hash->tabla_hash[pos].dato;
            }
        }
        pos++;
        if(pos == hash->tam) pos = POS_INICIAL;
    }
    return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){

    if(!clave)return NULL;

    size_t len = strlen(clave);
   // if(len<1)return NULL;

    if(hash->cant == 0) return NULL;

    char* clave_aux = malloc((len + 1)*sizeof(char));

    if (!clave_aux) return NULL;

    strcpy(clave_aux, clave);

    long int pos = POS_INICIAL;
    if(len > 0)pos = posicion(clave_aux, hash->tam);
    free(clave_aux);
    if(hash->tabla_hash[pos].clave != NULL){

        if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES) return hash->tabla_hash[pos].dato;
    }
    long int aux = pos;
    pos++;
    while((hash->tabla_hash[pos].estado != VACIO) && (pos != aux)){

        if(hash->tabla_hash[pos].clave != NULL){

            if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES) return hash->tabla_hash[pos].dato;
        }
        pos++;
        if(pos == hash->tam) pos = POS_INICIAL;
    }
    return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){

    if(hash->cant == 0) return false;

    if(!clave)return false;

    size_t len = strlen(clave);
    //if(len<1)return false;

    char* clave_aux = malloc((len + 1)*sizeof(char));

    if (!clave_aux) return false;

    strcpy(clave_aux, clave);

    long int pos = POS_INICIAL;
    if(len > 0)pos = posicion(clave_aux, hash->tam);
    free(clave_aux);
    if(hash->tabla_hash[pos].clave != NULL){

        if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES) return true;
    }
    long int aux = pos;
    pos++;
    while((hash->tabla_hash[pos].estado != VACIO) && (pos != aux)){

        if(hash->tabla_hash[pos].clave != NULL){

            if(strcmp(hash->tabla_hash[pos].clave, clave) == SON_IGUALES) return true;
        }
        pos++;
        if(pos == hash->tam) pos = POS_INICIAL;
    }
    return false;
}

size_t hash_cantidad(const hash_t *hash){

    return hash->cant;
}

void hash_destruir(hash_t *hash){

    for(int i = 0; i < hash->tam; i++){

        if(hash->tabla_hash[i].clave != NULL){

            free(hash->tabla_hash[i].clave);
            if(hash->destruir_dato != NULL){

                hash->destruir_dato(hash->tabla_hash[i].dato);
            }
        }
    }
    free(hash->tabla_hash);
    free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){

    if(!hash) return NULL;
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(!iter) return NULL;
    iter->hash = (hash_t*)hash;
    iter->actual = buscar_siguiente(hash, -1);
    return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){

    if(hash_iter_al_final(iter))return false;

    size_t siguiente = buscar_siguiente(iter->hash, iter->actual);

    iter->actual = siguiente;
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){

    if(hash_iter_al_final(iter)) return NULL;
    size_t pos = iter->actual;
    return iter->hash->tabla_hash[pos].clave;
}

bool hash_iter_al_final(const hash_iter_t *iter){

    if(iter->actual == iter->hash->tam) return true;
    return false;
}

void hash_iter_destruir(hash_iter_t* iter){

    free(iter);
}


