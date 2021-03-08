#include "funciones_tp2.h"
bool existen(abb_t* doctores, char* inicio, char* fin) {
    bool respuesta = true;
    void* dato = NULL;
    if (strcmp(inicio, "") != 0) {
        dato = abb_obtener(doctores, inicio);
        if (!dato) printf(ENOENT_DOCTOR, inicio);
        respuesta = false;
    }
    if (strcmp(fin, "") != 0) {
        dato = abb_obtener(doctores, fin);
        if (!dato) printf(ENOENT_DOCTOR, fin);
        respuesta = false;
    }
    return respuesta;
}

void imprimir_informe(abb_t* doctores, char* inicio, char* fin) {
    //if (!existen(doctores, inicio, fin)) return;
    lista_t* lista_doctores = abb_rango(doctores, inicio, fin);
    if (!lista_doctores) return;
    size_t n_doctores = lista_largo(lista_doctores);
    printf(DOCTORES_SISTEMA, n_doctores);
    doctor_t* imprimir = NULL;
    for (size_t i = 0; i < n_doctores; i++) {
        size_t indice = i + 1;
        imprimir = (doctor_t*)lista_borrar_primero(lista_doctores);
        printf(INFORME_DOCTOR, indice, imprimir->nombre, imprimir->especialidad, imprimir->atendidos);
    }
    lista_destruir(lista_doctores, NULL);
}