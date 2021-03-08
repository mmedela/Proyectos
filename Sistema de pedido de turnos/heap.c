#include "heap.h"

#include <math.h>
#include <stdbool.h> /* bool */
#include <stddef.h>  /* size_t */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define CAPACIDAD_INICIAL 100
#define FACTOR_AMPLIACION 2
#define FACTOR_REDUCCION 2
#define CAPACIDAD_MINIMA 4

struct heap {
    void **datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

heap_t *heap_crear_tam(cmp_func_t cmp, size_t tam) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) {
        return NULL;
    }
    heap->datos = malloc(tam * sizeof(void *));
    if (!heap->datos) {
        free(heap);
        return NULL;
    }
    heap->tam = tam;
    heap->cant = 0;
    heap->cmp = cmp;
    return heap;
}

heap_t *heap_crear(cmp_func_t cmp) {
    return heap_crear_tam(cmp, CAPACIDAD_INICIAL);
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
    if (destruir_elemento) {
        for (size_t i = 0; i < heap->cant; i++) {
            destruir_elemento(heap->datos[i]);
        }
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cant == 0;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    return heap->datos[0];
}

void swap(void **arr, size_t pos1, size_t pos2) {
    // printf("swapeo %s con %s\n", (char *)arr[pos1], (char *)arr[pos2]);
    void *temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
    return;
}

void upheap(void **arr, size_t hijo, cmp_func_t cmp) {
    if (hijo == 0) return;
    size_t padre = (hijo - 1) / 2;
    // printf("Pos padre: %d, Dato padre: %s, Pos hijo: %d, Dato hijo: %s\n", padre, (char*)heap->datos[padre], hijo, (char*)heap->datos[hijo]);
    if (cmp(arr[padre], arr[hijo]) < 0) {
        swap(arr, padre, hijo);
        upheap(arr, padre, cmp);
    }
}

bool heap_redimensionar(heap_t *heap, size_t cap_nueva) {
    void **nuevos_datos = realloc(heap->datos, cap_nueva * sizeof(void *));
    if (nuevos_datos == NULL) {
        return false;
    }
    heap->datos = nuevos_datos;
    heap->tam = cap_nueva;
    return true;
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (heap->cant + 1 > heap->tam) {
        if (heap_redimensionar(heap, heap->tam * FACTOR_AMPLIACION) == false) {
            return false;
        }
    }
    size_t pos = (int)heap->cant;
    // printf("Encolando %s en posicion %d\n", (char *)elem, pos);
    heap->datos[pos] = elem;
    heap->cant++;
    upheap(heap->datos, pos, heap->cmp);
    return true;
}

size_t calculo_mayor(void **arr, size_t padre, size_t izq, size_t der, cmp_func_t cmp) {
    if ((cmp(arr[izq], arr[padre]) >= 0) && (cmp(arr[izq], arr[der]) >= 0)) {
        return izq;
    }
    if ((cmp(arr[der], arr[padre]) >= 0) && (cmp(arr[der], arr[izq]) >= 0)) {
        return der;
    }
    return padre;
}

size_t calculo_mayor2(void **arr, size_t padre, size_t izq, cmp_func_t cmp) {
    if (cmp(arr[izq], arr[padre]) > 0) {
        return izq;
    }
    return padre;
}

void downheap(void **arr, size_t tam, size_t padre, cmp_func_t cmp) {
    // printf("Downheap de %s\n", (char *)arr[padre]);
    size_t izq = 2 * padre + 1;
    size_t der = 2 * padre + 2;
    if (izq > tam - 1) {
        // printf("no hay hijos\n");
        return;  // si no hay hijos vuelve
    }
    size_t mayor = 0;
    // printf("padre %d izq %d der %d tam %d\n", (int)padre, (int)izq, (int)der, (int)tam);
    if (der > tam - 1) {  //solo hay hijo izq
        // printf("solo hijo izq\n");
        mayor = calculo_mayor2(arr, padre, izq, cmp);
    } else {
        // printf("hay 2 hijos\n");
        mayor = calculo_mayor(arr, padre, izq, der, cmp);
        // printf("mayor de los tres: %s\n", (char*)arr[mayor]);
    }
    if (padre != mayor) {
        swap(arr, padre, mayor);

        // arreglo_void_cadenas_imprimir(arr, tam);
        // printf("\n");
        downheap(arr, tam, mayor, cmp);
    }
}

void *heap_desencolar(heap_t *heap) {
    // printf("Antes de desencolar:\n");
    // heap_mostrar(heap);
    if (heap_esta_vacio(heap)) return NULL;
    bool esta_muy_vacio = (heap->cant - 1 < heap->tam / CAPACIDAD_MINIMA);
    bool esta_al_minimo = (heap->tam <= CAPACIDAD_INICIAL);
    if (esta_muy_vacio && !esta_al_minimo) {
        if (!heap_redimensionar(heap, heap->tam / FACTOR_REDUCCION)) return NULL;
    }

    void *dato_a_devolver = heap->datos[0];
    swap(heap->datos, 0, (int)heap->cant - 1);
    heap->cant--;
    // printf("Antes de downheap:\n");
    // heap_mostrar(heap);
    // printf("Cantidad: %d\n", (int)heap->cant);
    if (heap->cant > 1) {
        downheap(heap->datos, heap->cant, 0, heap->cmp);
    }
    return dato_a_devolver;
}

void heapify(void **arr, size_t n, cmp_func_t cmp) {
    if (n < 2) return;
    int comienzo = (int)(n / 2 - 1);
    for (int i = comienzo; i >= 0; i--) {
        // printf("\nHeapify - Downheap de pos %d\n", (int)i);
        downheap(arr, n, i, cmp);
    }
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = heap_crear_tam(cmp, n);
    for (size_t i = 0; i < n; i++) {
        heap->datos[i] = arreglo[i];
    }
    heap->cant = n;
    heapify(heap->datos, n, cmp);
    return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    if (cant <= 1) return;
    heapify(elementos, cant, cmp);
    // printf("Arreglo heapificado:\n");
    // arreglo_void_cadenas_imprimir(elementos, cant);
    size_t cant_orig = cant;
    for (size_t i = 0; i < cant_orig-1; i++) {
        swap(elementos, 0, cant - 1);
        cant--;
        // printf("HEAPSORT: DOWNHEAP DE %s, CANT: %d\n", (char *)elementos[0], (int)cant);
        downheap(elementos, cant, 0, cmp);
    }
}
