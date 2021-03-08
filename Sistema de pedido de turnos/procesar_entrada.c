#include "funciones_tp2.h"
#define CODIGO_TURNO 1
#define CODIGO_ATENDER 2
#define CODIGO_INFORME 3
#define SON_IGUALES 0
#define CODIGO_ERRONEO -1
#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

/// IMPRIMO EL MENSAJE DE ERROR CORRESPONDIENTE CON LA CONSTANTE DE MENSAJES.H.

void doctor_no_existe(char* nombre) {
    printf(ENOENT_DOCTOR, nombre);
}

int validar_comando(char* comando) {
    ///COMPARO EL COMANDO RECIBIDO POR CONSOLA CON LOS VALIDOS Y DEVUELVO EL CODIGO CORRESPONDIENTE.
    int codigo = CODIGO_ERRONEO;
    if (strcmp(comando, COMANDO_PEDIR_TURNO) == SON_IGUALES) codigo = CODIGO_TURNO;
    if (strcmp(comando, COMANDO_ATENDER) == SON_IGUALES) codigo = CODIGO_ATENDER;
    if (strcmp(comando, COMANDO_INFORME) == SON_IGUALES) codigo = CODIGO_INFORME;
    return codigo;
}

bool comprobar_formato(char** parametros, int codigo_comando) {
    int i = 0;
    while (parametros[i]) {
        i++;
    }
    int cant_parametros = i;
    bool formato_correcto = true;

    switch (codigo_comando) {
        case CODIGO_TURNO:

            if (cant_parametros != 3) formato_correcto = false;
            break;
        case CODIGO_ATENDER:

            if (cant_parametros != 1) formato_correcto = false;
            break;
        case CODIGO_INFORME:

            if (cant_parametros != 2) formato_correcto = false;
            break;
    }
    return formato_correcto;
}

void procesar_comando(char* comando, char** parametros, hash_t* urgencias, hash_t* especialidades, abb_t* doctores, hash_t* pacientes) {
    int codigo_comando = -1;
    codigo_comando = validar_comando(comando);
    switch (codigo_comando) {
        case CODIGO_TURNO:
            if (comprobar_formato(parametros, codigo_comando)) {
                pedir_turno(parametros[0], parametros[1], parametros[2], especialidades, urgencias, pacientes);
            }
            else
                printf(ENOENT_PARAMS, comando);
            break;

        case CODIGO_ATENDER:
            if (comprobar_formato(parametros, codigo_comando))
                atender_siguiente(parametros[0], doctores, especialidades, urgencias);
            else
                printf(ENOENT_PARAMS, comando);
            break;

        case CODIGO_INFORME:
            if (comprobar_formato(parametros, codigo_comando)){
            imprimir_informe(doctores, parametros[0], parametros[1]);
            }
            else
                printf(ENOENT_PARAMS, comando);
            break;

        default:
            printf(ENOENT_CMD, comando);
    }
}

bool ingresa_linea(char* linea) {
    fflush(stdout);
    char* pos;
    if (!fgets(linea, LARGO_LINEA, stdin)) return false;
    //borra el \n
    pos = strchr(linea, '\n');
    if (pos != NULL) {
        *pos = '\0';
    }
    return true;
}

void procesar_entrada(hash_t* urgencias, hash_t* especialidades, abb_t* doctores, hash_t* pacientes) {
    char linea[LARGO_LINEA];
    while (true) {
        if (!ingresa_linea(linea) || linea[0] == '\0') break;
        char** campos = split(linea, ':');
        if (campos[1] == NULL) {
            printf(ENOENT_FORMATO, linea);
            free_strv(campos);
            continue;
        }
        char** parametros = split(campos[1], ',');
        procesar_comando(campos[0], parametros, urgencias, especialidades, doctores, pacientes);
        free_strv(parametros);
        free_strv(campos);
    }
}
