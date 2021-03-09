package vista;

import controller.BotonesPanelBloquesHandler;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import modelo.*;

public class PanelBloquesView extends VBox {

    private Button[] boton = new Button[12];

    public PanelBloquesView(AlgoBlocks algoBlocks, PanelAlgoritmoView panelAlgoritmo){
        Label tituloBloques = new Label("Bloques");
        tituloBloques.setStyle("-fx-font: 24 arial;");
        this.getChildren().add(tituloBloques);
        this.setStyle("-fx-border-color: #000000");
        this.setStyle("-fx-background-color: pink");
        this.setMinWidth(200);
        this.setMinHeight(500);
        this.setAlignment(Pos.TOP_CENTER);


        // Botones para crear algoritmo y sus funcionalidades

        boton[1] = new Button("Bajar Lapiz");
        boton[2] = new Button("Subir Lapiz");
        boton[3] = new Button("Arriba");
        boton[4] = new Button("Abajo");
        boton[5] = new Button("Izquierda");
        boton[6] = new Button("Derecha");
        boton[7] = new Button("Invertir");
        boton[8] = new Button("Repite 2");
        boton[9] = new Button("Repite 3");
        boton[10] = new Button("Cerrar ciclo Actual");
        boton[11] = new Button("Run Macro");

        BotonesPanelBloquesHandler botonera = new BotonesPanelBloquesHandler(algoBlocks, panelAlgoritmo, boton);

        // Agregamos los botones a la interfaz
        for (int i=1;i<=11;i++){
            this.getChildren().add(boton[i]);
        }
    }
}
