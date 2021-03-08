#ifndef PERFIL_H_INCLUDED
#define PERFIL_H_INCLUDED

#include "batalla.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ACCION  'A'
#define TERROR  'T'
#define COMEDIA  'C'
#define DRAMA  'D'

#define ARIES  1
#define Tauro  2
#define GEMINIS  3
#define CANCER  4
#define LEO  5
#define VIRGO  6
#define LIBRA  7
#define ESCORPIO  8
#define SAGITARIO  9
#define CAPRICORNIO  10
#define ACUARIO  11
#define PISCIS  12

#define ATACA 'A'
#define DEFIENDE 'D'

#define FUEGO 'F'
#define AIRE 'V'
#define TIERRA 'T'
#define AGUA 'A'

int Pedir_Signo ();
void perfil ( char * tipo , int * intensidad );
char Pedir_Genero();
char Asignar_Elemento (int Signo);
int Pedir_Mascotas ();
int Pedir_Maldades();
void Preguntar_Usario (int* Signo, datos_t* datos_obtenidos_del_usuario, int* Num_Maldades, char* Genero);
void Puntaje_x_Maldades (int Num_Maldades, datos_t* datos_obtenidos_del_usuario);
int Asignar_Bando (int Elemento, int Num_Maldades, char Genero);
void definir_bando(datos_t* datos_obtenidos_del_usuario);
int Intensidad_guerrero (int Puntos_x_Mascota, int Puntos_x_Maldades);


#endif // PERFIL_H_INCLUDED
