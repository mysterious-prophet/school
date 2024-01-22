/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxapplication1;


import javafx.application.Application;
import javafx.beans.binding.Bindings;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Font;
import javafx.stage.Stage;

/**
 *
 * @author pokorm20
 */
public class JavaFXApplication1 extends Application {
    
    @Override
    public void start(Stage primaryStage) {
        
        /*Label zprava = new Label("yoyoyo");
        zprava.setFont(new Font(100));
        
        Slider tahlo = new Slider();
        tahlo.setValue(100);
        tahlo.valueProperty().addListener(vlastnost-> zprava.setFont(new Font(tahlo.getValue())));
        
        Button tlacitko = new Button("zelenkava");
        tlacitko.setOnAction(udalost->zprava.setTextFill(Color.CHARTREUSE));
        VBox obsah = new VBox();
        obsah.getChildren().addAll(tlacitko, zprava, tahlo);
        
        
        primaryStage.setScene(new Scene(obsah));
        primaryStage.setTitle("yo");
        primaryStage.show();*/
        
        
       /* TextArea odberatel = new TextArea();
        TextArea platce = new TextArea();
        platce.textProperty().bindBidirectional(odberatel.textProperty());
        VBox obsah = new VBox();
        obsah.getChildren().addAll(new Label("Odberatel"), odberatel, new Label("Platce"), platce);
        Scene scena = new Scene(obsah);
        primaryStage.setScene(scena);
        primaryStage.show();*/
       
       
       Circle kruh = new Circle();
       kruh.setFill(Color.INDIGO);
       Pane panel = new Pane();
       panel.setPrefSize(300, 200);
       panel.getChildren().add(kruh);
       Scene scena = new Scene(panel);
       kruh.centerXProperty().bind(Bindings.divide(scena.widthProperty(), 2));
       kruh.centerYProperty().bind(Bindings.divide(scena.heightProperty(), 2));
       kruh.radiusProperty().bind(Bindings.divide(Bindings.min(scena.heightProperty(), scena.widthProperty()), 3));
       primaryStage.setScene(scena);
       primaryStage.show();
        
       
    }

  
}

class Pozdrav{
    private StringProperty text = new SimpleStringProperty("");
    public final StringProperty textProperty(){return text;};
    public final void setText(String novyText){text.set(novyText);};
    public final String getText(){return text.get();};
}
