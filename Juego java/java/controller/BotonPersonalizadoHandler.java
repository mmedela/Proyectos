package controller;

import javafx.event.Event;
import javafx.event.EventHandler;
import modelo.AlgoBlocks;

public class BotonPersonalizadoHandler implements EventHandler {
    private AlgoBlocks algoBlocks;

    public BotonPersonalizadoHandler(AlgoBlocks algoBlocks) {
        this.algoBlocks = algoBlocks;
    }

    @Override
    public void handle(Event event) {
        algoBlocks.crearBloquePersonalizado();
    }
}
