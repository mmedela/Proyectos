package vista;

import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Line;
import modelo.AlgoBlocks;
import modelo.Linea;

public class PanelDibujoView extends VBox{
    Pane dibujoSolo;

    public PanelDibujoView() {
        Label tituloDibujo = new Label("Dibujo");
        tituloDibujo.setStyle("-fx-font: 24 arial;");
        dibujoSolo = new Pane();
        this.getChildren().add(tituloDibujo);
        this.getChildren().add(dibujoSolo);
        this.setMinWidth(700);
        this.setStyle("-fx-border-color: black");
        this.setStyle("-fx-background-color: lightblue");
        this.setAlignment(Pos.TOP_CENTER);
    }

    public void borrar(){
        dibujoSolo.getChildren().clear();
    }

    public void agregarLinea(Line linea){
        dibujoSolo.getChildren().add(linea);
    }

    public void dibujar(AlgoBlocks algoBlocks){
        Integer xInicial = 350;
        Integer yInicial = 250;
        this.borrar();
        for (Linea linea : algoBlocks.getLineas()) {

            Integer x0 = linea.getCoordenadas().get(0) * 100+xInicial;
            Integer y0 = linea.getCoordenadas().get(1) * (-100)+yInicial;
            Integer x1 = linea.getCoordenadas().get(2) * 100+xInicial;
            Integer y1 = linea.getCoordenadas().get(3) * (-100)+yInicial;

            Line lineaADibujar = new Line(x0, y0, x1, y1);
            this.agregarLinea(lineaADibujar);

        }

    }
}
