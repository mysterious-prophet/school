/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ctvrty;

/**
 *
 * @author pokorm20
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    
    static int max(int ... data) // ... misto [] - funkce s promennym poctem parametru
    {
       
        int vysledek = Integer.MIN_VALUE;
        for(int i:data)
        {
            if (i>vysledek)
                vysledek = i;
        }
        return vysledek;
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        
         AbstraktniBod ab = new AbstraktniBod()
        {
            @Override
            public void vypis()
            {
                System.out.println("divna trida");
            };
        };
        
        System.out.println(max(new int[]{3,2,4}));
        Bod b = new Bod(4,7);
        System.out.println(b); //vypise hashcode
        System.out.println(b.hashCode());
        
        Bod c  = new Bod(1,2);
        
        System.out.println("Pocet bodu:" + Bod.kolik());
        
    }
    
}
