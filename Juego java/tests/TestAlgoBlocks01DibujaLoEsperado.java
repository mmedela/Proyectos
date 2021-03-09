package tests;
import modelo.*;
import static  org.junit.Assert.*;
import org.junit.Test;

public class TestAlgoBlocks01DibujaLoEsperado {

    @Test
    public void testAlgoritmoDibujaLoEsperado(){
        AlgoBlocks algoBlocks = new AlgoBlocks();

        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        algoBlocks.agregarBloque(new BloqueDerecha());
        algoBlocks.agregarBloque(new BloqueAbajo());

        algoBlocks.ejecutar();
        // METODO USADO PARA VERIFICAR LO DIBUJADO POR EL ALGORITMO
        // algoBlocks.getLineas().toString() DEVUELVE:
        // [0 0 1 0, 1 0 1 -1]
        // ES UN DIBUJO  QUE TIENE DOS LINEAS:
        // 0 0 1 0  : LINEA DESDE (0, 0) HASTA (1, 0)
        // 1 0 1 -1 : LINEA DESDE (1, 0) HASTA (1, -1)
        assertEquals("[0 0 1 0, 1 0 1 -1]", algoBlocks.getLineas().toString());
    }
}
