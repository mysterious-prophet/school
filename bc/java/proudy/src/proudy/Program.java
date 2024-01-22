
package proudy;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;
//import java.util.ArrayList;
import java.util.stream.*;

 class Kontakt{
    public String jmeno;
    public String prijmeni;
    public String telefon;
    public String typ;
    
    Kontakt(String jmeno, String prijmeni, String telefon, String typ)
    {
        this.jmeno = jmeno;
        this.prijmeni = prijmeni;
        this.telefon = telefon;
        this.typ = typ;
    }
    
    @Override
    public String toString()
    {
        return jmeno + " " + prijmeni + " " + telefon + " " + typ ;
    }
}


public class Program {

    static String text = "Toto je priklad nejakeho textu, no a co ma byt?";
    
    static ArrayList<Kontakt> kontakty = new ArrayList<>();
    
    public static void priprava(ArrayList<Kontakt> kontakty)
    {
        kontakty.add(new Kontakt("jan", "novak", "123456", "soukromy"));
        kontakty.add(new Kontakt("tomas", "novotny", "654321", "pracovni"));
        kontakty.add(new Kontakt("ivan", "hajek", "456789", "soukromy"));
    }
    
    static long pocetSlov(String text)
    {
        String pole[] = text.split("\\s+");
        //Stream proud = Stream.of(pole);
        //proud = proud.filter((String w)->w.length() == 2);
        //return proud.count();
        return Stream.of(pole).filter(w->w.length()==2).count();
    }
    
    static String[] nactiARozlozNaSlova( String jmenoSouboru) throws FileNotFoundException
    {
        BufferedReader br = new BufferedReader(new FileReader(jmenoSouboru));
        return br.lines()
                .reduce("", (vysledek, slovo)->vysledek + " " + slovo)
                .split("\\s+");
    }
    
    
    static void vypis (Collection kolekce)
    {
        kolekce.stream().forEach((k)->System.out.println(k));
    }
    
    static int faktorial(int n)
    {
     
        return 0;
    }
    
    
    public static void main(String[] args) throws FileNotFoundException {
       // System.out.println(pocetSlov(text));      
      // String []pole = nactiARozlozNaSlova("data.dta");
      
      
       
       /*priprava(kontakty);
       vypis(kontakty);
      kontakty.stream().filter(k->k.typ.equals("soukromy")).forEach(k->k.telefon="2"+k.telefon);
       //kontakty.stream().forEach(k->System.out.println(k));
       vypis(kontakty);*/
       
      /* Stream<Double> nahodna = Stream.generate(Math::random);
       Stream<Integer> posloupnost = Stream.iterate(0, n->n+1);
       Stream.iterate(0, n->n+1).skip(5).limit(15).filter(n->n%2 == 0).forEach(n->System.out.println(n));*/
       
       /*Stream<Integer> proud1 = Stream.iterate(0, n->n+1).skip(5).limit(6);
       Stream<Integer> proud2 = Stream.iterate(0, n->n+1).skip(20).limit(4);
       Stream<Integer> proud3 = Stream.concat(proud1, proud2);
       proud3.forEach(n->System.out.println(n));*/
       
       /*//tohle nebude fungovat
       Stream<Integer> proud = Stream.iterate(0, n->n+1);
       Stream<Integer> proud1 = proud.skip(5).limit(5);
       Stream<Integer> proud2 = proud.skip(20).limit(5);
       Stream<Integer> proud3 = Stream.concat(proud1, proud2);
       proud3.forEach(n->System.out.println(n));
       */
       
       //Stream<Integer> proud1 = Stream.iterate(0, n->n+1).skip(5).limit(6);
       //proud1.map(n->n*n).forEach(n->System.out.println(n));
       
       
       //IntStream.of(3,9,2,5,7,6,1,5,7,3).distinct().sorted().forEach(n->System.out.println(n));
       //IntStream.of(3,9,2,5,7,6,1,5,7,3).parallel().forEachOrdered(n->System.out.println(n));
       
       //System.out.println(faktorial(5));
       //Integer[] pole = (Integer[])Stream.of(1,2,3,5,8).toArray();
       
       //List<String> seznam = Stream.of("ahoj", "nazdar", "lidi", "jak").collect(Collectors.toList());
       
       Map<String, List<Kontakt>> kontaktyPodleTypu = 
               kontakty.stream().collect(Collectors.groupingBy(k->k.typ));
        
        
            
       
    }
    
}
