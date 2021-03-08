
//#include "strutil.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define TAM_INICIAL_SPLIT  10
#define POS_INICIAL         0
#define MIN_NUM_SEGMENTOS   2

char *substr(const char *str, size_t n){

    char* resul = (char*)calloc(n+1,sizeof(char));

    if (!resul) return NULL;

    size_t largo = strlen(str);

    if (largo > n) largo = n;

    for (size_t i = 0; i < largo; i++){

        resul[i] = str[i];
    }
    return resul;
}

char** el_sep_es_nulo(const char* str){

    char** devolver = (char**)calloc(2, sizeof(char*));
    devolver[POS_INICIAL] = (char*)calloc(strlen(str) + 1, sizeof(char));
    strcpy(devolver[POS_INICIAL], str);
    return devolver;
}

char **split(const char *str, char sep){


    if(!str)return NULL;

    if (sep == 0){

        return el_sep_es_nulo(str);
    }
    char** resul;

    size_t largo = strlen(str), largo_segmento_auxiliar=0, largo_segmento=0, num_segmentos=MIN_NUM_SEGMENTOS, pos=0, x=0;

    for (size_t i = 0; i < largo; i++){

        if (largo_segmento < largo_segmento_auxiliar){

            largo_segmento = largo_segmento_auxiliar;
        }
        largo_segmento_auxiliar++;
        if (str[i] == sep){

            largo_segmento_auxiliar = 0;
            num_segmentos++;
        }
    }

    largo_segmento+=2;

    resul = (char**)malloc(sizeof(char*) * num_segmentos);
    resul[x] = (char*)malloc( sizeof(char) * largo_segmento);
    for (size_t i = 0; i< largo; i++){
        if(str[i]==sep){
            resul[x][pos]=0;
            x++;
            pos = 0;
            resul[x] = (char*)malloc( sizeof(char) * largo_segmento);
        }else{
            resul[x][pos]=str[i];
            pos++;
        }

    }
    resul[x][pos]=0;
    x++;
    resul[x] = NULL;

    return resul;
}

char *join(char **strv, char sep){

    size_t i = 0, j = 0, tam_resul = 0, pos = 0;
    char* resul;
    if (!strv) return NULL;
   while(strv[i]){

        j = 0;
        while (strv[i][j] != 0){

            tam_resul++;
            j++;
        }
        tam_resul++;
        i++;
   }
    tam_resul++;
   resul = (char*)calloc(tam_resul, sizeof(char));
   if(!resul) return NULL;
   i = 0;
   while(strv[i]){

        j = 0;
        while (strv[i][j] != 0){

            resul[pos] = strv[i][j];
            pos++;
            j++;
        }
        i++;
        if (strv[i]){
            if(sep!=0) {
                resul[pos] = sep;
                pos++;
            }
        }
   }

   return resul;
}

void free_strv(char *strv[]){

    size_t pos = 0;
    while(strv[pos] != 0){

        free(strv[pos]);
        pos++;
    }
    free(strv[pos]);
    free(strv);
}

