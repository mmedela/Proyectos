package modelo;

import java.util.ArrayList;

public class BloqueInvertir implements Bloque, ConjuntoBloques {
    private ArrayList<Bloque> listaBloques = new ArrayList<Bloque>();

    public void agregarBloque(Bloque bloque) {
        listaBloques.add(bloque);
    }

    public void ejecutar(Personaje persona) {
        listaBloques.forEach(bloque -> bloque.ejecutarInvertido(persona));
    }

    public void ejecutarInvertido(Personaje persona) {
        listaBloques.forEach(bloque -> bloque.ejecutar(persona));
    }


    public String getNombre(){
        return "Invertir";
    }

    public ArrayList<Bloque> getListaBloques() {
        return listaBloques;
    }

}
