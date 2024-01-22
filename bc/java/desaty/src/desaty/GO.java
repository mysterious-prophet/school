/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package desaty;

/**
 *
 * @author pokorm20
 */
public abstract class GO implements java.io.Serializable {
    int barva;
    public GO(int barva){
    setBarva(barva);
    }

    final public int getBarva() {
        return barva;
    }

    final public void setBarva(int barva) {
        this.barva=barva;
    }
    
    public abstract void nakresli();
}
