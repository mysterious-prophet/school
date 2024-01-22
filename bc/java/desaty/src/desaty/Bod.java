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
public class Bod extends GO{
    
        private int x;
    private int y;

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }
    
    public Bod(int barva, int x, int y){
        super(barva);
        setX(x);
        setY(y);
    }

    @Override
    public void nakresli() {
        System.out.println("["+getBarva()+"]("+x+","+y+")");
    }
    
    
}
