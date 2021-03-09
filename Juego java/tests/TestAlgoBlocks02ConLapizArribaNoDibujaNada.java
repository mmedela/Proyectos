package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAlgoBlocks02ConLapizArribaNoDibujaNada {

    @Test
    public void testAlgoritmoConLapizArribaNoDibujaNada(){
        AlgoBlocks algoBlocks = new AlgoBlocks();

        algoBlocks.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(new BloqueAbajo());

        algoBlocks.ejecutar();
        assertEquals("[]", algoBlocks.getLineas().toString());
    }


}
