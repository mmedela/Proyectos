package vista;

import controller.BotonBorrarHandler;
import controller.BotonPersonalizadoHandler;
import controller.BotonRunHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import modelo.AlgoBlocks;
import modelo.Bloque;
import modelo.ConjuntoBloques;

import java.util.ArrayList;
import java.util.EmptyStackException;
import java.util.Stack;

public class PanelAlgoritmoView extends VBox {
    VBox bloquesAlgoritmo;
    ConjuntoBloques conjuntoActual;
    AlgoBlocks algoBlocks;
    private Stack<ConjuntoBloques> pilaCiclos = new Stack<>();
    private ArrayList<Bloque> bloquesAMostrar = new ArrayList<Bloque>();


    public PanelAlgoritmoView(AlgoBlocks algoBlocks, ConjuntoBloques conjuntoActual, PanelDibujoView panelDibujo) {
        this.conjuntoActual = conjuntoActual;
        this.algoBlocks = algoBlocks;
        this.pilaCiclos.push(algoBlocks);

        //TITULO
        Label tituloAlgoritmoGeneral = new Label("Algoritmo");
        tituloAlgoritmoGeneral.setStyle("-fx-font: 24 arial;");

        //BOTONERA
        Button buttonRun = new Button("Run");
        buttonRun.setOnAction(new BotonRunHandler(algoBlocks, panelDibujo));

        Button buttonBorrar = new Button("Borrar todo");
        buttonBorrar.setOnAction(new BotonBorrarHandler(algoBlocks, panelDibujo, this));

        Button buttonPersonalizado = new Button("Guardar Macro");
        buttonPersonalizado.setOnAction(new BotonPersonalizadoHandler(algoBlocks));

        Button buttonTerminar = new Button("Terminar el Programa y Salir");
        buttonTerminar.setOnAction(value -> {
            System.exit(0);
        });

        HBox botonera1 = new HBox(buttonRun, buttonBorrar, buttonPersonalizado);
        botonera1.setAlignment(Pos.TOP_CENTER);

        HBox botonera2 = new HBox(buttonTerminar);
        botonera2.setAlignment(Pos.TOP_CENTER);

        VBox botonera = new VBox(botonera1, botonera2);
        botonera.setAlignment(Pos.TOP_CENTER);


        //BLOQUES DEL ALGORITMO
        bloquesAlgoritmo = new VBox();
        bloquesAlgoritmo.setStyle("-fx-border-color: black");
        bloquesAlgoritmo.setAlignment(Pos.TOP_CENTER);

        this.getChildren().add(tituloAlgoritmoGeneral);
        this.getChildren().add(botonera);
        this.getChildren().add(bloquesAlgoritmo);
        this.setStyle("-fx-border-color: black");
        this.setStyle("-fx-background-color: lightgreen");
        this.setMinWidth(200);
        this.setMinHeight(500);
        this.setAlignment(Pos.TOP_CENTER);

    }

    public void agregarBloque(Button bloque) {
        bloquesAlgoritmo.getChildren().add(bloque);
    }

    public void borrar() {
        bloquesAlgoritmo.getChildren().clear();
    }

    public void setConjuntoActual(ConjuntoBloques conjuntoActual) {
        this.conjuntoActual = conjuntoActual;
    }

    public ConjuntoBloques getConjuntoActual(){
        return conjuntoActual;
    }

    public void agregarCiclo(ConjuntoBloques bloque){
        pilaCiclos.add(bloque);
    }

    public ConjuntoBloques cerrarCiclo() throws EmptyStackException {
        pilaCiclos.pop();
        return pilaCiclos.peek();
    }


    public void manejarExepcion(){

        Stage exceptionStage = new Stage();
        exceptionStage.setTitle(" ADVERTENCIA ");
        exceptionStage.setMinWidth(500);
        exceptionStage.setMinHeight(100);
        exceptionStage.initModality(Modality.APPLICATION_MODAL);

        Pane layout = new Pane();

        Scene exceptionScene = new Scene(layout);
        exceptionStage.setScene(exceptionScene);

        Label label = new Label("  Está intentando cerrar un ciclo que nunca abrió, el programa se cerrara  ");
        label.setStyle("-fx-font: 14 arial;");
        label.setAlignment(Pos.TOP_CENTER) ;


        Button buttonCerrar = new Button(" Cerrar ");
        buttonCerrar.setOnAction(value -> {
            System.exit(0);
            exceptionStage.close();
        });

        VBox ventana = new VBox(label, buttonCerrar);
        ventana.setAlignment(Pos.TOP_CENTER);

        layout.getChildren().add(ventana);

        exceptionStage.show();
    }

  public void actualizar(ConjuntoBloques conjuntoActual){
        ArrayList<Bloque> bloquesModelo = conjuntoActual.getListaBloques();
        this.borrar();
        bloquesAMostrar.add(bloquesModelo.get(bloquesModelo.size()-1));
        bloquesAMostrar.forEach(bloque -> bloquesAlgoritmo.getChildren().add(new Button(bloque.getNombre())));

  }

  public void borrarBloquesAMostrar(){
        bloquesAMostrar.clear();
  }



}


