package tests;

import modelo.*;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestLapizAbajoCreaLineaCorrectaEnDibujo {
    Dibujo dibujo;
    Posicion pos1 = new Posicion(0, 0);
    Posicion pos2 = new Posicion(0, 1);

    @Before
    public void setUp() {
        dibujo = new Dibujo();
    }

    @Test
    public void TestLapizAbajoCreaLineaCorrectaEnDibujo() {

        Lapiz lapiz = new LapizAbajo();
        lapiz.dibujar(dibujo, pos1, pos2);

        assertEquals("[0 0 0 1]", dibujo.getLineas().toString());

    }

}
