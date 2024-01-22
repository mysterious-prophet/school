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


int main()
{
	/*seznam<int> s0{ 1,3,5 };
	s0.vlož_na_konec(7);
	s0.odstraò_první();
	s0.vlož_na_zaèátek(8);
	s0.vypiš();*/
	/*seznam<int*> s1;
	s1.vlož_na_zaèátek(new int{ 8 });
	s1.vypiš();*/

	/*seznam<X*> s3;
	s3.vlož_na_zaèátek(new X);
	s3.vypiš();*/

	/*seznam<int> s4{ 1,2,3 };
	seznam<int> s5(s4);
	s4.vlož_na_konec(9);
	s5.vypiš();
	s4.vypiš();*/
	seznam<int> si1{ 1,3,5 };
	/*seznam<int> si2(move(si1));
	seznam<int> si3;
	si3 = move(si2);*/
	auto it = si1.najdi(1);
	auto beg = si1.begin();
	auto kon = si1.end();
	bool b = beg == kon;
	it++;
	/*for (
		auto i = si1.begin(); 
		i != si1.end(); 
		i++)
	{
		cout << *i << endl;
	}*/
	for(auto i: si1)
		cout << i << endl;
}