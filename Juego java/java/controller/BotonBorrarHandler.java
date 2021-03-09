package controller;

import javafx.event.Event;
import javafx.event.EventHandler;
import modelo.AlgoBlocks;
import vista.PanelAlgoritmoView;
import vista.PanelDibujoView;

public class BotonBorrarHandler implements EventHandler {
    private AlgoBlocks algoBlocks;
    private PanelDibujoView panelDibujo;
    private PanelAlgoritmoView panelAlgoritmo;

    public BotonBorrarHandler(AlgoBlocks algoBlocks, PanelDibujoView panelDibujo, PanelAlgoritmoView panelAlgoritmo) {
        this.algoBlocks = algoBlocks;
        this.panelDibujo = panelDibujo;
        this.panelAlgoritmo = panelAlgoritmo;
    }

    @Override
    public void handle(Event event) {
        panelAlgoritmo.borrar();
        panelDibujo.borrar();
        algoBlocks.borrarAlgoritmo();
        algoBlocks.borrarDibujo();
        panelAlgoritmo.setConjuntoActual(algoBlocks);
        panelAlgoritmo.borrarBloquesAMostrar();
    }
}
