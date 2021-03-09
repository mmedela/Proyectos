package tests;

import modelo.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class TestAlgoBlocks03BorrarAlgoritmoNoDibujaNada {

    @Test
    public void testAlgoritmoBorradoNoDibujaNada(){
        AlgoBlocks algoBlocks = new AlgoBlocks();

        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        algoBlocks.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(new BloqueAbajo());
        algoBlocks.borrarAlgoritmo();
        algoBlocks.ejecutar();
        assertEquals("[]", algoBlocks.getLineas().toString());
    }

}
