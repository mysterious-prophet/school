#include <iostream>
#include "seznam.h"

using namespace std;

class X
{
public:
	X() { cout << "bezparametrick�" << endl; }
	X(X& x) { cout << "kop�rovac�" << endl; }
	X(X&& x){ cout << "st�hovac�" << endl; }
	~X() { cout << "destruktor" << endl; }
};

std::ostream& operator<<(std::ostream& proud, X& x)
{
	return proud << "x";
}

template<class Iter�tor>
void v�pis(Iter�tor it1, Iter�tor it2)
{
	for (Iter�tor it = it1; it != it2; it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

template<class T>
void v�pis(T sezn)
{
	v�pis(sezn.begin(), sezn.end());
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
	v�pis(e);
	//v�pis( move(a) + move(b));
	//e = (a + b) + (c + d);
	//a += move(b);
}