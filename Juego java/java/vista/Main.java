package vista;

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import modelo.*;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("AlgoBlocks");

        AlgoBlocks algoBlocks = new AlgoBlocks();

        PanelDibujoView panelDibujo = new PanelDibujoView();
        PanelAlgoritmoView panelAlgoritmo = new PanelAlgoritmoView(algoBlocks, algoBlocks, panelDibujo);
        PanelBloquesView panelBloques = new PanelBloquesView(algoBlocks,  panelAlgoritmo);

        HBox hbox = new HBox( panelBloques,panelAlgoritmo,panelDibujo);
        hbox.setAlignment(Pos.TOP_CENTER);

        Scene scene = new Scene(hbox, 1400, 700);
        primaryStage.setScene(scene);
        primaryStage.show();

    }
}

