#include <iostream>
using namespace std;

template<int N>
concept sudé = N % 2 == 0;

template<int N>
concept liché = !sudé<N>;

template<int N> requires sudé<N>
void f()
{
	cout << "f: " << N << " je sudé" << endl;
}

template<int N> requires liché<N>
void f()
{
	cout << "f: " << N << " je liché" << endl;
}

int main()
{
	f<2>();
	f<3>();
}