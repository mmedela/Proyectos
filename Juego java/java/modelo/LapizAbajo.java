package modelo;

public class LapizAbajo implements Lapiz {
    public void dibujar(Dibujo dibujo, Posicion com, Posicion fin) {
        Linea linea = new Linea(com, fin);
        dibujo.agregarLinea(linea);
    }

    //  PARA TESTING
    @Override
    public boolean estaAbajo() {
        return true;
    }
}
