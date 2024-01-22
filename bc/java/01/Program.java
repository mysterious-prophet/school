/**
komentar
*/


public class Program //stejne jmeno jako program
{
	public static void main(String[] arg)
	{
		System.out.println("Hello, world");
		System.out.println(Pomoc(5));
	}
}

class Pomoc
{
	public static int faktorial(int n)
	{
		int vysledek = 1;
		while(n>1) vysledek *=n--;
		return vysledek;
	}
}