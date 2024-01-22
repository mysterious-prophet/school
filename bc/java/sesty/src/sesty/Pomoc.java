/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sesty;

/**
 *
 * @author pokorm20
 */
public class Pomoc {
    public static <T extends Comparable & java.io.Serializable> T max(T a, T b)
    {
        return a.compareTo(b) < 0 ? b : a;
    }
    
    public static void tisk(java.util.Collection<? super Object> c)
    {
        java.util.Iterator it = c.iterator();
        while(it.hasNext())
        {
            System.out.println(it.next());
        }
    }
    
}
