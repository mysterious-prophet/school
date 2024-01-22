
package blikani;


public class Prepinac implements Runnable {

    @Override
    public void run() {
        for(;;)
        {
            try{
                Program.blikac.prepni();
                Thread.sleep(10);
            } catch(InterruptedException ex){
               
            }
        }
    }
    
}
