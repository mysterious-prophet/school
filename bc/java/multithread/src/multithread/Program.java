
package multithread;

import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

class Vers implements Runnable
{
    private String text;
    public Vers(String text)
    {
        this.text = text;
    }
    @Override
    public void run()
    {
        try{
        for(int i = 0; i<1000000; i++){
            System.out.println(text);        
            //Thread.yield();
            Thread.sleep(10);
        }
        } catch (InterruptedException ex){
            //Logger.getLogger(Vers.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}


public class Program {  
    public static void main(String[] args) throws InterruptedException, IOException {
        
        Thread vers1 = new Thread(new Vers("Kocka leze dirou"));
        Thread vers2 = new Thread(new Vers("Pes oknem"));
        
        //vers1.setDaemon(true);
        //vers2.setDaemon(true);
        
        vers1.setPriority(Thread.MAX_PRIORITY);
        vers2.setPriority(Thread.MIN_PRIORITY);
        
        vers1.start();
        vers2.start();
        
        //vers1.join();
       // vers2.join();
       
       System.in.read();
       vers1.interrupt();
       vers2.interrupt();
       
        
        System.out.println("Nebude-li prset nezmoknem");
        
    }
    
}
