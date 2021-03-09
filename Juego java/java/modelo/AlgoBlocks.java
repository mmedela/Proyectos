package modelo;

import java.util.ArrayList;
import java.util.Set;

public class AlgoBlocks implements ConjuntoBloques {
    private ArrayList<Bloque> listaBloques = new ArrayList<Bloque>();
    private ArrayList<Bloque> listaPlana = new ArrayList<>();
    private Dibujo dibujo = new Dibujo();
    private Personaje persona = new Personaje(dibujo);
    private BloquePersonalizado bloquePersonalizado = new BloquePersonalizado(listaBloques);

    public void resetPos(){
        persona.resetPosicion();
    }


    public void actualizarListaPlana(Bloque bloque){
        listaPlana.add(bloque);
    }
    public void agregarBloque(Bloque bloque) {
        listaBloques.add(bloque);
        actualizarListaPlana(bloque);
    }

    public void ejecutar() {
        listaBloques.forEach(bloque -> bloque.ejecutar(persona));
    }


    public BloquePersonalizado crearBloquePersonalizado() {
        bloquePersonalizado = new BloquePersonalizado(listaBloques);
        return bloquePersonalizado;
    }

    public BloquePersonalizado getBloquePersonalizado() {
        return bloquePersonalizado;
    }

    public void borrarAlgoritmo() {
        listaBloques.clear();
        persona.levantarLapiz();
    }

    public void borrarDibujo(){
        dibujo.getLineas().clear();
        resetPos();
    }

    public Set<Linea> getLineas() {
        return dibujo.getLineas();
    }

    public ArrayList<Bloque> getListaBloques() {
        return listaBloques;
    }
}
