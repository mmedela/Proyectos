package modelo;

public interface Lapiz {
    void dibujar(Dibujo dibujo, Posicion com, Posicion fin);

    //    PARA TESTING
    boolean estaAbajo();
}
