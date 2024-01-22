#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
struct B�ze
{
	void metoda()
	{
		(static_cast<T*>(this))->metoda();
	}
};

struct Prvn�Odvozen� : public B�ze<Prvn�Odvozen�>
{
	void metoda()
	{
		cout << "Metoda v prvn� odvozen�" << endl;
	}
};

struct Druh�Odvozen� : public B�ze<Druh�Odvozen�>
{
	void metoda()
	{
		cout << "Metoda ve druh� odvozen�" << endl;
	}
};

struct T�et�Odvozen� : public Druh�Odvozen�
{
	void metoda()
	{
		cout << "Metoda ve t�et� odvozen�" << endl;
	}
};

template<typename T>
void zpracuj(B�ze<T>* b)
{
	b->metoda();
}

int main()
{
	Prvn�Odvozen� d1;
	Druh�Odvozen� d2;
	T�et�Odvozen� d3;
	zpracuj(&d1);
	zpracuj(&d2);
	zpracuj(&d3);
}