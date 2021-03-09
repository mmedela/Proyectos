package controller;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.shape.Line;
import modelo.AlgoBlocks;
import modelo.Linea;
import vista.PanelDibujoView;

public class BotonRunHandler implements EventHandler<ActionEvent> {
    private AlgoBlocks algoBlocks;
    private PanelDibujoView panelDibujo;

    public BotonRunHandler(AlgoBlocks algoBlocks, PanelDibujoView panelDibujo) {
        this.algoBlocks = algoBlocks;
        this.panelDibujo = panelDibujo;
    }

    public void handle(ActionEvent event) {
        algoBlocks.getLineas().clear();
        algoBlocks.resetPos();
        algoBlocks.ejecutar();

        panelDibujo.dibujar(algoBlocks);
    }
}
