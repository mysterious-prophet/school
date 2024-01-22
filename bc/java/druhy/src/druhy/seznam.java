/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package druhy;

/**
 *
 * @author pokorm20
 */
public class seznam {
    private prvek hlava, zarazka;
    public seznam()
    {
        hlava = zarazka = new prvek(0,null);
    }
    
    public void vlozNaZacatek(int co)
    {
        hlava = new prvek(co, hlava);
    } 
    public void vyprazdni()
    {
        hlava = zarazka;
        
    }
    
    public void vypis()
    {
        prvek  pom = hlava;
        while(pom != zarazka)
        {
            System.out.print(" " + pom.getData());
            pom = pom.getDalsi();
        }
    }
    
    public boolean prazdny()
    {
        return hlava == zarazka;
    }
    
    public int prvni() throws Exception
    {
        if (prazdny()) throw new Exception("prazdny seznam");
        return hlava.getData();
    }
}
