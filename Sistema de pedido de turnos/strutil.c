#include "strutil.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n) {
    //n = (n <= strlen(str)) ? n : strlen(str);
    if (n >= strlen(str)) return strdup(str);
    char *subcadena = malloc(sizeof(char) * (n + 1));
    if (!subcadena) return NULL;
    memset(subcadena, 0, n + 1);
    strncpy(subcadena, str, n);
    return subcadena;
}
char **split(const char *str, char sep) {
    size_t largo_str = strlen(str);
    char *final_str = (char *)str + largo_str;
    size_t tam_arreglo = sizeof(char *) * (largo_str + 2);
    char **arreglo = malloc(tam_arreglo);
    if (!arreglo) return NULL;
    char *corte;
    size_t largo, pos = 0;
    if (!sep) {
        corte = NULL;
    } else {
        corte = strchr(str, sep);
    }
    char *subcadena;
    while (corte) {
        largo = (size_t)(corte - str);
        subcadena = substr(str, largo);  //substr hace un malloc
        arreglo[pos] = subcadena;
        str = str + largo + 1;
        corte = strchr(str, sep);
        pos++;
    }
    //arreglo[pos] = (char *)str;
    arreglo[pos] = substr(str, (size_t)(final_str - str));
    arreglo[pos + 1] = NULL;
    //free(subcadena);
    return arreglo;
}

size_t tam_total(char **strv) {
    size_t i = 0, tam = 0;
    while (strv[i]) {
        tam += strlen(strv[i]) + 1;
        i++;
    }
    return tam;
}

char *join(char **strv, char sep) {
    size_t tam_cadena = sizeof(char) * (tam_total(strv) + 1);
    //size_t tam_cadena = sizeof(char) * (sizeof(strv) + 1);
    char *cadena = malloc(tam_cadena);
    if (!cadena) return NULL;
    int elem = 0;
    int car;
    size_t total_caracteres = 0;
    cadena[0] = '\0';  // por si el arreglo esta vacio
    while (strv[elem]) {
        car = 0;
        while (strv[elem][car] != '\0') {
            cadena[total_caracteres]= strv[elem][car];
            car++;
            total_caracteres++;
        }
        if (strv[elem + 1] && sep!='\0' ) {
                cadena[total_caracteres] = sep;
                total_caracteres++;
        }
        elem++;
    }
    cadena[total_caracteres] = '\0';
    return cadena;
}

void free_strv(char **strv) {
    int elem = 0;
    while (strv[elem]) {
        free(strv[elem]);
        elem++;
    }
    free(strv);
}

void mostrar_arreglo(char **arr) {
    printf("\nArreglo:\n");
    int i = 0;
    while (arr[i]) {
        printf("arr[%d]: \"%s\"\n", i, arr[i]);
        i++;
    }
}