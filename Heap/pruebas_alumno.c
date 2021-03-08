
#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Comparar(const void *a, const void *b)
{
    int* na = (int*)a;
    int* nb = (int*)b;
    if(*na < *nb) return -1;
    if(*na == *nb) return 0;
    if(*na > *nb) return 1;
    return 0;
}

void pruebas_heap_vacio(){

    heap_t* cola = heap_crear(Comparar);
    if(!cola) return;
    print_test("heap_esta_vacio devuelve que esta vacio", heap_esta_vacio(cola));
    print_test("heap_cantidad devuelve que esta vacio (la cantidad de elementos es 0)", heap_cantidad(cola) == 0);
    print_test("heap_desencolar devuelve que esta vacio", !heap_desencolar(cola));
    print_test("heap_ver_max devuelve que esta vacio", !heap_ver_max(cola));
    heap_destruir(cola, NULL);

}

void pruebas_heap_un_elemento(){

     heap_t* cola = heap_crear(Comparar);
     int* valor1 = (int*)malloc(sizeof(int));
     *valor1 = 10;
     void* valor2 = NULL;
     valor2 = (void*)valor1;
     print_test("se encolo el valor correctamente",  heap_encolar(cola,valor2));
     print_test("el tamanio del heap es el correcto", heap_cantidad(cola) == 1);
     void* valor3 = heap_desencolar(cola);
     print_test("se desencolo el valor correctamente",  valor2 == valor3);
     free(valor1);
     heap_destruir(cola, free);
}

void pruebas_con_heap_crear_arr(){
    int* valor = NULL;
    void** vector = (void**)malloc(3 * sizeof(void*));
    bool ok = true;
    for(int i = 1; i < 4; i++){

        valor = (int*)malloc(sizeof(int));
        *valor = i;
        vector[i-1] = (void*)valor;
    }

    heap_t* heap = heap_crear_arr(vector,3,Comparar);
    print_test("heap_crear_arr creo el heap correctamente con el vector (1, 2, 3)", heap);
    print_test("el tamanio del heap es el correcto", heap_cantidad(heap) == 3);
    valor = (int*)heap_ver_max(heap);
    print_test("el elemento de mayor prioridad quedo al principio del vector", *valor == 3);

    for(int i = 3;i > 0;i--)
    {
        valor = (int*)heap_desencolar(heap);
        if(*valor != i) ok = false;
        free(valor);
        if(!ok)break;
    }
    print_test("el heap se desencolo en el orden correcto de prioridad", ok);
    print_test("esl heap quedo vacio", heap_esta_vacio(heap));
    heap_destruir(heap,NULL);
    free(vector);

    vector = (void**)malloc(3 * sizeof(void*));

    valor = (int*)malloc(sizeof(int));

    *valor = 2;

    vector[0] = (void*)valor;

    valor = (int*)malloc(sizeof(int));

    *valor = 3;

    vector[1] = (void*)valor;

    valor = (int*)malloc(sizeof(int));

    *valor = 1;

    vector[2] = (void*)valor;

    heap = heap_crear_arr(vector,3,Comparar);

    print_test("heap_crear_arr creo el heap correctamente con el vector (2, 3, 1)", heap);

    print_test("el tamanio del heap es el correcto", heap_cantidad(heap) == 3);

    valor = (int*)heap_ver_max(heap);

    print_test("el elemento de mayor prioridad quedo al principio del vector", *valor == 3);
    ok = true;
    valor = (int*)heap_desencolar(heap);
    if(*valor != 3) ok = false;
    free(valor);
    valor = (int*)heap_desencolar(heap);
    if(*valor != 2) ok = false;
    free(valor);
    valor = (int*)heap_desencolar(heap);
    if(*valor != 1) ok = false;
    free(valor);
    print_test("se desencolaron todos los elementos el heap en el orden correcto", ok);
    print_test("el heap quedo vacio", heap_esta_vacio(heap));

    free(vector);
    heap_destruir(heap, free);


}

void pruebas_con_heap_encolar(){

    heap_t* heap = heap_crear(Comparar);
    int* valor = NULL;
    bool ok = true;

    valor = (int*)malloc(sizeof(int));

    *valor = 1;

    ok = heap_encolar(heap, (void*)valor);

    if(ok){

        valor = (int*)malloc(sizeof(int));

        *valor = 2;

        ok = heap_encolar(heap, (void*)valor);

        if(ok){

            valor = (int*)malloc(sizeof(int));

            *valor = 3;

            ok = heap_encolar(heap, (void*)valor);

        }
    }
    print_test("se encolaron 3 elementos de forma exitosa", ok);
    valor = (int*)heap_ver_max(heap);
    print_test("el elemento de mayor prioridad quedo al principio del heap", *valor == 3);
    ok = true;
    valor = (int*)heap_desencolar(heap);

    if(*valor != 3) ok = false;

    free(valor);

    if(ok){

        valor = (int*)heap_desencolar(heap);

        if(*valor != 2) ok = false;

        free(valor);

        if(ok){

            valor = (int*)heap_desencolar(heap);

            if(*valor != 1) ok = false;

            free(valor);

        }
    }
    print_test("los elementos del heap se desencolaron en el orden correcto", ok);
    ok = true;
    valor = (int*)malloc(sizeof(int));

    *valor = 1;

    ok = heap_encolar(heap, (void*)valor);

    if(ok){

        valor = (int*)malloc(sizeof(int));

        *valor = 1;

        ok = heap_encolar(heap, (void*)valor);

        if(ok){

            valor = (int*)malloc(sizeof(int));

            *valor = 1;

            ok = heap_encolar(heap, (void*)valor);

            if(ok){

                valor = (int*)malloc(sizeof(int));

                *valor = 15;

                ok = heap_encolar(heap, (void*)valor);
            }
        }
    }
    print_test("se encolaron 4 elementos de forma exitosa", ok);
    valor = (int*)heap_ver_max(heap);
    print_test("el elemento de mayor prioridad quedo al principio del heap", *valor == 15);
    heap_destruir(heap, free);
}

void pruebas_heap_varios_elementos(){

    pruebas_con_heap_crear_arr();
    pruebas_con_heap_encolar();
}
void pruebas_heap_volumen(){

    srand((unsigned int)time(NULL));
    heap_t* heap = heap_crear(Comparar);
    int* valor = NULL;
    bool ok = true;
    for(int i = 0; i < 101; i++){

        valor = (int*)malloc(sizeof(int));
        *valor = rand();
        ok = heap_encolar(heap, (void*)valor);
        if(!ok)break;
    }
    print_test("se encolaron 100 elementos satisfactoriamente", ok);
    ok = true;
    int* valor_aux = (int*)heap_desencolar(heap);
    for(int i = 100; i > 0; i--){


        valor = (int*)heap_desencolar(heap);
        if(*valor_aux < *valor) ok = false;
        free(valor_aux);
        valor_aux = valor;
        if(!ok)break;
    }
    free(valor);
    print_test("se desencolaron los 100 elementos en el orden correcto", ok);
    print_test("el heap quedo vacio", heap_esta_vacio(heap));
    ////////////////////////////
    for(int i = 0; i < 1001; i++){

        valor = (int*)malloc(sizeof(int));
        *valor = rand();
        ok = heap_encolar(heap, (void*)valor);
        if(!ok)break;
    }
    print_test("se encolaron 1000 elementos satisfactoriamente", ok);
    ok = true;
    valor_aux = (int*)heap_desencolar(heap);
    for(int i = 1000; i > 0; i--){

        valor = (int*)heap_desencolar(heap);
        if(*valor_aux < *valor) ok = false;
        free(valor_aux);
        valor_aux = valor;
        if(!ok)break;
    }
    free(valor);
    print_test("se desencolaron los 1000 elementos en el orden correcto", ok);
    print_test("el heap quedo vacio", heap_esta_vacio(heap));
    //////////////////////////////
    for(int i = 0; i < 10001; i++){


        valor = (int*)malloc(sizeof(int));
        *valor = rand();
        ok = heap_encolar(heap, (void*)valor);
        if(!ok)break;
    }
    print_test("se encolaron 10000 elementos satisfactoriamente", ok);
    ok = true;
    valor_aux = (int*)heap_desencolar(heap);
    for(int i = 10000; i > 0; i--){

        valor = (int*)heap_desencolar(heap);
        if(*valor_aux < *valor) ok = false;
        free(valor_aux);
        valor_aux = valor;
        if(!ok)break;
    }
    free(valor);
    print_test("se desencolaron los 10000 elementos en el orden correcto", ok);
    print_test("el heap quedo vacio", heap_esta_vacio(heap));
    //////////////////////////
    for(int i = 0; i < 100001; i++){

        valor = (int*)malloc(sizeof(int));
        *valor = rand();
        ok = heap_encolar(heap, (void*)valor);
        if(!ok)break;
    }
    print_test("se encolaron 100000 elementos satisfactoriamente", ok);
    ok = true;
    valor_aux = (int*)heap_desencolar(heap);
    for(int i = 100000; i > 0; i--){

        valor = (int*)heap_desencolar(heap);
        if(*valor_aux < *valor) ok = false;
        free(valor_aux);
        valor_aux = valor;
        if(!ok)break;
    }
    free(valor);
    print_test("se desencolaron los 100000 elementos en el orden correcto", ok);
    print_test("el heap quedo vacio", heap_esta_vacio(heap));

    heap_destruir(heap, free);

}


void pruebas_heap_alumno(){

    pruebas_heap_vacio();
    pruebas_heap_un_elemento();
    pruebas_heap_varios_elementos();
    pruebas_heap_volumen();
}
