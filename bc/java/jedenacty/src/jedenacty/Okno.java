/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jedenacty;

/**
 *
 * @author pokorm20
 */

import javax.swing.*;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;

public class Okno extends JFrame{
    public Okno()
    {
        init();
    }
    
    private void init()
    {
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setBounds(100,100,300,200);
        setTitle("Prvni okno");       
        setLayout(null);
        
        this.addWindowListener(new WindowAdapter()
        {
            @Override
            public void windowClosing(java.awt.event.WindowEvent e){
                stiskTlacitka(null);
            }
        }
        );
        
        
        //tl stop
        tlacitkoStop.setBounds(10,10,100,30);
        //tlacitkoStop.addActionListener(e->{System.exit(0);});
        tlacitkoStop.addActionListener(this::stiskTlacitka);
        add(tlacitkoStop); //center bude na cele okno
        /*tlacitkoStop.addActionListener(
                new ActionListerner() {
                    @Override
                    public void actionPerformed(ActionEvent e){
                        System.exit(0);    
                    }
                }
        
        */
        //add(tlacitko2, BorderLayout.WEST);
        //add(tlacitko3, BorderLayout.NORTH);
        //add(tlacitko4, BorderLayout.EAST);
        //add(tlacitko5, BorderLayout.SOUTH);
//tl stop
    }
    
    void stiskTlacitka(ActionEvent e)
    {
        System.exit(0);
    }
    
    
    //BorderLayout layout = new BorderLayout();
    //FlowLayout layout = new FlowLayout();
    
    GridLayout layout = new GridLayout(3,2, 10, 20); //radky sloupce mezery
    
    private JButton tlacitkoStop = new JButton("konec");
    private JButton tlacitko2 = new JButton("2");
    private JButton tlacitko3 = new JButton("3");
    private JButton tlacitko4 = new JButton("4");
    private JButton tlacitko5 = new JButton("5");
}
