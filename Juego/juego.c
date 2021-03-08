#include "batalla.h"
#include "perfil.h"

int main()
{

    juego_t juego;

    datos_t datos_obtenidos_del_usuario;
    inicializar_juego(&juego, &datos_obtenidos_del_usuario);

    personaje_t* p=NULL;
    realizar_turno(&juego);
    imprimir_pantalla(&juego);

    return 0;
}
