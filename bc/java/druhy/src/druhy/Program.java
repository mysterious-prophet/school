/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package druhy;

import java.util.Scanner;
//import java.util.*;

import static java.lang.Math.*;

// byte 1B vs.  Byte - objektove obalove typy jsou konstantni
//short 2B  Short
// int 4B   Integer
//long 8B   Long

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
        seznam s = new seznam();
        //s.vlozNaZacatek(5);
        //s.vlozNaZacatek(6);
        //s.vypis();
        
        Scanner vstup = new Scanner(System.in);
        while(vstup.hasNextInt())
        {
            int n = vstup.nextInt();
            s.vlozNaZacatek(n);
            if (n == 0) break;
        }
        s.vypis();
        
        double x = 3.14;
        double y = sin(x);
        
    }
    
}
