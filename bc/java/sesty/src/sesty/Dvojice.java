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

class X
{
    public int i;
    
    public X(int i)
    {
        this.i = i;
    }
    
    @Override
    public String toString(int i)
    {
        return "" + i;
    }
}

public class Dvojice {
    public int prvni;
    public X druhy;
    
    public Dvojice(int prvni, X druhy)
    {
        this.prvni = prvni;
        this.druhy = druhy;
        
    }
    
    public Dvojice(Dvojice puvodni)
    {
        this.prvni = puvodni.prvni;
        this.druhy = new X(puvodni.druhy.i);
    }
    
    @Override
    public Object clone() throws CloneNotSupportedException{
        Dvojice vysledek = (Dvojice) super.clone();
        vysledek.druhy = new X(druhy.i);
    }
    
    public String toString()
    {
        return "(" + prvni + "," + druhy + ")";
    }
    
    
}
