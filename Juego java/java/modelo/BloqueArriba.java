package modelo;

public class BloqueArriba implements Bloque {

    public void ejecutar(Personaje persona) {
        persona.mover(0, 1);
    }

    public void ejecutarInvertido(Personaje persona) {
        persona.mover(0, -1);
    }


    public String getNombre(){
        return "Arriba";
    }
}
