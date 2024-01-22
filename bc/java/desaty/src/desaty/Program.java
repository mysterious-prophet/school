/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package desaty;

import java.io.FileNotFoundException;
import java.io.IOException;


/**
 *
 * @author pokorm20
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        Obrazek o1 = new Obrazek();
        o1.pridej(new Bod(1,55,66));
        o1.pridej(new Usecka(0, new Bod(1,57,98), new Bod(1,89,100)));
        o1.nakresli();
        o1.uloz("obrazek.obr");
        o1 = null;
        System.out.println("-------");
        Obrazek o2 = (Obrazek)vstup.readObject();
        o2.nakresli();
                
        
        
        
    }
    
}
