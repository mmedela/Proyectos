#include "funciones_tp2.h"

int antiguedad(const void* dato1, const void* dato2) {
    paciente_t* paciente1 = (paciente_t*)dato1;
    paciente_t* paciente2 = (paciente_t*)dato2;
    return strcmp(paciente2->anio, paciente1->anio);
}



bool entradas_validas(char* nombre_especialidad, hash_t* hash_especialidades, char* urgencia) {
    // valida especialidad
    if (!hash_pertenece(hash_especialidades, nombre_especialidad)) {
        printf(ENOENT_ESPECIALIDAD, nombre_especialidad);
        return false;
    }
    // valida urgencia
    if (strcmp(urgencia, "REGULAR") && strcmp(urgencia, "URGENTE")) {
        printf(ENOENT_URGENCIA, urgencia);
        return false;
    }
    return true;
}

void pedir_turno(char* nombre_paciente, char* nombre_especialidad, char* urgencia, hash_t* hash_especialidades, hash_t* hash_urgencias, hash_t* hash_pacientes) {
    // printf("\n%s pide turno para %s con urgencia %s\n", nombre_paciente, nombre_especialidad, urgencia);
    // valida paciente
    paciente_t* paciente = (paciente_t*)hash_obtener(hash_pacientes, nombre_paciente);
    if (!paciente) {
        printf(ENOENT_PACIENTE, nombre_paciente);
        return;
    }

    // valida el resto
    if (!entradas_validas(nombre_especialidad, hash_especialidades, urgencia)) return;

    // calcula cuantos en espera (suma de regulares y urgentes)
    heap_t* heap_especialidad = (heap_t*)hash_obtener(hash_especialidades, nombre_especialidad);
    size_t en_espera = heap_especialidad ? heap_cantidad(heap_especialidad) : 0;
    lista_t* lista_especialidad_urg = (lista_t*)hash_obtener(hash_urgencias, nombre_especialidad);
    en_espera += lista_especialidad_urg ? lista_largo(lista_especialidad_urg) : 0;

    // si es REGULAR encola en heap
    if (!strcmp(urgencia, "REGULAR")) {
        if (!heap_especialidad) {  // si no habia pacientes en espera crea el heap y lo guarda en el hash
            heap_especialidad = heap_crear(antiguedad);
            hash_guardar(hash_especialidades, nombre_especialidad, (void*)heap_especialidad);
        }
        heap_encolar(heap_especialidad, (void*)paciente);
        // si es URGENCIA encola en lista,
    } else {
        //  si no habia pacientes en espera, crea la lista y la guarda en en el hash
        if (!lista_especialidad_urg) {
            lista_especialidad_urg = lista_crear();
            hash_guardar(hash_urgencias, nombre_especialidad, (void*)lista_especialidad_urg);
        }
        lista_insertar_ultimo(lista_especialidad_urg, (void*)paciente);
    }
    printf(PACIENTE_ENCOLADO, paciente->nombre);
    printf(CANT_PACIENTES_ENCOLADOS, ++en_espera, nombre_especialidad);
}
