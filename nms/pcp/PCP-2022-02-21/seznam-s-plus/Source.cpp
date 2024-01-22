#include <iostream>
#include "seznam.h"

using namespace std;

class X
{
public:
	X() { cout << "bezparametrický" << endl; }
	X(X& x) { cout << "kopírovací" << endl; }
	X(X&& x){ cout << "stìhovací" << endl; }
	~X() { cout << "destruktor" << endl; }
};

std::ostream& operator<<(std::ostream& proud, X& x)
{
	return proud << "x";
}

template<class Iterátor>
void výpis(Iterátor it1, Iterátor it2)
{
	for (Iterátor it = it1; it != it2; it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

template<class T>
void výpis(T sezn)
{
	výpis(sezn.begin(), sezn.end());
}

int main()
{
	seznam<int> a{ 1,2 };
	seznam<int> b{ 3,4 };
	seznam<int> c{ 5,6 };
	seznam<int> d{ 7,8 };
	seznam<int> e;
	//e = move(a) + b;
	a += move(b);
	výpis(e);
	//výpis( move(a) + move(b));
	//e = (a + b) + (c + d);
	//a += move(b);
}