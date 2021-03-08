
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_INICIAL  13
#define TAM_REDIM     2


struct heap{
    void** datos;
    size_t tamanio;
    size_t cantidad;
    cmp_func_t cmp;
};

size_t posmax(void *elementos[],size_t pos_padre,size_t pos_izq,size_t pos_der,cmp_func_t cmp)
{
    size_t pos_max = pos_izq;

    if(pos_der != 0)
    {
      if(cmp(elementos[pos_max],elementos[pos_der]) < 0) pos_max = pos_der;
      if(cmp(elementos[pos_max],elementos[pos_padre]) < 0) pos_max = pos_padre;
    }else{
        if(cmp(elementos[pos_max],elementos[pos_padre]) < 0) pos_max = pos_padre;
    }
    return pos_max;
}

void upheap(void *elementos[],size_t pos, cmp_func_t cmp)
{
    if(pos == 0) return;

    int pos_padre = (int)(pos - 1)/2;
    void*dato = NULL;
    if(cmp(elementos[pos],elementos[pos_padre]) > 0)
    {
        dato = elementos[pos_padre];
        elementos[pos_padre] = elementos[pos];
        elementos[pos] = dato;

        upheap(elementos,pos_padre,cmp);
    }
}

void downheap(void *elementos[],size_t pos,size_t cant, cmp_func_t cmp)
{
    size_t pos_izq = 2 * pos + 1, pos_der = 2 * pos + 2, pos_max = pos;
    void* dato = NULL;

    if((pos_izq < cant)&&(pos_der < cant))pos_max = posmax(elementos,pos,pos_izq,pos_der,cmp);

    else if(pos_izq < cant) pos_max = posmax(elementos,pos,pos_izq,0,cmp);

    if(pos_max != pos)
    {
        dato = elementos[pos];
        elementos[pos] = elementos[pos_max];
        elementos[pos_max] = dato;

        downheap(elementos,pos_max,cant,cmp);
    }
}

void heapify(void *elementos[], size_t cant, cmp_func_t cmp)
{
    int i, tope = (int)cant/2;

    for(i = tope - 1; i >= 0; i--) downheap(elementos,i,cant,cmp);

    downheap(elementos,0,cant,cmp);
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{
    size_t i;
    void* dato;

    heapify(elementos,cant,cmp);

    for(i = 0; i < cant; i++)
    {
        dato = elementos[0];
        elementos[0] = elementos[cant - 1 - i];
        elementos[cant - 1 - i] = dato;

        downheap(elementos,0,cant - 1 - i, cmp);
    }
}

heap_t* heap_crear(cmp_func_t cmp){

    heap_t* cola = malloc(sizeof(heap_t));

    if(!cola) return NULL;

    cola->cantidad = 0;
    cola->tamanio = TAM_INICIAL;
    cola->cmp = cmp;
    cola->datos = calloc(TAM_INICIAL,sizeof(void*));

    if(!cola->datos){
        free(cola);
        return NULL;
    }

    return cola;
}

heap_t *heap_crear_arr(void* arreglo[], size_t n, cmp_func_t cmp){

        if(!arreglo || n == 0) return NULL;

        size_t tam = 2*n;
        heap_t * heap = (heap_t*)malloc(sizeof(heap_t));
        if(!heap) return false;
        heap->cantidad = n;
        heap->tamanio = tam;
        heap->cmp = cmp;
        heap->datos= calloc(tam,sizeof(void*));

        if(!heap->datos){

            free(heap);
            return false;
        }

        for(size_t i = 0; i < n; i++) heap->datos[i] = arreglo[i];

        heapify(heap->datos,heap->cantidad,cmp);

        return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){

    if(!heap)return;
    size_t largo = heap->cantidad;

    if(destruir_elemento){
        for(size_t i = 0; i < largo; i++){

            destruir_elemento(heap->datos[i]);
        }
    }

    free(heap->datos);

    free(heap);

}

size_t heap_cantidad(const heap_t *heap){
    if(!heap)return 0;

    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
    if(!heap)return true;

    return (heap->cantidad == 0);
}

bool redimensionar(heap_t* heap, size_t tam_nuevo){

    if(tam_nuevo < TAM_INICIAL) return true;

    void** datos = (void**)realloc(heap->datos, sizeof(void*) * tam_nuevo);

    if(!datos) return false;

    heap->tamanio = tam_nuevo;

    heap->datos = datos;

    return true;
}

bool heap_encolar(heap_t *heap, void *elem){
    if(!heap || !elem)return false;

    if(heap->cantidad == heap->tamanio)if(!redimensionar(heap, heap->tamanio * TAM_REDIM)) return false;

    heap->datos[heap->cantidad]=elem;
    heap->cantidad++;
    upheap(heap->datos,heap->cantidad - 1,heap->cmp);
    return true;

}

void *heap_ver_max(const heap_t *heap){
    if(!heap || heap->cantidad == 0)return NULL;

    return heap->datos[0];

}

void *heap_desencolar(heap_t *heap){

    if(!heap)return NULL;

    if(heap->cantidad == 0) return NULL;

   if(heap->cantidad < heap->tamanio / TAM_REDIM) redimensionar(heap, heap->tamanio/TAM_REDIM);

    void* dato = heap->datos[0];

    heap->datos[0] = heap->datos[heap->cantidad-1];
    heap->cantidad--;

    downheap(heap->datos,0,heap->cantidad,heap->cmp);

    return dato;
}
