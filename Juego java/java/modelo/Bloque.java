package modelo;


public interface Bloque {

    void ejecutar(Personaje persona);

    void ejecutarInvertido(Personaje persona);

    String getNombre();

}
