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

class Trida
{
    private static int pocet = 0;
    public  class Vnitrni  //static v prvnim prikladu?
    {
        public int x = pocet; //vnitrni trida ma pristup k vlast vnejsi
        // public int x = Trida.this.pocet; //taky funguje
    }
}

enum SvetoveStrany{SEVER, JIH, VYCHOD, ZAPAD} //mozne do deklarace pridat i vlastni metody

class Alfa
{
    public double beta(double x)
    {
        return x*x*x/3;
    }
    
    public double gama(double x)
    {
        return 1/x;
    }
    
}

public class Program {

    /**
     * @param args the command line arguments
     */
    
    public static void Overeni(Kontrola k)
    {
        k.zkontroluj();
    }
    
    public static void pocitani(Vypocet v)
    {
        System.out.println(v.prvni(2) + v.dalsi(4));   
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        
        //Trida.Vnitrni tv = new Trida.Vnitrni();
        //System.out.println(tv.x); //vypisuje private pocet Tridy, ma pristup
        
        //Trida t = new Trida();
        //Trida.Vnitrni tv = t.new Vnitrni();
        //int y = tv.x;
        
        //SvetoveStrany smer = SvetoveStrany.JIH;
        //System.out.println(smer);
        
        /*Kontejner k = new Kontejner(0);
        Nastroj n = new Nastroj();
        Kontrola kk = new Kontrola(){
            @Override
            public void zkontroluj() {
                System.out.println("Overeno");
            }
            
        };
        
        Overeni(k);
        Overeni(n);
        Overeni(kk);*/
        
        /*Nastroj n = new Nastroj();
        n.prvni(0);      
        Vypocet.vypis();
        Nastroj.vypis();
        Overeni(n);
        Overeni(new Kontrola(){
            @Override
            public void zkontroluj() {
                System.out.println("HAHA");
            }
        });*/
        
        Overeni(()->{System.out.println("provedeno");}); //lambda vyrazy
        //pocitani((x) -> x*x*x); //tady mam chybu
        
        Alfa alfa = new Alfa();
        //pocitani(alfa::beta); //proc to jemu fungovalo?
        //(Alfa::gama);
        
        //Par<Integer, String> par = new Par<>(1, "Nazdar");
        
        
    }
    
}
