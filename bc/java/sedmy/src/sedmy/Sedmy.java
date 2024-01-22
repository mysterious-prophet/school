/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sedmy;

/**
 *
 * @author pokorm20
 */
public class Sedmy {
    
    static final int HORNI_MEZ = 12;
    public static int faktorial(int n) throws Exception
    {
        if(n < 0 || (n > HORNI_MEZ))
            //throw new com.sun.media.sound.InvalidDataException("mimo meze");
            throw new IndexOutOfBoundsException("mimo meze");//IllegalArgumentException("mimo meze"); //korektni nazev vyjimky
        
        int vysledek = 1;
        while(n > 1)
            vysledek *= n--;
        
        return vysledek;        
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        try(java.util.Scanner vstup = new java.util.Scanner(System.in);)
        {
            System.out.println("Cislo:");
            //java.util.Scanner vstup = new java.util.Scanner(System.in);
            int n = vstup.nextInt();
            System.out.println(faktorial(n));
            System.out.println("podpis");
        }
        catch(IllegalArgumentException e | IndexOutOfBoundsException e)
        {
            //System.out.println("CHyba");
        }
        catch(Exception e)
        {
            //prazdny schvalne    
        }
        finally
        {
            System.out.println("podpis");
            //vstup.close();
        }
        
    }
    
}
