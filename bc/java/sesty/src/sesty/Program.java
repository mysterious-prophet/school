/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sesty;

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
        
        Par<String, String> dvaStringy = new Par<>("yo", "steve");
        System.out.println(dvaStringy.getDruhy());
        
        Par<Integer, Long> dveCisla = new Par<>(7,9L); //vs Par<int[], long[]>
        //Long ll = dvaStringy.getDruhy();
        int x = Pomoc.max(5, 6);
        
        Par pq = new Par(null, null);
        
        java.util.ArrayList<Integer> ali = new ArrayList<>();
        ali.add(4);
        ali.add(5);
        //Pomoc.tisk(ali);
        
        Dvojice par = new Dvojice(6, new X(8));
        Dvojice par2 = (Dvojice)par.clone();
        par2.druha = new X(9);
        System.out.println(par);
    }
    
}
