package modelo;

import java.util.LinkedHashSet;
import java.util.Set;

public class Dibujo {
    private Set<Linea> lineas = new LinkedHashSet<Linea>();

    public void agregarLinea(Linea linea) {
        lineas.add(linea);
    }

    public Set getLineas() {
        return lineas;
    }
}
