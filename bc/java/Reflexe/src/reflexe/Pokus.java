
package reflexe;

public class Pokus implements Rozhrani{
    int n;
    public Pokus(int n)
    {
        this.n=n;
    }
    public Pokus()
    {
        this(99);
    }
    public int nasobek(int m)
    {
        return m*n;
    }
    
    static
    {
        System.out.println("zavedeno do pameti");
    }
    
    @Override
    public void metoda()
    {
        System.out.println("volana metoda rozhrani");
    }
    
}
