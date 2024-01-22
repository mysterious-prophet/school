
package reflexe;

import java.lang.reflect.*;

//class X{};
//class Y extends X{};

public class Program {

    
    /*public static void detekce(Object obj)
    {
        if (obj instanceof String)
        {
            System.out.println("je to tak");
        }
        else
        {
            System.out.println("ne");
        }
    }*/
    
    public static void main(String[] args) throws ReflectiveOperationException {// NoSuchMethodException, ClassNotFoundException, InstantiationException, IllegalAccessException, IllegalArgumentException, InvocationTargetException {
        //detekce("haha");
        //detekce(new Y());
        
        Class c = Class.forName("reflexe.Pokus"); 
        Constructor konstruktor = c.getConstructor(int.class);
        Rozhrani obj = (Rozhrani)konstruktor.newInstance(5);
        obj.metoda();
        
        
        Method metoda = c.getMethod("nasobek", int.class);       
        int y = (int)metoda.invoke(obj, 7);
        System.out.println(y);
        
        
     
    }
    
}
