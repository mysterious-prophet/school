/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package desaty;


import java.io.*
/**
 *
 * @author pokorm20
 */
public class SerializovatelnaBarva implements Serializable{
    private Barva barva;
    public SerializovatelnaBarva(Barva _barva)
    {
        setBarva(barva);
    }
    
    public SerializovatelnaBarva(int _barva)
    {
        setBarva(new Barva(_barva));
    }
            
    public Barva getBarva()
    {
        return barva;
    }
    
    public void setBarva(Barva barva)
    {
        this.barva = barva;
    }
    
    private void writeObject(ObjectOutputStream vystup) throws IOException
    {
            vystup.writeInt (getBarva().getBarva());
        
    }
    
    private void readObject(ObjectInputStream vstup) throws IOException, ClassNotFoundException
    {
        int _barva = 
    }
    
}
