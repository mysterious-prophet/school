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


int main()
{
	/*seznam<int> s0{ 1,3,5 };
	s0.vlo�_na_konec(7);
	s0.odstra�_prvn�();
	s0.vlo�_na_za��tek(8);
	s0.vypi�();*/
	/*seznam<int*> s1;
	s1.vlo�_na_za��tek(new int{ 8 });
	s1.vypi�();*/

	/*seznam<X*> s3;
	s3.vlo�_na_za��tek(new X);
	s3.vypi�();*/

	/*seznam<int> s4{ 1,2,3 };
	seznam<int> s5(s4);
	s4.vlo�_na_konec(9);
	s5.vypi�();
	s4.vypi�();*/
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