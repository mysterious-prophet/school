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
public class Usecka extends GO {
    
      private Bod pocatek;
    private Bod konec;
    
    public Usecka(int barva, Bod pocatek, Bod konec){
        super(barva);
        setPocatek(pocatek);
        setKonec(konec);
    }

   final public Bod getPocatek() {
        return pocatek;
    }

   final public void setPocatek(Bod pocatek) {
        this.pocatek = pocatek;
    }

   final public Bod getKonec() {
        return konec;
    }

   final public void setKonec(Bod konec) {
        this.konec = konec;
    }

    @Override
    public void nakresli() {
        pocatek.nakresli();
        konec.nakresli();
    }
    
    
}
