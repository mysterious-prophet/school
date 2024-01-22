
package blikani;

import java.io.IOException;


public class Program {

    public static Blikac blikac = new Blikac();
   
    public static void main(String[] args) throws IOException {
     
        Prepinac prepinac = new Prepinac();
        Vypisovac vypisovac = new Vypisovac();
        Thread prepinajici = new Thread(prepinac);
        Thread vypisujici = new Thread(vypisovac);
        vypisujici.setDaemon(true);
        prepinajici.setDaemon(true);
        
        System.out.println("enter ukonci progra");
        prepinajici.start();
        vypisujici.start();
        
        System.in.read();
        
        
    }
    
}
