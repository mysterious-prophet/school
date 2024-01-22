#include <iostream>
using namespace std;

template<class T>
concept m�_bar_c = requires(T a)
{
	{T::bar};
	//typename T::typ;
}  && same_as<int, T>; // ???

struct X { int bar; using typ = int; };


int main()
{
	cout << boolalpha;
	cout << m�_bar_c<X> << endl;
}
