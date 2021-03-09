package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestDibujoAgregarLineasQuedanGuardadas {
    @Test
    public void TestAgregarLineas(){
        Dibujo dibujo1 = new Dibujo();
        Posicion pos1 = new Posicion(0,0);
        Posicion pos2 = new Posicion(0,1);
        Posicion pos3 = new Posicion(1,1);

        Linea linea1 = new Linea(pos1, pos2);
        dibujo1.agregarLinea(linea1);

        Linea linea2 = new Linea(pos2, pos3);
        dibujo1.agregarLinea(linea2);

        Linea linea3 = new Linea(pos2, pos3);
        dibujo1.agregarLinea(linea3);

        assertEquals("[0 0 0 1, 0 1 1 1]", dibujo1.getLineas().toString());

    }
}
