#include "funciones_tp2.h"



bool ingresar_linea(char* linea, FILE* archivo) {
    fflush(stdout);
    char* pos;
    if (!fgets(linea, LARGO_LINEA, archivo)) return false;
    //borra el \n
    pos = strchr(linea, '\n');
    if (pos != NULL) {
        *pos = '\0';
    }
    return true;
}

void destruir_doctor(void* dato) {
    doctor_t* doctor = (doctor_t*)dato;
    free(doctor->nombre);
    free(doctor->especialidad);
    free(doctor);
}

void destruir_paciente(void* dato) {
    paciente_t* paciente = (paciente_t*)dato;
    free(paciente->nombre);
    free(paciente->anio);
    free(paciente);
}

void destruir_especialidad(void* dato) {
}


bool guarda_doctor(char** campos, abb_t* abb_doctores) {
    doctor_t* doctor = malloc(sizeof(doctor_t));
    doctor->nombre = strdup(campos[0]);
    doctor->especialidad = strdup(campos[1]);
    doctor->atendidos = 0;
    return abb_guardar(abb_doctores, doctor->nombre, (void*)doctor);
}

bool procesa_csv_doctores(char* ruta_archivo, abb_t* abb_doctores, hash_t* hash_especialidades, hash_t* hash_urgencias) {
    FILE* archivo = fopen(ruta_archivo, "r");
    if (!archivo) {
        printf(ENOENT_ARCHIVO, ruta_archivo);
        return false;
    }
    char linea[LARGO_LINEA];
    bool carga_ok = true;
    while (true) {
        if (!ingresar_linea(linea, archivo) || linea[0] == '\0') break;
        char** campos = split(linea, ',');
        carga_ok &= guarda_doctor(campos, abb_doctores);
        carga_ok &= hash_guardar(hash_especialidades, campos[1], NULL);
        carga_ok &= hash_guardar(hash_urgencias, campos[1], NULL);
        free_strv(campos);
    }
    fclose(archivo);
    return carga_ok;
}

bool paciente_crear(char** campos, hash_t* hash_pacientes) {
    paciente_t* paciente = malloc(sizeof(paciente_t));
    paciente->nombre = strdup(campos[0]);
    if (!atoi(campos[1])) {
        printf(ENOENT_ANIO, campos[0]);
        return false;
    }
    paciente->anio = strdup(campos[1]);
    return hash_guardar(hash_pacientes, paciente->nombre, (void*)paciente);
}

bool procesa_csv_pacientes(char* ruta_archivo, hash_t* hash_pacientes) {
    FILE* archivo = fopen(ruta_archivo, "r");
    if (!archivo) {
        printf(ENOENT_ARCHIVO, ruta_archivo);
        return false;
    }
    char linea[LARGO_LINEA];
    bool ok = true;
    while (ok) {
        if (!ingresar_linea(linea, archivo) || linea[0] == '\0') break;
        char** campos = split(linea, ',');
        ok &= paciente_crear(campos, hash_pacientes);
        free_strv(campos);
    }

    fclose(archivo);
    return ok;
}
