package tests;

import clases_tp.*;
import org.junit.Test;

import javax.sound.sampled.Line;
import java.util.ArrayList;

import static org.junit.Assert.assertEquals;

public class TestAlgoBlocks01DevuelveCoordenadas {

    @Test
    public void testAlgoritmoDibujaLoEsperado(){
        AlgoBlocks algoBlocks = new AlgoBlocks();

        algoBlocks.agregarBloque(new BloqueBajarLapiz());
        algoBlocks.agregarBloque(new BloqueArriba());
        algoBlocks.agregarBloque(new BloqueArriba());

        algoBlocks.ejecutar();
        System.out.println(algoBlocks.getLineas());

//        algoBlocks.getLineas().forEach(Linea linea -> System.out.println(linea.getCoordenadas())
        for (Linea linea : algoBlocks.getLineas()){
            System.out.println(linea.getCoordenadas().get(1));

        }





    }
}
