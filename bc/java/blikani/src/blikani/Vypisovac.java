/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blikani;

import java.util.Random;

public class Vypisovac implements Runnable {

    private Random generator = new Random();
    private String minule = "";
    
    @Override
    public void run() {
    
        try
        {
            for(;;)
            {
                String text = Program.blikac.getData();
                if(!text.equals(minule))
                {
                    System.out.println(text);
                    minule = text;
                    int hodnota = Math.abs(generator.nextInt() % 11);
                    Thread.sleep(hodnota);
                }
            }
        }
        catch(InterruptedException e)
        {
            //
        }
    }
    
}
