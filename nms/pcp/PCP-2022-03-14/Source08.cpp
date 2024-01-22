#include <iostream>
using namespace std;

template<class T>
struct rovnost
{
	friend
	bool operator==(T a, T b) { return a.rovno(b); }
	//friend bool operator !=(T a, T b) { return !a.rovno(b); }
};

class Numero : public rovnost<Numero>
{
	int n;
public:
	Numero(int n) : n(n) {}
	bool rovno(Numero a)
	{
		return n == a.n;
	}
};

int main()
{
	Numero n1(8);
	Numero n2(7);
	if (n1 != n2)
	{
		cout << "rùzné" << endl;
	}
}
