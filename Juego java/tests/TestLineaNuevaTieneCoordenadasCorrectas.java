package tests;

import modelo.Linea;
import modelo.Posicion;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestLineaNuevaTieneCoordenadasCorrectas {
    @Test
    public void TestLinea1()
    {
        Posicion posicion1 = new Posicion(2, 4);
        Posicion posicion2 = new Posicion(2, 5);
        Linea linea1 = new Linea(posicion1, posicion2);
        assertEquals("2 4 2 5", linea1.toString());
    }

}
