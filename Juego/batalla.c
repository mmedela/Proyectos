#include "batalla.h"
#include "perfil.h"


//int i = 0;
void limpiar_pantalla()
{
    system("cls");
}

void juega_hombre(juego_t* juego, int i){

    int x = 0, y = 0, j = 0;
    bool puedo_moverme = true, atacar = false;

    x = juego->rohan[i].columna;
    y = juego->rohan[i].fila;

    for (j = 0; j < juego->cantidad_isengard; j++){
        atacar = false;
        if((juego->isengard[j].columna==x+1)||(juego->isengard[j].columna==x-1)){

            if((juego->isengard[j].columna==y+1)||(juego->isengard[j].columna==y-1)){
                atacar = true;
            }
        }
        if (atacar){
            puedo_moverme = false;
            juego->isengard[j].vida -= juego->rohan[i].ataque;
            if (juego->isengard[j].vida == 0){
                juego->isengard[j].codigo = 0;
            }
        }
    }

    if (puedo_moverme){
        mover_personaje(juego, i);
    }
    if(juego->rohan[i].fila == 0){
        juego->rohan[i].codigo = 0;
        juego->llegadas_rohan++;
        juego->terreno[y][x] = ' ';
    }
    imprimir_pantalla(juego);
}



void juega_orco(juego_t* juego, int i){
    int x = 0, y = 0, j = 0;
    bool puedo_moverme = true, atacar = false;



            x = juego->isengard[i].columna;
            y = juego->isengard[i].fila;

            for (j = 0; j < juego->cantidad_rohan; j++){
                atacar=false;

                if((juego->rohan[j].columna==x+1)||(juego->rohan[j].columna==x-1)){

                    if((juego->rohan[j].columna==y+1)||(juego->rohan[j].columna==y-1)){
                        atacar = true;
                    }
                }
                if (atacar){
                    puedo_moverme = false;
                    juego->rohan[j].vida -= juego->isengard[i].ataque;
                    if (juego->rohan[j].vida == 0){
                        juego->rohan[j].codigo = 1;
                    }
                }

            }

            if (puedo_moverme){
                mover_personaje(juego, i);
            }
            if(juego->isengard[i].fila == 9){
                juego->isengard[i].codigo = 0;
                juego->terreno[y][x] = ' ';
                juego->llegadas_isengard++;
            }



}

int determinar_distancia(int personaje_rohan, int personaje_isengard, juego_t* juego){

    int coordenada_1 = 0, coordenada_2 = 0;
    coordenada_1 = juego->rohan[personaje_rohan].fila - juego->isengard[personaje_isengard].fila;
    coordenada_2 = juego->rohan[personaje_rohan].columna - juego->isengard[personaje_isengard].columna;
    return (abs(coordenada_1) + abs(coordenada_2));
}

void jugar_ranged(juego_t* juego, int i, char bando){
    int j = 0, distancia = 0;

    if(bando == DEFIENDE){
        for (j=0; j<MAX_PERSONAJES; j++){
            if (juego->isengard[j].codigo == 0)
                break;
            distancia = determinar_distancia(i,j,juego);
            if (distancia <= RANGO_RANGED_MAX){
                juego->isengard[j].vida -= juego->rohan[i].ataque;
            }
        }
    }

    if(bando == ATACA){
        for (j=0; j<MAX_PERSONAJES; j++){
            if (juego->rohan[j].codigo == 0)
                break;
            distancia = determinar_distancia(j,i,juego);
            if ((distancia <= RANGO_RANGED_MAX) && (juego->isengard[i].codigo == URUK_HAI)){
                juego->rohan[j].vida -= juego->isengard[i].ataque;
            }
        }
    }

}

void realizar_turno(juego_t* juego){

    int i=0;
    while((juego->llegadas_isengard != CANTIDAD_LLEGADAS)&&(juego->llegadas_rohan != CANTIDAD_LLEGADAS)){
        imprimir_pantalla(juego);
        juego->turno = TURNO_ROHAN;
        ejecutar_comandos(juego);
        juego->turno = TURNO_ISENGARD;
        ejecutar_comandos(juego);
        juego->turno = TURNO_ROHAN;
        for ( i = 0; i < juego->cantidad_rohan; i++){
            if (juego->rohan[i].codigo == ELFO){
                jugar(juego, DEFIENDE, i);
            }
        }
        juego->turno = TURNO_ISENGARD;
        for ( i = 0; i < juego->cantidad_isengard; i++){
            if (juego->isengard[i].codigo == URUK_HAI){
                jugar(juego, ATACA, i);
            }
        }
        juego->turno = TURNO_ROHAN;
        for ( i = 0; i < juego->cantidad_rohan; i++){
            if (juego->rohan[i].codigo == HUMANO){
                jugar(juego, DEFIENDE, i);
            }
        }
        juego->turno = TURNO_ISENGARD;
        for ( i = 0; i < juego->cantidad_isengard; i++){
            if (juego->isengard[i].codigo == ORCO){
                jugar(juego, ATACA, i);
            }
        }

        juego->energia_isengard++;
        juego->energia_rohan++;
    }

}

void ejecutar_comandos(juego_t* juego){
    char comando = 0;

    scanf(" %c",&comando);
    if(juego->turno==TURNO_ROHAN){
        if ((comando == 'h') || (comando == HUMANO))
            crear_humano(juego);
        else if ((comando == 'e') || (comando == ELFO))
            crear_elfo(juego);
        else
            printf("comando equivocado.\n Por favor ingrese el comando nuevamente...");
    }else{
        if ((comando == 'o') || (comando == ORCO))
            crear_orco(juego);
        else if ((comando == 'u') || (comando == URUK_HAI))
            crear_uruk(juego);
        else
            printf("comando equivocado.\n Por favor ingrese el comando nuevamente...");
    }

    imprimir_pantalla(juego);
}

void crear_humano(juego_t* juego){
    int X = 0;
    int Y = 0;
    int i = 0;
    char letra = HUMANO;
    buscar_libre(letra,&X, &Y);
    while (juego->terreno[Y][X] != ' '){
            printf("la posicion ingresada esta ocupada, intente de nuevo.\n");
            buscar_libre(letra,&X, &Y);
        }
    for( i=0;i<MAX_PERSONAJES;i++){
        if(juego->rohan[i].codigo==0){

            juego->rohan[i].codigo = HUMANO;
            juego->cantidad_rohan++;
            juego->rohan[i].columna = X;
            juego->rohan[i].fila = Y;
            juego->rohan[i].costo = COSTO_MELE;
            juego->rohan[i].rango = MELE;
            juego->rohan[i].bando = DEFIENDE;
            juego->rohan[i].ataque= BASIC_ATTACK_MELE + juego->plus_rohan;
            juego->rohan[i].vida= vida_personajes(juego, i);
            posicionar_personaje(juego, juego->rohan[i]);
            break;
        }

    }

}
void crear_elfo(juego_t* juego){
    int X = 0;
    int Y = 0, i = 0;
    char letra = ELFO;
    buscar_libre(letra,&X, &Y);
    while (juego->terreno[Y][X] != ' '){
            if (juego->terreno[Y][X] != ' '){
                printf("Esa posicion ya esta ocupada, intenta de nuevo");
            }else{
                printf("Esa área está restringida para esta especie");
            }
            buscar_libre(letra,&X, &Y);
        }
    for( i=0;i<MAX_PERSONAJES;i++){
        if(juego->rohan[i].codigo==0){

            juego->rohan[i].codigo = ELFO;
            juego->cantidad_rohan++;
            juego->rohan[i].columna = X;
            juego->rohan[i].fila = Y;
            juego->rohan[i].costo = COSTO_RANGED;
            juego->rohan[i].rango = RANGED;
            juego->rohan[i].bando = DEFIENDE;
            juego->rohan[i].ataque= BASIC_ATTACK_RANGED + juego->plus_rohan;
            juego->rohan[i].vida= vida_personajes(juego, i);
            posicionar_personaje(juego, juego->rohan[i]);
            break;
        }

    }


}
void crear_orco(juego_t* juego){
    int X = 0;
    int Y = 0, i = 0;
    char letra = ORCO;
    buscar_libre(letra,&X, &Y);
    while (juego->terreno[Y][X] != ' '){
            buscar_libre(letra,&X, &Y);
        }
    for( i=0;i<MAX_PERSONAJES;i++){
        if(juego->isengard[i].codigo==0){

            juego->isengard[i].codigo = ORCO;
            juego->cantidad_isengard++;
            juego->isengard[i].columna = X;
            juego->isengard[i].fila = Y;
            juego->isengard[i].costo = COSTO_MELE;
            juego->isengard[i].rango = MELE;
            juego->isengard[i].ataque= BASIC_ATTACK_MELE + juego->plus_isengard;
            juego->isengard[i].vida= vida_personajes(juego, i);
            posicionar_personaje(juego, juego->isengard[i]);
            break;
        }

    }

}
void crear_uruk(juego_t* juego){
    int X = 0;
    int Y = 0, i = 0;
    char letra = URUK_HAI;
    buscar_libre(letra,&X, &Y);
    while (juego->terreno[Y][X] != ' '){
            if (juego->terreno[Y][X] != ' '){
                printf("Esa posicion ya esta ocupada, intenta de nuevo");
            }else{
                printf("Esa área está restringida para esta especie");
            }
            buscar_libre(letra,&X, &Y);
        }
    for( i=0;i<MAX_PERSONAJES;i++){
        if(juego->isengard[i].codigo==0){

            juego->isengard[i].codigo = URUK_HAI;
            juego->cantidad_isengard++;
            juego->isengard[i].columna = X;
            juego->isengard[i].fila = Y;
            juego->isengard[i].costo = COSTO_RANGED;
            juego->isengard[i].rango = RANGED;
            juego->isengard[i].ataque= BASIC_ATTACK_RANGED + juego->plus_isengard;
            juego->isengard[i].vida= vida_personajes(juego, i);
            posicionar_personaje(juego, juego->isengard[i]);
            break;
        }

    }

}
void buscar_libre(char letra,int* ncol, int* nrow){
int col=0, row=0;

    while(col<1 || col>10){
        printf("Ingrese la columna de 1 a 10...\n");
        scanf("%i",&col);

    }
    if (letra == HUMANO){
        row = 10;
    }
    if (letra == ORCO){
        row = 1;
    }

    if (letra == URUK_HAI){

        while(row<1 || row>5){
        printf("Ingrese la fila de 1 a 5...\n");
        scanf("%i",&row);
        }
    }
    if (letra == ELFO){

        while(row<1 || row>5){
        printf("Ingrese la fila de 1 a 5...\n");
        scanf("%i",&row);
        }
        row =11 - row;
    }

    *ncol=col-1;
    *nrow=row-1;
}
void mover_personaje(juego_t* juego, int i)
{
    int row = 0;
    int col = 0;

    if(juego->turno==TURNO_ROHAN){

        row = juego->rohan[i].fila;
        col = juego->rohan[i].columna;
        juego->terreno[row][col]=' ';
        juego->rohan[i].fila++;
        row++;
        if (juego->terreno[row][col] == ELFO){
            juego->terreno[row][col]= AMBOS;
        }else{
            juego->terreno[row][col]=juego->rohan[i].codigo;
        }

    }else if(juego->turno==TURNO_ISENGARD){

        row = juego->isengard[i].fila;
        col = juego->isengard[i].columna;
        juego->terreno[row][col]=' ';
        juego->isengard[i].fila++;
        row++;
        if (juego->terreno[row][col] == URUK_HAI)
            juego->terreno[row][col]= AMBOS;
        else
            juego->terreno[row][col]=juego->isengard[i].codigo;
        }
}

void definir_modo(juego_t* juego){
    printf(" Ingrese 1 si desea jugar solo.\n Ingrese 2 si desea jugar junto a otro jugador.\n");
    scanf("%i", &juego->modo);
    limpiar_pantalla();
}

void definir_plus (datos_t* datos_obtenidos_del_usuario, juego_t* juego){
    if (datos_obtenidos_del_usuario->Bando == DEFIENDE){
        juego->plus_rohan = (Intensidad_guerrero(datos_obtenidos_del_usuario->Puntos_x_Mascota, datos_obtenidos_del_usuario->Puntos_x_Maldades)) * (aleatorio (5, 0));
        juego->plus_isengard = (10 - Intensidad_guerrero(datos_obtenidos_del_usuario->Puntos_x_Mascota, datos_obtenidos_del_usuario->Puntos_x_Maldades)) * (aleatorio (5, 0));
    }
    else{

        juego->plus_isengard = (Intensidad_guerrero(datos_obtenidos_del_usuario->Puntos_x_Mascota, datos_obtenidos_del_usuario->Puntos_x_Maldades)) * (aleatorio (5, 0));
        juego->plus_rohan = (10 - Intensidad_guerrero(datos_obtenidos_del_usuario->Puntos_x_Mascota, datos_obtenidos_del_usuario->Puntos_x_Maldades)) * (aleatorio (5, 0));

    }

}


int vida_personajes (juego_t* juego, int i)
{
    if ((juego->rohan[i].rango == RANGED)&&(juego->rohan[i].bando == DEFIENDE)){
        return VIDA_RANGED_MAXIMA - juego->plus_rohan;
    }
    if ((juego->isengard[i].rango == RANGED)&&(juego->isengard[i].bando == ATACA)){
        return VIDA_RANGED_MAXIMA - juego->plus_isengard;
    }
    if ((juego->rohan[i].rango == MELE)&&(juego->rohan[i].bando == DEFIENDE)){
        return VIDA_MELE_MAXIMA - juego->plus_rohan;
    }
    if ((juego->isengard[i].rango == MELE)&&(juego->isengard[i].bando == ATACA)){
        return VIDA_MELE_MAXIMA - juego->plus_isengard;
    }
    return 0;
}
void imprimir_pantalla(juego_t* juego)
{
    limpiar_pantalla();
    char linea[]="-----------------------------------------";
    printf("\n");
    int col=0,row=0;

    printf("\n*****************Isengard****************\n");
    printf(linea);
    printf("\n");
    for(row=0;row<MAX_TERRENO_FIL;row++){
        for(col=0;col<MAX_TERRENO_COL;col++){
            printf(" | ");
            printf("%c",juego->terreno[row][col]);

        }
        printf(" |  ");

        if(row==0){
            printf("1   ");

        }
        if(row==1){
            printf("2   ENERGIA ACUMULADA: %i",juego->energia_isengard);

        }

        if(row==2){
            printf("3   ORCOS que pasaron al otro bando = ");
            printf("%i",juego->llegadas_isengard);
        }
        if(row==3)printf("4   .....................................");

        if(row==4)printf("5   *************************************");
        if(row==5)printf("5   *************************************");

        if(row==6){
            printf("4   ");

        }
        if(row==7){
            printf("3   ");
            printf("HUMANOS que pasaron al otro bando = ");
            printf("%i",juego->llegadas_rohan);
        }
        if(row==8)printf("2   ENERGIA ACUMULADA: %i", juego->energia_rohan);
        if(row==9)printf("1   .....................................");

        printf("\n");
        printf(linea);
        printf("\n");
        if(row==9){

            printf("   1   2   3   4   5   6   7   8   9  10\n");
            printf("*******************Rohan******************\n");
        }



    }
printf("\n");

char jugador[2][80]={"Le toca jugar a Rohan\n\n\0","Le toca jugar a Isengard\n\n\0"};

printf(jugador[juego->turno]);


    printf("instrucciones de juego...\n\n");

    if(juego->turno==TURNO_ROHAN){
        printf("-- Presione H para crear humanos (3 puntos) o E para crear Elfos (8 puntos)...\n\n");

    }else{
        printf("-- Presione O para crear Orcos (3 puntos) o U para crear Uruk-hais (8 puntos)...\n\n");

    }
        printf("-- Presione N si no desea crear un nuevo personaje...\n\n");


        printf("-- Presione T para terminar del juego...\n\n");

}
void inicializar_juego(juego_t* juego, datos_t* datos_obtenidos_del_usuario)
{
int i=0;
    juego->energia_isengard = ENERGIA_DE_INICIO;
    juego->energia_rohan = ENERGIA_DE_INICIO;

    definir_modo(juego);
    definir_bando(datos_obtenidos_del_usuario);

    int col=0,row=0;
    for(row=0;row<MAX_TERRENO_FIL;row++){
        for(col=0;col<MAX_TERRENO_COL;col++){
            juego->terreno[row][col]=' ';
        }
    }
    juego->cantidad_isengard = MAX_PERSONAJES;
    juego->cantidad_rohan = MAX_PERSONAJES;
    juego->llegadas_rohan = 0;
    juego->plus_rohan = 0;
    juego->llegadas_isengard = 0;
    juego->plus_isengard = 0;
    definir_plus (datos_obtenidos_del_usuario, juego);
    for (i = 0; i < MAX_PERSONAJES; i++){
        juego->isengard[i].codigo=0;
        juego->isengard[i].columna=0;
        juego->isengard[i].fila=0;
        juego->isengard[i].alcance=0;
        juego->isengard[i].ataque=0;
        juego->isengard[i].costo=0;
        juego->isengard[i].movilidad=0;
        juego->isengard[i].rango=0;
        juego->isengard[i].vida=0;

        juego->rohan[i].codigo=0;
        juego->rohan[i].columna=0;
        juego->rohan[i].fila=0;
        juego->rohan[i].alcance=0;
        juego->rohan[i].ataque=0;
        juego->rohan[i].costo=0;
        juego->rohan[i].movilidad=0;
        juego->rohan[i].rango=0;
        juego->rohan[i].vida=0;

    }

    for (i = 0; i < CANTIDAD_INICIO_ISENGARD; i++){
        juego->isengard[i].rango = RANGED;
        juego->isengard[i].ataque=10 + juego -> plus_isengard;
        juego->isengard[i].codigo='U';
        juego->isengard[i].bando=ATACA;
        juego->isengard[i].vida= vida_personajes(juego, i);
        juego->isengard[i].columna=aleatorio(10,0);
        juego->isengard[i].fila=aleatorio(3,1);
        while (juego->terreno[juego->isengard[i].fila][juego->isengard[i].columna] != ' '){
            juego->isengard[i].columna=aleatorio(10,0);
            juego->isengard[i].fila=aleatorio(3,1);
        }
        posicionar_personaje(juego,juego->isengard[i]);
    }

    for(i = 0; i < CANTIDAD_INICIO_ROHAN; i++){

        juego->rohan[i].rango = RANGED;
        juego->rohan[i].ataque=10 + juego -> plus_rohan;
        juego->rohan[i].codigo='E';
        juego->rohan[i].bando=DEFIENDE;
        juego->rohan[i].vida= vida_personajes(juego, i);
        juego->rohan[i].columna=aleatorio(10,0);
        juego->rohan[i].fila=aleatorio(3,5);
        while (juego->terreno[juego->rohan[i].fila][juego->rohan[i].columna] != ' '){
            juego->rohan[i].columna=aleatorio(10,0);
            juego->rohan[i].fila=aleatorio(3,5);
        }
        posicionar_personaje(juego,juego->rohan[i]);
    }
    juego->cantidad_isengard = 3;
    juego->cantidad_rohan = 3;
    juego->turno = TURNO_ROHAN;




}

void posicionar_personaje(juego_t* juego, personaje_t personaje)
{
    int X = personaje.columna;
    int Y = personaje.fila;

    juego->terreno[Y][X] = personaje.codigo;
}

void jugar(juego_t* juego, char bando, int posicion_personaje)
{
    if ((bando == DEFIENDE)&&(juego->rohan[posicion_personaje].codigo == HUMANO)){
        juego->turno = TURNO_ROHAN;
        juega_hombre(juego, posicion_personaje);
    }
    else if ((bando == ATACA)&&(juego->isengard[posicion_personaje].codigo == ORCO)){
        juego->turno = TURNO_ISENGARD;
        juega_orco(juego, posicion_personaje);
    }
    else{
        jugar_ranged(juego, posicion_personaje, bando);
    }
}

int aleatorio(int rango, int minimo)
{
    srand (( unsigned ) time ( NULL ));
    int numero = rand () % rango + minimo;

    return numero;
}
