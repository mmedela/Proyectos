package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAlgoBlocksBloquePersonalizado {

    @Test
    public void testAlgoritmoConBloquePersonalizadoDibujaLoEsperado() {
        AlgoBlocks algoBlocks = new AlgoBlocks();

        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        algoBlocks.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(new BloqueArriba());

        BloquePersonalizado personalizado = algoBlocks.crearBloquePersonalizado();

        algoBlocks.borrarAlgoritmo();
        algoBlocks.agregarBloque(personalizado);

        algoBlocks.ejecutar();

        assertEquals("[0 0 1 0, 1 0 1 1]", algoBlocks.getLineas().toString());

    }

}
