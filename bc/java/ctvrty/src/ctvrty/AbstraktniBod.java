/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ctvrty;

/**
 *
 * @author pokorm20
 */
public abstract class AbstraktniBod {
    private double x,y;
    private static int pocet;
    static{
        pocet = 0;
    }
    public AbstraktniBod(double x, double y){
        this.x = x;
        this.y = y;
        pocet++;
    }
    
    public AbstraktniBod(double x){
        this(x,0);
    }
    
    public AbstraktniBod(){
        this.x = 0;
        this.y = 0;
    }
    
    @Override
    public String toString()
    {
       return "(" + x +", " +y+")";
    }
    
    public static int kolik(){
        return pocet;
    }
    
    public abstract void vypis();
}


// class Bod1 extends Bod //neda se dedit od final bod

class Bod extends AbstraktniBod{
    public Bod(double x, double y){
        super(x,y);
    }
    @Override
    public void vypis(){
        System.out.println(this);
    }
}