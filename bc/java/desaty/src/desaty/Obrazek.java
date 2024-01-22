/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package desaty;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;


/**
 *
 * @author pokorm20
 */
public class Obrazek extends GO {
 private static ArrayList<GO> obrazek = new ArrayList<>();
    
    public Obrazek(){
        super(0);
    }
    
    public void pridej(GO g){
        obrazek.add(g);
    }
    
    @Override
    public void nakresli() {
        for(GO g: obrazek){
            g.nakresli();
        }
    }
    
    public void uloz(String jmenoSouboru) throws FileNotFoundException, IOException{
        try(ObjectOutputStream vystup = new ObjectOutputStream(new FileOutputStream(jmenoSouboru))){
            vystup.writeObject(this);
        }
            
    }
    
    public static Obrazek nacti(String jemnoSouboru) throws FileNotFoundException, IOException, ClassNotFoundException{
        try(ObjectInputStream vstup = new ObjectInputStream(new FileInputStream(jemnoSouboru))){
            Object obj = vstup.readObject();
            Obrazek obr = (Obrazek)obj;
            return obr;
        }
    }
     
}
