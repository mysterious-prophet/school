class Pomoc
{
	public static int faktorial(int n)
	{
		int vysledek = 1;
		while(n>1) vysledek *=n--;
		return vysledek;
	}
}
