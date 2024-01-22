#include <iostream>
using namespace std;

class pole
{
	int *p;
	int velikost;
public:
	explicit pole(int n) : velikost(n), p(new int[n]) {}
};

class Numero
{
	int n;
	static int poèet;
public:
	int hodnota() const;
	int hodnota();
	static int poèet_numer();
	Numero(int n = 0)
	{
		this->n = n; poèet++;
	}
	~Numero()
	{
		poèet--;
	}
	//Numero() = default;
	Numero(const Numero& n) :Numero(n.n) { };
	//Numero& operator=(Numero&) = delete;
	Numero operator+(Numero a)
	{
		return n + a.n;
	}
	//Numero operator+(Numero& n) &;
	//Numero operator+(Numero& n) &&;
	//Numero operator+(Numero&& n) &;
	//Numero operator+(Numero&& n) && ;
private:
	//Numero& operator=(Numero&);
};

int Numero::poèet = 0;

int Numero::hodnota() const
{
	cout << "hodnota konstanty" << endl;
	cout << poèet << endl;
	return n;
}

int Numero::hodnota() 
{
	cout << "hodnota nekonstanty" << endl;
	return n;
}

int Numero::poèet_numer()
{
	return poèet;
}

int main()
{
	Numero x, y;
	cout << Numero::poèet_numer() << endl;
	auto z = x + y; // z = x.operator+(y);
	cout << x.hodnota() << endl;
	const Numero n(9);
	cout << n.hodnota() << endl;
	cout << Numero::poèet_numer() << endl;
	x = y;
	//int a = 5;
	//pole p(6);
	//p = (pole)a;

}