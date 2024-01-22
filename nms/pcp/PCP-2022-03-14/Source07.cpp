#include <iostream>
#include <stdlib.h>

using namespace std;

template<typename T>
struct Báze
{
	void metoda()
	{
		(static_cast<T*>(this))->metoda();
	}
};

struct PrvníOdvozená : public Báze<PrvníOdvozená>
{
	void metoda()
	{
		cout << "Metoda v první odvozené" << endl;
	}
};

struct DruháOdvozená : public Báze<DruháOdvozená>
{
	void metoda()
	{
		cout << "Metoda ve druhé odvozené" << endl;
	}
};

struct TøetíOdvozená : public DruháOdvozená
{
	void metoda()
	{
		cout << "Metoda ve tøetí odvozené" << endl;
	}
};

template<typename T>
void zpracuj(Báze<T>* b)
{
	b->metoda();
}

int main()
{
	PrvníOdvozená d1;
	DruháOdvozená d2;
	TøetíOdvozená d3;
	zpracuj(&d1);
	zpracuj(&d2);
	zpracuj(&d3);
}