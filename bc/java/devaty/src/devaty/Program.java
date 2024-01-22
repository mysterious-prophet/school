/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package devaty;

import java.io.*;

/**
 *
 * @author pokorm20
 */
public class Program {
    
    String kontrola(String[] args)
    {
        switch(args.length)
        {
            case 0:
                return ".";
            case 1:
                return args[0];
            default:
                System.err.println("pouziti: java program [adresar]");
                System.exit(1);
                return "";
        }
    }
    
    public void vypisAdresare(File adresar)
    {
        File[] polozky = adresar.listFiles();
        for(File polozka : polozky)
        {
            if(polozka.isDirectory())
                System.out.println(polozka.getName());
        }
        System.out.println("soubory: ");
        for(File polozka: polozky)
        {
            if(polozka.isDirectory())
                System.out.println(polozka.getName()                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 );
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        
        String cesta = kontrola(args);
        File adresar = new File(cesta);
        if(adresar.exists() && adresar.isDirectory())
        {
            
        }
        else
        {
            System.out.println("zadany adresar neexistuje");
        }
    }
    
}
