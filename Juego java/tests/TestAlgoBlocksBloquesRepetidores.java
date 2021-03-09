package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAlgoBlocksBloquesRepetidores {

    @Test
    public void testAlgoritmoconRepite2DibujaLoEsperado() {
        AlgoBlocks algoBlocks = new AlgoBlocks();
        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        algoBlocks.agregarBloque(new BloqueDerecha());
        BloqueRepite2 repite2 = new BloqueRepite2();
        repite2.agregarBloque(new BloqueAbajo());
        repite2.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(repite2);
        algoBlocks.ejecutar();
        assertEquals("[0 0 1 0, 1 0 1 -1, 1 -1 2 -1, 2 -1 2 -2, 2 -2 3 -2]", algoBlocks.getLineas().toString());

    }
    @Test
    public void testAlgoritmoconRepite3DibujaLoEsperado() {
        AlgoBlocks algoBlocks = new AlgoBlocks();
        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        BloqueRepite3 repite3 = new BloqueRepite3();
        repite3.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(repite3);
        algoBlocks.ejecutar();
        assertEquals("[0 0 1 0, 1 0 2 0, 2 0 3 0]", algoBlocks.getLineas().toString());

    }

}
