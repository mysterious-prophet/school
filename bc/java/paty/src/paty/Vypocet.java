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
public interface Vypocet {
    
    default public double dalsi(double x){
        return dalsi(x);
    }
    
    public double prvni(int x);
    
    public  void vypis();
    
}
