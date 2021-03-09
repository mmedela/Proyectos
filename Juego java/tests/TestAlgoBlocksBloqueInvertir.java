package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAlgoBlocksBloqueInvertir {

    @Test
    public void testAlgoritmoConBloqueInvertirDibujaLoEsperado() {
        AlgoBlocks algoBlocks = new AlgoBlocks();
        algoBlocks.agregarBloque(new BloqueBajarLapiz());

        BloqueInvertir invertido = new BloqueInvertir();
        invertido.agregarBloque(new BloqueDerecha());
        invertido.agregarBloque(new BloqueAbajo());

        algoBlocks.agregarBloque(invertido);

        algoBlocks.ejecutar();
        assertEquals("[0 0 -1 0, -1 0 -1 1]", algoBlocks.getLineas().toString());
    }
}
