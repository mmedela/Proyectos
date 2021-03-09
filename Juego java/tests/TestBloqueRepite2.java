package tests;
import modelo.*;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestBloqueRepite2 {
    Personaje persona;
    Dibujo dibujo;

    @Before
    public void setUp() throws Exception {
        dibujo = new Dibujo();
        persona = new Personaje(dibujo);
    }

    @Test
    public void testRepite2DibujaLoEsperado() {
        persona.bajarLapiz();
        BloqueRepite2 bloqueRepite2 = new BloqueRepite2();
        bloqueRepite2.agregarBloque(new BloqueAbajo());
        bloqueRepite2.ejecutar(persona);
        assertEquals("[0 0 0 -1, 0 -1 0 -2]",dibujo.getLineas().toString());
    }
    @Test
    public void testRepite2ConVariosBloquesDibujaLoEsperado() {
        persona.bajarLapiz();
        BloqueRepite2 bloqueRepite2 = new BloqueRepite2();
        bloqueRepite2.agregarBloque(new BloqueDerecha());
        bloqueRepite2.agregarBloque(new BloqueAbajo());
        bloqueRepite2.ejecutar(persona);
        assertEquals("[0 0 1 0, 1 0 1 -1, 1 -1 2 -1, 2 -1 2 -2]",dibujo.getLineas().toString());
    }

}