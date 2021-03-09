package controller;

import javafx.scene.control.Button;
import modelo.*;
import vista.PanelAlgoritmoView;

import java.util.EmptyStackException;


public class BotonesPanelBloquesHandler {
    private PanelAlgoritmoView panelAlgoritmo;

    public BotonesPanelBloquesHandler(AlgoBlocks algoBlocks,PanelAlgoritmoView panelAlgoritmo, Button[] boton ) {
        this.panelAlgoritmo = panelAlgoritmo;

        boton[1].setOnAction(value -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueBajarLapiz());
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[2].setOnAction(value -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueLevantarLapiz());
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[3].setOnAction(value -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueArriba());
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[4].setOnAction(value -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueAbajo());

            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[5].setOnAction(value -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueIzquierda());
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[6].setOnAction(valor -> {
            panelAlgoritmo.getConjuntoActual().agregarBloque(new BloqueDerecha());
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

        boton[7].setOnAction(value -> {
            BloqueInvertir invertido = new BloqueInvertir();
            panelAlgoritmo.getConjuntoActual().agregarBloque(invertido);
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
            panelAlgoritmo.setConjuntoActual(invertido);
            panelAlgoritmo.agregarCiclo(invertido);
        });

        boton[8].setOnAction(value -> {
            BloqueRepite2 bloqueRepite2 = new BloqueRepite2();
            panelAlgoritmo.getConjuntoActual().agregarBloque(bloqueRepite2);
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
            panelAlgoritmo.setConjuntoActual(bloqueRepite2);
            panelAlgoritmo.agregarCiclo(bloqueRepite2);
        });

        boton[9].setOnAction(value -> {
            BloqueRepite3 bloqueRepite3 = new BloqueRepite3();
            panelAlgoritmo.getConjuntoActual().agregarBloque(bloqueRepite3);
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
            panelAlgoritmo.setConjuntoActual(bloqueRepite3);
            panelAlgoritmo.agregarCiclo(bloqueRepite3);
        });

        boton[10].setOnAction(value -> {

            try{
                panelAlgoritmo.setConjuntoActual(panelAlgoritmo.cerrarCiclo());
                panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
            }catch (EmptyStackException pilaVacia) {
                panelAlgoritmo.manejarExepcion();
            }
        });

        boton[11].setOnAction(value -> {
            BloquePersonalizado personalizado = algoBlocks.getBloquePersonalizado() ;
            panelAlgoritmo.getConjuntoActual().agregarBloque(personalizado);
            panelAlgoritmo.actualizar(panelAlgoritmo.getConjuntoActual());
        });

    }

}

