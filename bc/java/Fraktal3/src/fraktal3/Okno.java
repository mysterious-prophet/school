/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fraktal3;


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
        
        this.setLayout(new BorderLayout());
        
        //Nabidka
        this.add(hlavniNabidka, BorderLayout.NORTH);
        //this.add()
        
        hlavniNabidka.add(menuObrazek);
        hlavniNabidka.add(menuNastaveni);
        hlavniNabidka.add(menuNapoveda);
        
        menuObrazek.add(menuNakresli);
        menuObrazek.add(menuNovy);
        menuObrazek.add(menuUloz);
        menuObrazek.addSeparator();
        menuObrazek.add(menuKonec);
        
        menuNastaveni.add(menuUpravit);
        menuNastaveni.add(menuObnovit);
        
        menuNapoveda.add(menuOProgramu);
        
        menuNakresli.addActionListener(Neimplementovano::neimplementovano);
        menuOProgramu.addActionListener(this::oknoOProgramu);
        
    }
    
    private void konec(WindowEvent e)
    {
        System.exit(0);
    }
    
    
    public void nakresli(ActionEvent e)
    {
        this.nakresleno = true;
        repaint();
    }
    
    public boolean isNakresleno()
    {
        return this.nakresleno;
    }
    
   
    
    private void oknoOProgramu(ActionEvent e)
    {
        JOptionPane.showMessageDialog(rootPane, "Program na kresleni fraktalu \n(c) ", "Fraktalnik 0.1", JOptionPane.INFORMATION_MESSAGE);
    }
    
    
    JMenuBar hlavniNabidka = new JMenuBar();
    JMenu menuObrazek = new JMenu("Obrazek");
    JMenu menuNastaveni = new JMenu("Nastaveni");
    JMenu menuNapoveda = new JMenu("Napoveda");
    
    JMenuItem menuNakresli = new JMenuItem("Nakreslit");
    JMenuItem menuNovy = new JMenuItem("Novy");
    JMenuItem menuUloz = new JMenuItem("Ulozit...");
    JMenuItem menuKonec = new JMenuItem("Konec");
    
    JMenuItem menuUpravit = new JMenuItem("Upravit");
    JMenuItem menuObnovit = new JMenuItem("Obnovit");
    
    JMenuItem menuOProgramu = new JMenuItem("O programu");
    
    
    private final int sirkaOkna = 400;
    private final int vyskaOkna = 300;
    
    private boolean nakresleno = false;
    
}

class KresliciPanel extends JPanel{
    private Okno okno;
    public KresliciPanel(Okno okno)
    {
        this.okno = okno;
    }
    
    //@Override
    public void paintComponent(Graphics grafika){
        super.paintComponent(grafika);
        if(okno.isNakresleno())
        grafika.drawLine(0, 0, 100, 100);
    }
}


