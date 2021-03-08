

#include "infix.h"

#define SUMA                '+'
#define RESTA               '-'
#define MULTIPLICACION      '*'
#define DIVISION            '/'
#define POTENCIA            '^'
#define SEP                 ' '
#define INICIO_PARENTESIS   '('
#define FIN_PARENTESIS      ')'
#define CHAR_TAM_INICIAL     3
#define POS_INICIAL          0
#define POS_SEP              1
#define SALTO_DE_LINEA     '\n'

const char espacio[] = " ";

bool esoperador(char letra)
{
    bool resul = false;
    switch(letra){
        case SUMA:
            resul = true;
        break;
        case RESTA:
            resul = true;
        break;
        case MULTIPLICACION:
            resul = true;
        break;
        case DIVISION:
            resul = true;
        break;
    }

    return resul;
}

void proc(char* formula)
{

    int len = strlen(formula);
    char *copia = calloc(len+1,sizeof(char));
    char *aux = calloc(len+1,sizeof(char));
    char operador[CHAR_TAM_INICIAL];
    operador[POS_INICIAL]=0; operador[POS_SEP]=SEP; operador[POS_SEP + 1]=0;
    int i = 0;
    strpila_t* mipila = strpila_crear();
    while(formula[i]!=0){
        if(esoperador(formula[i])){
            if(operador[POS_INICIAL]!=0){
                if(operador[POS_INICIAL]==MULTIPLICACION || operador[POS_INICIAL]==DIVISION){
                    strcat(copia,operador);
                }else{
                    char *a = calloc(CHAR_TAM_INICIAL,sizeof(char));
                    a[POS_INICIAL]=operador[POS_INICIAL];
                    a[POS_SEP]=SEP;
                    strpila_apilar(mipila,a);
                }
                operador[POS_INICIAL] = 0;            }
            operador[POS_INICIAL] = formula[i];
            i++;
        }else{
            if(formula[i]==INICIO_PARENTESIS){
            int ini = i+1;
                int contador = 1;
                while(contador>0){
                    i++;
                    if(formula[i]==FIN_PARENTESIS)contador--;
                    if(formula[i]==INICIO_PARENTESIS)contador++;
                }
            char c = formula[i];
            formula[i]=0;
            strcpy(aux,&formula[ini]);
            proc(aux);
            formula[i]=c;
            strcat(copia,aux);
            }else{
                if(formula[i]!=FIN_PARENTESIS && formula[i]!=SEP){
                int f = i;
                while(formula[i]!=SEP)i++;
                    formula[i]=0;
                    strcat(copia,&formula[f]);
                    formula[i]=SEP;
                    strcat(copia,espacio);
                }
                i++;
            }
        }
    }
    if(operador[POS_INICIAL]!=0){
        strcat(copia,operador);
    }
    while(!strpila_esta_vacia(mipila)){
        char* a = strpila_desapilar(mipila);
        strcat(copia,a);
        free(a);
    }
    strcpy(formula,copia);
    strpila_destruir(mipila);
    free(aux);
    free(copia);

}
void potencia(char* formula)
{

    int len = strlen(formula);
    if(formula[len-1]==SALTO_DE_LINEA){
        formula[len-1]=0;
        len--;
    }
    char* copia = calloc(len+2,sizeof(char));
    strcpy(copia,formula);
    if(copia[len-1]!=SEP)strcat(copia,espacio);
    proc(copia);
    for(int i=0;i<len;i++){
        if(copia[i]==POTENCIA){
            int j = i;
            while(copia[j+2]!=SEP){
                copia[j]=copia[j+2];
                copia[j+1]=SEP;
                copia[j+2]=SEP;
                j++;
            }
            j++;
            copia[j]=POTENCIA;
            i=j;
        }
    }
    strcpy(formula,copia);
    free(copia);
}

int main(){

    size_t largo_input = 0;
    char* formula = NULL;

    while(getline(&formula, &largo_input, stdin)>-1){
        if(formula[POS_INICIAL] != SALTO_DE_LINEA){

            potencia(formula);

            printf("%s\n",formula);
        }
        if(formula){
            free(formula);
            formula = NULL;
            largo_input = 0;
        }
    }

        if(formula){
            free(formula);
            formula = NULL;
            largo_input = 0;
        }
    return 0;
}
