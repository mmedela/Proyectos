#include "strutil.h"
#include "pila.h"


#define SUMA           '+'
#define RESTA          '-'
#define MULTIPLICACION '*'
#define DIVISION       '/'
#define POTENCIA       '^'
#define RAIZ           's'
#define LOGARITMO      'l'
#define TERNA          '?'


#define SALTO_DE_LINEA     '\n'

#define VALOR_MIN_BASE_LOG    2
#define VALOR_MIN_ARGUMENTO   0
#define ARGUMENTO_INVALIDO   -1
#define DIVISION_INVALIDA     0
#define ERROR              "ERROR"
#define EXPONENTE_INVALIDO    0
#define ERROR_DE_LECTURA     -1

#define NUM_ARGUMENTOS_OP_BINARIA  2
#define NUM_ARGUMENTOS_OP_TERNARIA 3
#define NUM_ARGUMENTOS_RAIZ        1

#define SEP ' '

#define POS_INICIAL 0

#define TAM_RESULTADO 20

#define CERO    48    //cero en el codigo ascii
#define NUEVE   57   //nueve en el codigo ascii


long int sumar (long int a, long int b){

    return a + b;
}

long int restar (long int a, long int b){

    return a - b;
}

long int multiplicar (long int a, long int b){

    return a * b;
}

long int dividir (long int arriba, long int abajo){

    return arriba / abajo;
}

long int logaritmo (long int argumento, long int base){


    if (argumento <= VALOR_MIN_ARGUMENTO || base < VALOR_MIN_BASE_LOG) return ARGUMENTO_INVALIDO;

    return log10(argumento)/log10(base);
}

long int raiz (double argumento){
    if (argumento < VALOR_MIN_ARGUMENTO) return ARGUMENTO_INVALIDO;
    return sqrt(argumento);
}

long int elevar (long int base, long int exponente){

    return pow(base, exponente);
}

long int terna (long int a, long int b, long int c){

    return a ? b : c;
}

bool procesar_datos(pila_t* pila, char operacion){

    size_t num_argumentos = pila_largo(pila);
    bool respuesta = true;
    long int resul = 0;

    switch (operacion){

        case SUMA:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) {
                respuesta = false;
            }else {
                resul = sumar(pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case RESTA:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) respuesta = false;
            else {
                resul = restar(pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case MULTIPLICACION:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) respuesta = false;
            else {
                resul = multiplicar(pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case DIVISION:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) respuesta = false;
            else {
                if (pila_ver_tope(pila) == DIVISION_INVALIDA) return false;

                resul = dividir(pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case RAIZ:
            if (num_argumentos < NUM_ARGUMENTOS_RAIZ) respuesta = false;
            else {
                resul = raiz(pila_desapilar(pila));
                if (resul == ARGUMENTO_INVALIDO)return false;
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case POTENCIA:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) respuesta = false;
            else {
                if (pila_ver_tope(pila) < EXPONENTE_INVALIDO) return false;
                resul = elevar(pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case LOGARITMO:
            if (num_argumentos < NUM_ARGUMENTOS_OP_BINARIA) respuesta = false;
            else {
                resul = logaritmo(pila_desapilar(pila), pila_desapilar(pila));
                if (resul == ARGUMENTO_INVALIDO)return false;
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;
        case TERNA:
            if (num_argumentos < NUM_ARGUMENTOS_OP_TERNARIA) respuesta = false;
            else {
                resul = terna(pila_desapilar(pila), pila_desapilar(pila), pila_desapilar(pila));
                respuesta = pila_apilar(pila, resul);
            }
            return respuesta;

            break;

        default: return true;
    }
    return respuesta;
}

bool es_negativo(char** datos, size_t i, size_t j){

    if (datos[i][j] == RESTA)return(datos[i][j+1] >= CERO && datos[i][j+1] <= NUEVE);
    else return false;
}

bool es_numero(char** datos, size_t i){

    bool resul = false;
    int j = 0;

    if (es_negativo(datos, i, j))j++;
    if(datos[i][j] >= CERO && datos[i][j] <= NUEVE){

        while((datos[i][j]) && datos[i][j] != SALTO_DE_LINEA){

            if(datos[i][j] >= CERO && datos[i][j] <= NUEVE) resul =  true;
            else resul = false;
            j++;
            if(!resul) break;
        }
    }
    return resul;
}

bool resultados(char** datos, char* respuesta){

    if(!datos[POS_INICIAL]) return false;
    if(datos[POS_INICIAL + 1] == NULL) return false;

    size_t i = 0, j = 0;

    bool resul = true;

    pila_t* pila = pila_crear();

    if (!pila) return false;

    while(datos[i]){

        if (es_numero(datos, i)){

            bool todo_ok = pila_apilar(pila, atoi(datos[i]));
            if(!todo_ok) {
                pila_destruir(pila);
                return false;
            }
        }else{
            if(!procesar_datos(pila, datos[i][j])){
                resul = false;
                break;
                }
            }

            i++;
        }
    if (pila_largo(pila) > 1 || pila_largo(pila)==0){

        pila_destruir(pila);
        return false;
    }


    sprintf(respuesta,"%li", pila_desapilar(pila));

    pila_destruir(pila);


    return resul;
}

void dc(){

    size_t largo_input = 0;
    char* formula = NULL;

    while(getline(&formula, &largo_input, stdin) > ERROR_DE_LECTURA){
        if(formula[POS_INICIAL] != SALTO_DE_LINEA){
            bool todo_ok = false;
            char* resultado = malloc(sizeof(char)*TAM_RESULTADO);
            char** datos = split(formula, SEP);
            free(formula);
            formula = NULL;

            if(datos){
                todo_ok = resultados(datos, resultado);
                free_strv(datos);

                if (todo_ok) printf ("%s\n", resultado);
                else printf("%s\n", ERROR);
            }else{
                printf("%s\n", ERROR);
            }
            free(resultado);



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
}
///////////////////////////////////////////////////////////
/*
int main (){

    dc();

    return 0;
}
*/


