/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blikani;

import javax.swing.JOptionPane;

/**
 *
 * @author pokorm20
 */
public class Blikac {
    
    private int prvni, druha;
    private int pocetPrepnuti = 0;
    
    Object zamek = new Object();
    
    public Blikac()
    {
        prvni = 0;
        druha = 1;
    }
    
    public void prepni()
    {
        prvni = druha;
        druha = 1-druha;
        pocetPrepnuti++;
    }
    
    private void kontrola(int prvni, int druha)
    {
        if (prvni + druha != 1)
        {
            JOptionPane.showMessageDialog(null, "nekonzistence po " + pocetPrepnuti + " prepnutich", "Koncime", JOptionPane.INFORMATION_MESSAGE);
            System.exit(1);
        }
    }
    
    String getData()
    {
        return this.toString();
    }
    
    
    
    public void vypis()
    {
        System.out.println(this);
    }
    
    
    
    @Override
    public String toString()
    {
        int kopie_prvni;
        int kopie_druha;
        
        synchronized(zamek)
        {
            kopie_prvni = prvni;
            kopie_druha = druha;
        }
        
        
        kontrola(kopie_prvni, kopie_druha);
        return "" + kopie_prvni + " " + kopie_druha;
    }
    
}
