/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package filtrsort;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.text.Collator;

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
        
        (new BufferedReader(new InputStreamReader(System.in)))
                .lines()
                .sorted(Collator.getInstance())
                .forEachOrdered(l->System.out.println(l));
    }
    
}
