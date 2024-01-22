#include <iostream>
using namespace std;

template<int N>
concept sud� = N % 2 == 0;

template<int N> requires sud�<N>
void f()
{
	cout << "f: " << N << " je sud�" << endl;
}

template<int N> requires (!sud�<N>)
void f()
{
	cout << "f: " << N << " je lich�" << endl;
}

template<int N> requires (N % 2 == 0)
void g()
{
	cout << "g: " << N << " je sud�" << endl;
}

template<int N> requires (N % 2 != 0)
void g()
{
	cout << "g: " << N << " je lich�" << endl;
}

//template<sud� N>  // Nelze
//void h()
//{}

int main()
{
	f<2>();
	f<3>();
	g<4>();
	g<5>();
}