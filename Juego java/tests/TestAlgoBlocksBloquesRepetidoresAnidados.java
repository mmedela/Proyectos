package tests;

import modelo.*;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class TestAlgoBlocksBloquesRepetidoresAnidados {

    @Test
    public void testAlgoritmoconRepite2DentroDeOtroDibujaLoEsperado() {
        AlgoBlocks algoBlocks = new AlgoBlocks();
        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        BloqueRepite2 repite2 = new BloqueRepite2();
        algoBlocks.agregarBloque(repite2);
            repite2.agregarBloque(new BloqueDerecha());
            BloqueRepite2 repite2b = new BloqueRepite2();
            repite2.agregarBloque(repite2b);
                repite2b.agregarBloque(new BloqueArriba());
        algoBlocks.agregarBloque(new BloqueDerecha());
        algoBlocks.ejecutar();
        // tiene que dibujar der, arr, arr, der, arr, arr, der
        assertEquals("[0 0 1 0, 1 0 1 1, 1 1 1 2, 1 2 2 2, 2 2 2 3, 2 3 2 4, 2 4 3 4]", algoBlocks.getLineas().toString());

    }
}
