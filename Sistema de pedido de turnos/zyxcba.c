#include "funciones_tp2.h"

int main(int argc, char** argv) {
    // si no se corrio el programa con los dos archivos.csv como parametro, tira error
    if (argc < 2) {
        printf(ENOENT_CANT_PARAMS);
        return -1;
    }
    // CREA LAS ESTRUCTURAS Y LAS CARGA
    abb_t* abb_doctores = abb_crear(strcmp, destruir_doctor);
    if (!abb_doctores) return -1;

    hash_t* hash_especialidades = hash_crear(NULL);
    if (!hash_especialidades) return -1;

    hash_t* hash_urgencias = hash_crear(NULL);
    if (!hash_urgencias) return -1;

    hash_t* hash_pacientes = hash_crear(destruir_paciente);
    if (!hash_pacientes) return -1;

    bool carga_ok = procesa_csv_doctores(argv[1], abb_doctores, hash_especialidades, hash_urgencias);
    carga_ok &= procesa_csv_pacientes(argv[2], hash_pacientes);
    if (!carga_ok) return -1;

    // descomentar línea siguiente para correr las pruebas 
    //(para ejecutar: "./pruebas 06_doctores 06_pacientes")
    //pruebas(hash_pacientes, hash_especialidades, hash_urgencias, abb_doctores);
    procesar_entrada(hash_urgencias, hash_especialidades, abb_doctores, hash_pacientes);

    abb_destruir(abb_doctores);
    hash_destruir(hash_especialidades);
    hash_destruir(hash_urgencias);
    hash_destruir(hash_pacientes);
    return 0;
}
