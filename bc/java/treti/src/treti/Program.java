/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package treti;

//import java.util.ArrayList;
import java.util.*;

class X()

/**
 *
 * @author pokorm20
 */
public class Program {
    
    static void f(Object n) //Integer dedi z Object
    {
        System.out.println((int)n+1); //n+1 nelze
    }

    /**
     * @param args the command line arguments
     * 
     * 
     * 
     */
    
    static void pozdrav(int i)
    {
        switch(i)
        {
            case 1:
                System.out.println("yo");
                break;
            case 2:
                System.out.println("heyy");
                break;
            default:
                System.out.println("hi");
        }
    }
    
    static int i = 0;
    static ArrayList<Integer> data = new ArrayList<>();
    
    public static int faktorial(int n)
    {
        
        if(n<0) throw new Exception("Zaporny parametr faktorialu");
        int vysl = 1;
        for(int i = 2; i<=n; i++)
        {
            vysl *= i;
        }
        return vysl;
    }
    public static void main(String[] args) {
        // TODO code application logic here
        
        //integer i;
        //Integer i = new Integer(6);
       // f(i);
        //f(9);
        
        //X x  = new X();
        //f(x);
        
        //long n = 9L; //9Long
        
        //String s = "12";
        //int y = Integer.parseInt(s);
        //f(y);
        
        //char c = '\u00E1';
        //System.out.println(c);
        //Character h = new Character(c);
        //int j = c;
        
        //String t = "Ahoj";
        //Boolean b = Boolean.parseBoolean(t);
        //double d = Double.parseDouble(t);
        
        //int[] A, B;
       // A = new int[]{1,4,7};
        //A[5]=8;
        //System.out.print(A);
        
        /*for(int k : A)
        {
            System.out.print(i);
        }*/
        
        //int C[][] = {1,3,5},{8,7,6};
        //C = new int [3][4];
        
        /*data.add(4);
        data.add(8);
        for( int i:data)
        {
            System.out.println(i);
        }*/
        
        /*vnejsi:
        for(int i=0; i<5; i++)
            for(int j = 0; j<10; j++)
            {
                System.out.println(i+j);
                if(i+j == 8)
                {
                    break vnejsi;
                }
            }
        */
        
        try(Scanner vstup = new Scanner(System.in);)
        {
            //System.out.println("zadej cele cislo:");
            //Scanner vstup = new Scanner(System.in);
            int n = vstup.nextInt();
            System.out.println(faktorial(n));
            System.out.println("podpis"); //tohle se nevypise kdyz faktorial hodi vyjimku
        }
        catch(Exception e)
        {
            System.out.println(e.getMessage());
        }
        finally //kvuli tomu finally
        {
            System.out.println("podpis");
        }
        
    }
    
}
