#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

void destruir(void* dato){

    free(dato);
}

bool visitar(void* dato, void* extra){

        if (*(int*)dato == *(int*)extra)print_test("se encontro el dato", *(int*)dato == *(int*)extra);
    return !(*(int*)dato == *(int*)extra);
}


void pruebas_lista_uso_basico(){

    lista_t* lista = NULL;
    print_test("la lista es nula", !lista);
    lista = lista_crear();
    print_test("la lista se creo correctamente", lista != NULL);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    print_test("intento desenlistar una lista vacia", !lista_borrar_primero(lista));
    print_test("leo el primer elemento de una lista vacia",!lista_ver_primero(lista));
    print_test("leo el ultimo elemento de una lista vacia",!lista_ver_ultimo(lista));
    print_test("la lista tiene largo 1", lista_largo(lista) == 0);
    void* valor = malloc(sizeof(void*));
    print_test("enlisto el ultimo elemento en la lista vacia", lista_insertar_ultimo(lista, valor));
    print_test("la lista tiene un solo elemento", lista_largo(lista) == 1);
    print_test("se elimino el primer elemento la lista", valor == lista_borrar_primero(lista));
    destruir(valor);
    print_test("se borro el unico elemento de la lista", lista_esta_vacia(lista));
    valor = malloc(sizeof(void*));
    print_test("enlisto un elemento al principio de un lista vacia", lista_insertar_primero(lista, valor));
    print_test("leo el primer elemento",valor == lista_ver_primero(lista));
    valor = malloc(sizeof(void*));
    print_test("enlisto un elemento en una lista de un solo elemento", lista_insertar_primero(lista, valor));
    valor = malloc(sizeof(void*));
    print_test("enlisto un elemento al final habiendo otro preexistente", lista_insertar_ultimo(lista,valor));
    print_test("la lista no esta vacia", !lista_esta_vacia(lista));
    print_test("lista tiene 3 elementos", lista_largo(lista) == 3);

    bool todo_ok;
    for(int i = 0; i < 5; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_insertar_primero(lista, valor);
        if(!todo_ok) break;
    }
    print_test("se enlistaron 5 elementos en la primera posicion", todo_ok);
    print_test("leo el primer elemento", valor == lista_ver_primero(lista));
    print_test("se elimino el primer elemento de una lista con varios elementos", valor == lista_borrar_primero(lista));
    destruir(valor);
    for(int i = 0; i < 5; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_insertar_ultimo(lista, valor);
        if(!todo_ok) break;
    }
    print_test("se enlistaron 5 elementos en la ultima posicion", todo_ok);
    print_test("el ultimo elemento agregado al final de la lista, esta al final de la lista", valor == lista_ver_ultimo(lista));
    lista_destruir(lista, destruir);
    lista_t* lista2 = lista_crear();
    lista_destruir(lista2, destruir);
}

void pruebas_lista_volumen(){

    lista_t* lista = NULL;
    print_test("la lista es nula", !lista);
    lista = lista_crear();
    print_test("la lista se creo correctamente", lista != NULL);

    void* valor = malloc(sizeof(void*));
    void* valor_aux = valor;
    bool todo_ok = true;
    for (int i = 0; (i < 1000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_primero(lista, valor);
        }
    }
    print_test("se añadieron 1000 elementos al principio de la lista", todo_ok);
    print_test("la lista tiene largo 1000", lista_largo(lista) == 1000);
    todo_ok = true;
    for (int i = 0; (i < 1000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_ultimo(lista, valor);
        }
    }
    destruir(valor_aux);
    print_test("se añadieron 1000 elementos al final de la lista", todo_ok);
    print_test("la lista tiene largo 2000", lista_largo(lista) == 2000);
    for (int i = 0; (i < 2000) && todo_ok; i++){

        valor = lista_borrar_primero(lista);
        if(valor == NULL) todo_ok = false;
        destruir(valor);
    }
    print_test("se eliminaron 2000 elementos de la lista", todo_ok);
    print_test("la lista tiene largo 0", lista_largo(lista) == 0);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    for (int i = 0; (i < 5000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_primero(lista, valor);
        }
    }
    print_test("se añadieron 5000 elementos al principio de la lista", todo_ok);
    print_test("la lista tiene largo 5000", lista_largo(lista) == 5000);
    todo_ok = true;
    for (int i = 0; (i < 5000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_ultimo(lista, valor);
        }
    }
    print_test("se añadieron 5000 elementos al final de la lista", todo_ok);
    print_test("la lista tiene largo 10000", lista_largo(lista) == 10000);
    for (int i = 0; (i < 10000) && todo_ok; i++){

        valor = lista_borrar_primero(lista);
        if(valor == NULL) todo_ok = false;
        destruir(valor);
    }
    print_test("se eliminaron 10000 elementos de la lista", todo_ok);
    print_test("la lista tiene largo 0", lista_largo(lista) == 0);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    for (int i = 0; (i < 10000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_primero(lista, valor);
        }
    }
    print_test("se añadieron 10000 elementos al principio de la lista", todo_ok);
    print_test("la lista tiene largo 10000", lista_largo(lista) == 10000);
    todo_ok = true;
    for (int i = 0; (i < 10000) && todo_ok && (valor != NULL); i++){

        valor = malloc(sizeof(void*));
        if (valor != NULL){
            todo_ok = lista_insertar_ultimo(lista, valor);
        }
    }
    print_test("se añadieron 10000 elementos al final de la lista", todo_ok);
    print_test("la lista tiene largo 20000", lista_largo(lista) == 20000);
    for (int i = 0; (i < 20000) && todo_ok; i++){

        valor = lista_borrar_primero(lista);
        if(valor == NULL) todo_ok = false;
        destruir(valor);
    }
    print_test("se eliminaron 20000 elementos de la lista", todo_ok);
    print_test("la lista tiene largo 0", lista_largo(lista) == 0);
    print_test("la lista esta vacia", lista_esta_vacia(lista));
    lista_destruir(lista, NULL);
}
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void prueba_iter_uso_basico(){

    lista_t* lista = lista_crear();
    if (lista == NULL) return;
    lista_iter_t* iter = NULL;
    iter = lista_iter_crear(lista);
    print_test("se intento crear un iterador para una lista vacia", iter!= NULL);
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
    lista = lista_crear();
    bool todo_ok = true;
    void* valor = NULL;
    valor = malloc(sizeof(void*));
    void* actual = NULL;
    todo_ok = lista_insertar_primero(lista, valor);
    if(todo_ok) iter = lista_iter_crear(lista);
    print_test("se creo un iterador para una lista de un solo elemento", iter!= NULL);
    actual = lista_iter_ver_actual(iter);
    print_test("se leyo correctamente la poscicion actual del iterador", actual == valor);
    print_test("se pudo iterar una lista de un solo elemento", lista_iter_avanzar(iter));
    print_test("el iterador esta el final de la lista de un solo elemento", lista_iter_al_final(iter));
    actual = lista_iter_ver_actual(iter);
    print_test("se leyo el elemento de finalizacion de iteracion", actual == NULL);
    lista_iter_destruir(iter);
    for(int i = 0; i < 5; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_insertar_primero(lista, valor);
        if(!todo_ok) break;
    }

    if (todo_ok)  iter = lista_iter_crear(lista);
    print_test("se creo el iterador para una lista con varios elementos", iter != NULL);
    print_test("el iterador itero", lista_iter_avanzar(iter));
    actual = lista_iter_ver_actual(iter);
    print_test("se leyo correctamente el elemento actual en una lista de varios elementos", *(int*)actual == 3);
    valor = lista_iter_borrar(iter);
    actual = lista_iter_ver_actual(iter);
    print_test("se elimino el lemento actual",(*(int*)valor == 3) && (*(int*)actual == 2));
    print_test("el iterador no esta al final de la lista", !lista_iter_al_final(iter));
    destruir(valor);
    lista_destruir(lista, destruir);
    lista_iter_destruir(iter);

    lista = lista_crear();
    if (lista == NULL) return;
    valor = malloc(sizeof(void*));
    lista_insertar_primero(lista, valor);
    iter = lista_iter_crear(lista);
    if (iter == NULL) return;
    actual = lista_iter_borrar(iter);
    print_test("se borro el unico elemento del iterador",(valor == actual) && lista_iter_al_final(iter) && (lista_ver_primero(lista) == NULL));
    destruir(actual);
    lista_iter_destruir(iter);
    todo_ok = true;
    for(int i = 0; i < 5; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_insertar_primero(lista, valor);
        if(!todo_ok) break;
    }
    iter = lista_iter_crear(lista);
    actual = lista_iter_borrar(iter);
    print_test("se leyo y borro el primer elemento del iterador", (*(int*)actual == 4) && (*(int*)lista_ver_primero(lista) == 3));
    destruir(actual);
    size_t largo = lista_largo(lista);
    for(int i =0; i < largo-1; i++){
        todo_ok = lista_iter_avanzar(iter);
    }
    if(todo_ok) if (!lista_iter_al_final(iter)) actual = lista_iter_borrar(iter);
    print_test("se leyo y borro el ultimo elemento del iter", (*(int*)actual == 0) && (*(int*)lista_ver_ultimo(lista) == 1));
    destruir(actual);
    valor = malloc(sizeof(void*));
    todo_ok = lista_iter_insertar(iter, valor);
    if (todo_ok) actual = lista_ver_ultimo(lista);
    print_test("se inserto correctamente un elemento al final de la lista", actual == valor);
    lista_iter_destruir(iter);
    lista_destruir(lista, destruir);
    lista = lista_crear();
    todo_ok = true;
    for(int i = 0; i < 5; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_insertar_primero(lista, valor);
        if(!todo_ok) break;
    }
    if (todo_ok){

        iter = lista_iter_crear(lista);
        if(lista_iter_avanzar(iter)){

            valor = malloc(sizeof(void*));
            todo_ok = lista_iter_insertar(iter, valor);
            if (todo_ok) actual = lista_iter_borrar(iter);
            print_test("se inserto correctamente un elemento a la mitad de la lista", (actual == valor)&&(*(int*)lista_iter_ver_actual(iter)==3));
            destruir(valor);
            lista_iter_destruir(iter);
        }
    }
    iter = lista_iter_crear(lista);
    if (iter != NULL){

        valor = malloc(sizeof(void*));
        todo_ok = lista_iter_insertar(iter, valor);
        if (todo_ok) {

            actual = lista_iter_ver_actual(iter);
            print_test("se inserto un elemento correctamente al principio de una lista", (actual == valor)&&(lista_ver_primero(lista) == valor));
        }
    }
    lista_destruir(lista, destruir);
    lista_iter_destruir(iter);

}
void pruebas_iter_volumen(){

    lista_t* lista = lista_crear();
    if (lista == NULL) return;
    bool todo_ok = true;
    void* valor = NULL;
    todo_ok = lista_insertar_primero(lista, valor);
    lista_iter_t* iter = NULL;
    if (todo_ok && (lista_largo(lista) == 1))  iter = lista_iter_crear(lista);
    for(int i = 0; i < 1000; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_iter_insertar(iter, valor);
        if(!todo_ok) break;
    }
    print_test("se insertaron 1000 elementos al principio", lista_largo(lista) == 1001);
    for(int i = 0; i<1000; i++){

        destruir(lista_iter_borrar(iter));
    }
    print_test("se eliminaron 1000 elementos", lista_largo(lista) == 1);
    for(int i = 0; i < 10000; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_iter_insertar(iter, valor);
        if(!todo_ok) break;
    }
    print_test("se insertaron 10000 elementos al principio", lista_largo(lista) == 10001);
    for(int i = 0; i<10000; i++){

        destruir(lista_iter_borrar(iter));
    }
    print_test("se eliminaron 10000 elementos", lista_largo(lista) == 1);
    for(int i = 0; i < 20000; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_iter_insertar(iter, valor);
        if(!todo_ok) break;
    }
    print_test("se insertaron 20000 elementos al principio", lista_largo(lista) == 20001);
    for(int i = 0; i<20000; i++){

        destruir(lista_iter_borrar(iter));
    }
    print_test("se eliminaron 20000 elementos", lista_largo(lista) == 1);
    for(int i = 0; i < 61000; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_iter_insertar(iter, valor);
        if(!todo_ok) break;
    }
    print_test("se insertaron 61000 elementos al principio", lista_largo(lista) == 61001);
    for(int i = 0; i<61000; i++){

        destruir(lista_iter_borrar(iter));
    }
    print_test("se eliminaron 61000 elementos", lista_largo(lista) == 1);
    for(int i = 0; i < 100000; i++){

        valor = malloc(sizeof(void*));
        *(int*)valor = i;
        todo_ok =lista_iter_insertar(iter, valor);
        if(!todo_ok) break;
    }
    print_test("se insertaron 100000 elementos al principio", lista_largo(lista) == 100001);
    for(int i = 0; i<100000; i++){

        destruir(lista_iter_borrar(iter));
    }
    print_test("se eliminaron 100000 elementos", lista_largo(lista) == 1);
    destruir(lista_iter_borrar(iter));
    lista_destruir(lista, NULL);
    lista_iter_destruir(iter);
}


void prueba_iter_interno(){

    lista_t* lista = lista_crear();
    bool todo_ok = true;
    void* dato = NULL;
    void* extra = NULL;
    for(int i = 0; i < 1000; i++){

        dato = malloc(sizeof(void*));
        *(int*)dato = i;
        todo_ok = lista_insertar_primero(lista, dato);
        if(!todo_ok) break;
    }
    extra = malloc(sizeof(void*));
    *(int*)extra = 500;
    lista_iterar(lista, visitar, extra);
    free(extra);
    lista_destruir(lista, destruir);

}

void pruebas_lista_alumno (){

    pruebas_lista_uso_basico();
    pruebas_lista_volumen();
    prueba_iter_uso_basico();
    pruebas_iter_volumen();
    prueba_iter_interno();
}
