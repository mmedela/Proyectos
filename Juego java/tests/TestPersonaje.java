package tests;
import modelo.*;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestPersonaje {
	Personaje persona;
    Dibujo dibujo;
    @Before
    public void setUp() throws Exception {
        dibujo = new Dibujo();
        persona = new Personaje(dibujo);
    }

    @Test
    public void testPersonajeSeMueveALaDerecha(){
    	persona.mover(1,0);
        assertEquals(1 , persona.getPosX());
    }
    
    @Test
    public void testPersonajeSeMueveALaIzquierda(){
    	persona.mover(-1,0);
        assertEquals(-1 , persona.getPosX());
    }
    
    @Test
    public void testPersonajeSeMueveArriba(){
    	persona.mover(0,1);
        assertEquals(1 , persona.getPosY());
    } 
    
    @Test
    public void testPersonajeSeMueveAbajo(){
    	persona.mover(0,-1);
        assertEquals(-1 , persona.getPosY());
    }
    
    @Test
    public void testPersonajeElLapizEstaArribaCuandoSeCreaElPersonaje(){
    	assertFalse(persona.lapizEstaAbajo());
    }
    
    @Test
    public void testPersonajeElLapizEstaArriba(){
    	persona.levantarLapiz();
        assertFalse(persona.lapizEstaAbajo());
    }

    @Test
    public void testPersonajeElLapizEstaAbajo(){
        persona.bajarLapiz();
        assertTrue(persona.lapizEstaAbajo());
    }

    @Test
    public void TestPersonajeSeMueveADerechaConLapizAbajoDibujaLinea(){
        persona.bajarLapiz();
        persona.mover(1,0);
        assertEquals("[0 0 1 0]", dibujo.getLineas().toString());
    }

    @Test
    public void TestPersonajeSeMueveAbajoConLapizAbajoDibujaLinea(){
        persona.bajarLapiz();
        persona.mover(0,-1);
        assertEquals("[0 0 0 -1]", dibujo.getLineas().toString());
    }

    @Test
    public void TestPersonajeSeMueveAbajoConLapizArribaNoDibujaNada(){
        persona.levantarLapiz();
        persona.mover(0,-1);
        assertEquals("[]", dibujo.getLineas().toString());
    }
}
