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
public class Nastroj implements Kontrola, Vypocet{

    @Override
    public void zkontroluj() {
        System.out.println("Byla provedena kontrola");
    }
    
    //@Override
    public double dalsi(int x){
        return x/2;
    }
    
    public double prvni(int x){
        return x^x;
    }
    
    public void vypis(){
           
    }
}
