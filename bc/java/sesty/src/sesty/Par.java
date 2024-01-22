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
public class Par<T, U> {
    private T prvni;
    private U druhy;
    public Par(T _prvni, U _druhy)
    {
        prvni = _prvni;
        druhy = _druhy;
    }
    
    public void setPrvni(T _prvni)
    {
        prvni = _prvni;
    }
    
    public void setDruhy(U _druhy)
    {
        druhy = _druhy;
    }
    
    T getPrvni()
    {
        return prvni;
    }
    
    U getDruhy()
    {
        return druhy;
    }
    
}
