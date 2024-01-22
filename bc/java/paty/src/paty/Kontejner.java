/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paty;

/**
 *
 * @author pokorm20
 */


public class Kontejner implements Kontrola 
{

    private int x;
    public Kontejner(int x){
        this.x = x;
    }
    
    @Override
    public void zkontroluj()
    {
        System.out.println("Zkontrolovano");
    }
    
    public void uloz(){};
}
