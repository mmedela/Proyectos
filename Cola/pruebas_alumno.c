#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

void evento(void* dato){

    free(dato);

}

void pruebas_cola_vacia(){

    void* var3 = NULL;

    void* dato_leido = NULL;

    cola_t* cola = cola_crear();

    print_test("la cola fue creada", cola!=NULL);

    var3 = cola_ver_primero(cola);

    print_test("lee el priemr elemento de la cola vacia", var3 == NULL);

    dato_leido = cola_desencolar(cola);

    print_test("intenta desencolar cola vacia", dato_leido == NULL);

    print_test("la cola esta vacia", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

void pruebas_uso_simple(){

    int i = 0;

    int* dato = NULL;

    void* dato_leido = NULL;

    dato = malloc(sizeof(int));

    cola_t* cola = cola_crear();



    if (!cola) return;

    *dato = 3;

    print_test("la cola fue encolada", cola_encolar(cola, dato));

    dato_leido = cola_ver_primero(cola);

    print_test("se leyo el primero", dato_leido == dato);

    dato_leido = cola_desencolar(cola);

   print_test("la cola se desencolo", dato == dato_leido);
    free(dato);

    bool todo_ok = true;
   while (i<10 && todo_ok){

        dato = malloc(sizeof(int));
        *dato = i;
        todo_ok = cola_encolar(cola, dato);
        i++;
    }
    print_test("se encolaron", todo_ok);
    cola_destruir(cola, evento);
}

void pruebas_volumen(){

    bool respuesta = true;
    int i = 0;
    void* dato_leido;
    cola_t* cola = cola_crear();
    if(!cola) return;
    int* dato;
    while (i<1000 && respuesta){

        dato = malloc(sizeof(int));
        *dato = i;
        respuesta = cola_encolar(cola, dato);
        i++;
    }

    print_test("se encolaron 1000 elementos",respuesta);

    i=0;

    while (i<1000 && respuesta){

        dato_leido = cola_desencolar(cola);


        dato = (int*) dato_leido;
        if (*dato != i){

            respuesta = false;
        }
        evento(dato_leido);
        i++;
    }

    print_test("se desencolaron 1000 elementos", respuesta);

    print_test("la cola quedo vacia", cola_esta_vacia(cola));
    i = 0;
    while (i<5000 && respuesta){

        dato = malloc(sizeof(int));
        *dato = i;
        respuesta = cola_encolar(cola, dato);
        i++;
    }

    print_test("se encolaron 5000 elementos",respuesta);

    i=0;


    while (i<5000 && respuesta){

        dato_leido = cola_desencolar(cola);


        dato = (int*) dato_leido;
        if (*dato != i){

            respuesta = false;
        }
        evento(dato_leido);
        i++;
    }

    print_test("se desencolaron 5000 elementos", respuesta);

    print_test("la cola quedo vacia", cola_esta_vacia(cola));
    i = 0;
    while (i<10000 && respuesta){

        dato = malloc(sizeof(int));
        *dato = i;
        respuesta = cola_encolar(cola, dato);
        i++;
    }

    print_test("se encolaron 10000 elementos",respuesta);

    i=0;

    while (i<10000 && respuesta){

        dato_leido = cola_desencolar(cola);


        dato = (int*) dato_leido;
        if (*dato != i){

            respuesta = false;
        }
        evento(dato_leido);
        i++;
    }

    print_test("se desencolaron 10000 elementos", respuesta);

    print_test("la cola quedo vacia", cola_esta_vacia(cola));

    i = 0;
    while (i<20000 && respuesta){

        dato = malloc(sizeof(int));
        *dato = i;
        respuesta = cola_encolar(cola, dato);
        i++;
    }

    print_test("se encolaron 20000 elementos",respuesta);

    i=0;

    while (i<20000 && respuesta){

        dato_leido = cola_desencolar(cola);


        dato = (int*) dato_leido;
        if (*dato != i){

            respuesta = false;
        }
        evento(dato_leido);
        i++;
    }

    print_test("se desencolaron 20000 elementos", respuesta);

    print_test("la cola quedo vacia", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

void pruebas_cola_alumno(){

    pruebas_cola_vacia();
    pruebas_uso_simple();
    pruebas_volumen();
}
