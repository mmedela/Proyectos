package modelo;

public class BloqueDerecha implements Bloque {

    public void ejecutar(Personaje persona) {
        persona.mover(1, 0);
    }

    public void ejecutarInvertido(Personaje persona) {
        persona.mover(-1, 0);
    }


    public String getNombre(){
        return "Derecha";
    }
}
