#include "funciones_tp2.h"
void atender_de_urgencia(lista_t* lista, char* especialidad) {
    paciente_t* paciente = (paciente_t*)lista_borrar_primero(lista);
    printf(PACIENTE_ATENDIDO, paciente->nombre);
}

void atender_paciente_regular(heap_t* pacientes, char* especialidad) {
    paciente_t* paciente = (paciente_t*)heap_desencolar(pacientes);
    printf(PACIENTE_ATENDIDO, paciente->nombre);
}

void impimir_en_espera(char* nombre_especialidad, hash_t* hash_especialidades, hash_t* hash_urgencias) {
    heap_t* heap_especialidad = (heap_t*)hash_obtener(hash_especialidades, nombre_especialidad);
    size_t en_espera = heap_especialidad ? heap_cantidad(heap_especialidad) : 0;
    lista_t* lista_especialidad_urg = (lista_t*)hash_obtener(hash_urgencias, nombre_especialidad);
    en_espera += lista_especialidad_urg ? lista_largo(lista_especialidad_urg) : 0;
    printf(CANT_PACIENTES_ENCOLADOS, en_espera, nombre_especialidad);
}

void atender_siguiente(char* nombre_doctor, abb_t* doctores, hash_t* especialidades, hash_t* urgencias) {
    doctor_t* doctor = (doctor_t*)abb_obtener(doctores, nombre_doctor);
    if (doctor == NULL) {
        printf(ENOENT_DOCTOR, nombre_doctor);
        return;
    }

    lista_t* urgentes = (lista_t*)hash_obtener(urgencias, doctor->especialidad);

    if (urgentes) {
        atender_de_urgencia(urgentes, doctor->especialidad);
        doctor->atendidos++;
        impimir_en_espera(doctor->especialidad, especialidades, urgencias);
        if (lista_esta_vacia(urgentes)) {
            urgentes = (lista_t*)hash_borrar(urgencias, doctor->especialidad);
            lista_destruir(urgentes, NULL);
        }
        return;
    }

    heap_t* paciente = (heap_t*)hash_obtener(especialidades, doctor->especialidad);

    if (paciente) {
        atender_paciente_regular(paciente, doctor->especialidad);
        doctor->atendidos++;
        impimir_en_espera(doctor->especialidad, especialidades, urgencias);
        if (heap_cantidad(paciente) == 0) {
            paciente = (heap_t*)hash_borrar(especialidades, doctor->especialidad);
            heap_destruir(paciente, NULL);
        }
        return;
    }

    printf(SIN_PACIENTES);
}
