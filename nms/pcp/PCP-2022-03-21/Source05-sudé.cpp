#include <iostream>
using namespace std;

template<int N>
concept sud� = N % 2 == 0;

template<int N>
concept lich� = !sud�<N>;

template<int N> requires sud�<N>
void f()
{
	cout << "f: " << N << " je sud�" << endl;
}

template<int N> requires lich�<N>
void f()
{
	cout << "f: " << N << " je lich�" << endl;
}

int main()
{
	f<2>();
	f<3>();
}