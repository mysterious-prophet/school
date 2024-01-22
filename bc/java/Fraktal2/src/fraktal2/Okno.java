/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fraktal2;


import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Okno  extends JFrame {
    
    public Okno(){
        init();
    }
    
    private void init()
    {
        Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
        this.setBounds((dim.width-sirkaOkna)/2, (dim.height-vyskaOkna)/2, sirkaOkna, vyskaOkna);
        
        addWindowListener(new WindowAdapter()
        {
            public @Override void windowClosing(WindowEvent e){konec(e);}
        });
        
        setTitle("Fraktalnik");
    }
    
    private void konec(WindowEvent e)
    {
        System.exit(0);
    }
    
    
    JMenuBar hlavniNabidka = new JMenuBar();
    
    
    private final int sirkaOkna = 400;
    private final int vyskaOkna = 300;
    
}
