/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package osmy;
import java.util.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

/**
 *
 * @author pokorm20
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    
    
    public static void regularni()
    {
        //String vzor = "."; vsechno
        //String vzor = "\\."; //jen tecka
        //String vzor = "\\d+"; \\D \\w \\s
        //String vzor = "[a-z]";
        String vzor = "[a-z&&[^d]]";//not d
        String text = "Bylo tam 123 lidi, 56 psu, -14 stevu";
        Pattern p = Pattern.compile(vzor);
        Matcher m = p.matcher(text);
        
        while(m.find())
        {
            System.out.println(m.group());
        }
    }
    
    
    public static void nahrada()
    {
        String vstup = "123 777 \n 6 \t 7 123";
        String vystup = vstup.replaceAll("\\s+", " ");
        System.out.println(vstup);
        System.out.println("--------");
        System.out.println(vystup);
        String[] vysledek = vstup.split("\\s+");
        System.out.println("--------");
        for (String s:vysledek)
        {
            System.out.println(s);
        }
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        
        /*String zprava = "";
        zprava += "chyba";
        zprava += "v souboru"; //nove a nove alokace pameti, neefektivni
        String jmeno = "soubor.txt"; 
        zprava += jmeno + " ";*/
        
        /*StringBuffer pomoc = new StringBuffer();
        pomoc.append("v souboru ");
        String jmeno = "soubor.txt";
        pomoc.append(jmeno);
        pomoc.append(" na radce ");
        pomoc.append(11); //jedenact
        String zprava = "";*/
        
        
        //%[index][priznaky][sirka][.presnost]konverze
        
        /*int i = 123456;
        double x = Math.PI;
        String s = String.format(new Locale("de", "DE"), "Dela to %d a pi je %g a zaplatite %1$X", i,x);
        System.out.println(s);
        
        Date ted = new Date();
        String cas = String.format("je prave %1$tH h %1$tM min %1$TS s %1$TZ, %1$tA, %1$Te. %1TB %1$tF %1$tT", ted);
        System.out.println(cas);*/
        
        //regularni();
        
        nahrada();
        
        
    }
    
    
    
}
