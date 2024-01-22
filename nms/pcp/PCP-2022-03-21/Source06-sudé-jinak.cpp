#include <iostream>
using namespace std;

template<int N>
concept sudé = N % 2 == 0;

template<int N> requires sudé<N>
void f()
{
	cout << "f: " << N << " je sudé" << endl;
}

template<int N> requires (!sudé<N>)
void f()
{
	cout << "f: " << N << " je liché" << endl;
}

template<int N> requires (N % 2 == 0)
void g()
{
	cout << "g: " << N << " je sudé" << endl;
}

template<int N> requires (N % 2 != 0)
void g()
{
	cout << "g: " << N << " je liché" << endl;
}

//template<sudé N>  // Nelze
//void h()
//{}

int main()
{
	f<2>();
	f<3>();
	g<4>();
	g<5>();
}