package tests;

import modelo.*;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;


public class TestBloqueArribaAbajoDerechaIzquierdaLevantaBaja {
	Dibujo dibujo;
	Personaje persona;

	@Before
    public void setUp() throws Exception {
        dibujo = new Dibujo();
		persona = new Personaje(dibujo);
    }
	
	@Test
	public void testBloqueDerechaMuevePersonajeALaDerecha(){
    	Bloque bloque = new BloqueDerecha();
    	bloque.ejecutar(persona);
        assertEquals(1 , persona.getPosX());
    }
	
	@Test
    public void testBloqueDerechaMuevePersonajeALaDerechaVariasVeces(){
    	Bloque bloque = new BloqueDerecha();
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
        assertEquals(3 , persona.getPosX());
    }
	
	@Test
	public void testBloqueIzquierdaMuevePersonajeALaIzquierda(){
		Bloque bloque = new BloqueIzquierda();
    	bloque.ejecutar(persona);
        assertEquals(-1 , persona.getPosX());
    }
	
	@Test
    public void testBloqueIzquierdaMuevePersonajeALaIzquierdaVariasVeces(){
		Bloque bloque = new BloqueIzquierda();
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
        assertEquals(-3 , persona.getPosX());
    }
	
	@Test
	public void testBloqueArribaMuevePersonajeArriba(){
		Bloque bloque = new BloqueArriba();
    	bloque.ejecutar(persona);
        assertEquals(1 , persona.getPosY());
    }
	
	@Test
    public void testBloqueArribaMuevePersonajeArribaVariasVeces(){
		Bloque bloque = new BloqueArriba();
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
        assertEquals(3 , persona.getPosY());
    }
	
	@Test
	public void testBloqueAbajoMuevePersonajeAbajo(){
		Bloque bloque = new BloqueAbajo();
    	bloque.ejecutar(persona);
        assertEquals(-1 , persona.getPosY());
    }
	
	@Test
    public void testBloqueAbajoMuevePersonajeAbajoVariasVeces(){
		Bloque bloque = new BloqueAbajo();
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
    	bloque.ejecutar(persona);
        assertEquals(-3 , persona.getPosY());
    }
	
	@Test
	public void testBloqueSubirLapizLevantaElLapiz(){
		Bloque bloque = new BloqueLevantarLapiz();
    	bloque.ejecutar(persona);
		assertFalse(persona.lapizEstaAbajo());
    }
	
	@Test
	public void testBloqueBajarLapizBajaElLapiz(){
		Bloque bloque = new BloqueBajarLapiz();
    	bloque.ejecutar(persona);
		assertTrue(persona.lapizEstaAbajo());
    }
}
