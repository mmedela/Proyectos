
#ifndef FUNCIONES_TP2_H
#define FUNCIONES_TP2_H
#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "lista.h"
#include "mensajes.h"
#include "strutil.h"

#define LARGO_LINEA 200
#define TAM_CAMPOS 100

typedef struct doctor {
    char* nombre;
    char* especialidad;
    size_t atendidos;
} doctor_t;

typedef struct paciente {
    char* nombre;
    char* anio;
} paciente_t;

void destruir_doctor(void* dato);
void destruir_paciente(void* dato);

bool procesa_csv_pacientes(char* ruta_archivo, hash_t* hash_pacientes);
bool procesa_csv_doctores(char* ruta_archivo, abb_t* abb_doctores, hash_t* hash_especialidades, hash_t* hash_urgencias);
void procesar_entrada(hash_t* urgencias, hash_t* especialidades, abb_t* doctores, hash_t* pacientes);
void pedir_turno(char* nombre_paciente, char* nombre_especialidad, char* urgencia, hash_t* hash_especialidades, hash_t* hash_urgencias, hash_t* hash_pacientes);
void atender_siguiente(char* nombre_doctor, abb_t* doctores, hash_t* especialidades, hash_t* urgencias);
void imprimir_informe(abb_t* doctores, char* inicio, char* fin);



//void pruebas(hash_t* hash_pacientes, hash_t* hash_especialidades, hash_t* hash_urgencias, abb_t* abb_imprimir_doctores);


#endif