package modelo;

public class Personaje {
    private Lapiz lapiz = new LapizArriba();
    private Posicion pos = new Posicion(0, 0);
    private Dibujo dibujo;

    public Personaje(Dibujo dibujo) {
        this.dibujo = dibujo;
    }

    public void mover(Integer dx, Integer dy) {
        Posicion pos2 = new Posicion(pos.getX() + dx, pos.getY() + dy);
        lapiz.dibujar(dibujo, pos, pos2);
        pos = pos2;
    }

    public void resetPosicion(){
        pos.setX(0);
        pos.setY(0);
    }

    public void bajarLapiz() {
        lapiz = new LapizAbajo();
    }

    public void levantarLapiz() {
        lapiz = new LapizArriba();
    }

    //  PARA TESTING
    public Boolean lapizEstaAbajo() {
        return lapiz.estaAbajo();
    }

    // PARA TESTING
    public int getPosX() {
        return pos.getX();
    }

    // PARA TESTING
    public int getPosY() {
        return pos.getY();
    }

}
