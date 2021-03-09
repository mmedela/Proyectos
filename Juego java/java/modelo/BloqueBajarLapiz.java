package modelo;

public class BloqueBajarLapiz implements Bloque {

    public void ejecutar(Personaje persona) {
        persona.bajarLapiz();
    }

    public void ejecutarInvertido(Personaje persona) {
        persona.levantarLapiz();
    }


    public String getNombre(){
        return "Bajar Lapiz";
    }
}
