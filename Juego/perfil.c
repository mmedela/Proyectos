#include "perfil.h"
#include "batalla.h"



//precondiciones: que el usuario ingrese el valor correspondiente a su signo
int Pedir_Signo () {
    int signo = 0;
    printf("a continuacion, se muestran los diferentes signos con su valor correspondiente:\n ARIES(1).\n");
    printf(" Tauro(2).\n GEMINIS(3).\n CANCER(4).\n LEO(5).\n VIRGO(6).\n LIBRA(7).\n ESCORPIO(8).\n ");
    printf("SAGITARIO(9).\n CAPRICORNIO(10).\n Cuario(11).\n PISCIS(12).\n");
    printf("por favor, ingrese el valor correspondiente a su signo.\n");
    scanf(" %i",&signo);
    if(signo<ARIES || signo>PISCIS ){
        limpiar_pantalla();
        printf("CUIDADO GUERRERO!!!\n Un simple error puede ser la diferencia entre la vida y la muerte, intentemoslo de nuevo, pero prestando mas atencion esta vez.");
        signo = Pedir_Signo();
    }
    return signo;
} //poscondiciones: obtener un valor que corresponda a alguno de los signos zodiacales

char Pedir_Genero(){ // precondicion: que el usuario ingrese su genero favorito

   int  bandera = 0;
   char genero = 0;
        printf ("hay cuatro Generos\n ACCION(A)\n TERROR(T)\n COMEDIA(C)\n DRAMA(D)\n ingresa la letra del Genero que mas te guste.\n");

        while (bandera == 0){
        scanf(" %c", &genero);

            if ( (genero != ACCION) && (genero != COMEDIA) && (genero != DRAMA) && (genero != TERROR) ){
                printf("Como un sabio enano verde dijo una vez:\n Si ganar quieres, Errores evitar debes.\n Intenta practicar con esta pregunta y responde nuevamente.\n");
            }
            else{
                bandera = 1;
            }
        }
    return genero;
} // postcondicion: que el dato ingresado por el usuario se corresponda con alguno de los generos dados

char Asignar_Elemento (int Signo){ //precondiciones: que el signo obtenido del usuario se corresponda con alguno de los elementos
    if ((Signo==ARIES)||(Signo==LEO)||(Signo==SAGITARIO))
        return FUEGO;

    if ((Signo==Tauro)||(Signo==VIRGO)||(Signo==CAPRICORNIO))
        return TIERRA;

    if ((Signo==GEMINIS)||(Signo==LIBRA)||(Signo==ACUARIO))
        return AIRE;

    return AGUA;
}  //poscondiciones: que al signo ungresado se le halla podido asignar algun elemento

int Pedir_Mascotas (){ // precondiciones: que el usuario halla ingresado un numero entero que se corresponda con su numero de mascotas
    int Num_Mascotas = -1;
    printf("Recluta, dieme cuantas mascotas tienes y tal vez pueda ubicarte en unas barracas mas limpias.\n");
    scanf("%i",&Num_Mascotas);
    while ((Num_Mascotas < 0)||(Num_Mascotas > 5)){
        limpiar_pantalla();
        printf("No jueges con migo recula, o me dices ciantas mascotas tienes o te hare limpiar las letrinas del regimiento completo con tu sepillo de dientes.\n");
        scanf(" %i", &Num_Mascotas);

    }
    return Num_Mascotas;
}//posrcondiciones: que se halla obtenido una cantidad positiva menor a 5 de mascotas, para poder asignar el puntaje
int Pedir_Maldades(){ //precondiciones: el usuario debera ingresar la cantidad de maldades que halla realizado en el ultimo mes
    int Num_Maldades = 0;
    printf("La tradicion demanda que me confieces cuantas maldades has hecho en el ultimo mes para que puedas obtener el perdon de Eru.\n");
    scanf("%i",&Num_Maldades);
    while (Num_Maldades<0 || Num_Maldades>99){
        limpiar_pantalla();
        printf("No mientas o la furia de Iluvatar caera sobre ti!!! ");
        printf("Ahora dime la verdad antes de que me enoje y confiesa cuantas maldades has hecho.\n");
        scanf(" %i",&Num_Maldades);
    }
    return Num_Maldades;
}// postcondiciones: que el valor ingresado pertenezca al intervalo [0;99]
void Preguntar_Usario (int* Signo, datos_t* datos_obtenidos_del_usuario, int* Num_Maldades, char* Genero){//precondiciones: que todas las variables pasadas por referencia hallan sido correcgtamente inicializadas en la funcion main
    (*Signo) = Pedir_Signo();
    limpiar_pantalla();
    (*Genero) = Pedir_Genero();
    limpiar_pantalla();
    (*Num_Maldades) = Pedir_Maldades();
    limpiar_pantalla();
    (datos_obtenidos_del_usuario->Puntos_x_Mascota) = Pedir_Mascotas();
    limpiar_pantalla();

}//postcondiciones: que todas las funciones hallan obtenido los datos deseados en el orden correcto y que los hallan validado correctamente

void Puntaje_x_Maldades (int Num_Maldades,datos_t* datos_obtenidos_del_usuario){ //poscondiciones: que la funcion Peguntar_Usuario funcione correctamente y que el compilador trunque el resultado de la division en lugar de redondearlo
    if (Num_Maldades<50)
        datos_obtenidos_del_usuario->Puntos_x_Maldades = ((Num_Maldades)/10) + 1;
    else
        datos_obtenidos_del_usuario->Puntos_x_Maldades = ((Num_Maldades - 50)/10) + 1;

}//posrcondiciones: que la funcion le halla otorgado el valor correcto al usuario en funcion a la cantidad de maldades cometidas

int Asignar_Bando_aux (int Elemento, int Num_Maldades, char Genero){//precondicion: que la funcion Preguntar_Usuario halla obtenido los datos necesarios
    if (((Elemento==AIRE)||(Elemento==FUEGO))&&((Genero==COMEDIA)||(Genero==TERROR))&&(Num_Maldades>=50))
        return ATACA;

    if (((Elemento==TIERRA)||(Elemento==AGUA))&&((Genero==ACCION)||(Genero==DRAMA))&&(Num_Maldades<50))
        return DEFIENDE;

    return 0;
}
int Intensidad_guerrero (int Puntos_x_Mascota, int Puntos_x_Maldades)
{
    return Puntos_x_Mascota + Puntos_x_Maldades;
}

void definir_bando(datos_t* datos_obtenidos_del_usuario) { //precondiciones: que todas las variables necesitadas hallan sido previamente definidas.

    int Signo=0, Num_Maldades=-1, Bando_aux = 0;
    char Genero = 0, Elemento = 0, pausa = 0;
    datos_obtenidos_del_usuario->Puntos_x_Mascota = -1;
    do {
        Preguntar_Usario(&Signo,datos_obtenidos_del_usuario, &Num_Maldades, &Genero);
        Puntaje_x_Maldades (Num_Maldades, datos_obtenidos_del_usuario);
        Elemento=Asignar_Elemento (Signo);
        Bando_aux = Asignar_Bando_aux(Elemento, Num_Maldades, Genero);
        datos_obtenidos_del_usuario->Bando = Bando_aux;
    }while (Bando_aux == 0);

    int intensidad_luchador = Intensidad_guerrero (datos_obtenidos_del_usuario->Puntos_x_Mascota, datos_obtenidos_del_usuario->Puntos_x_Maldades);

    if (Bando_aux == DEFIENDE){
        printf("Debido a tu caracter protector y espiritu defensivo (Nivel %i),",intensidad_luchador);
        printf(" usted tendra la fortuna de luchar codo a codo con grandes guerreros como ");
        printf("Aragon en la gloriosa batalla por venir. /n le deseamos buena suerte y esperamos su victoria.");
    }
    else{
        printf("Debido a tu caracter ofensivo y espiritu guerrero (Nivel %i), ", intensidad_luchador);
        printf("usted tendra la fortuna de luchar bajo el comando del legendario Saruman el blanco y usar el");
        printf(" ariete para derribar esa apestosa muralla que se interpone entre el señor oscuro y sus objetivos.\n");
    }
    printf("oprima cualquier letra para continuar.");

    scanf(" %c",&pausa);
}
void perfil ( char * tipo , int * intensidad )
{

}
