#include <iostream>
using namespace std;

template<class T>
concept má_bar_c = requires(T a)
{
	{T::bar};
	//typename T::typ;
}  && same_as<int, T>; // ???

struct X { int bar; using typ = int; };


int main()
{
	cout << boolalpha;
	cout << má_bar_c<X> << endl;
}
