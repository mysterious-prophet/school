#include <iostream>

using namespace std;

typedef double (*fce)(double);

void tabulka(fce f)
{
	cout << f(1.5) << endl;
}

template<auto N>
struct hodnota
{
	decltype(N) data = N;
};

template<class T, T N>
struct hodnota1
{
	T data = N;
};

template<auto ... hodnoty> struct seznam_hodnot {};

//template<auto V1, auto v2, ....> struct seznam_hodnot {};


int main()
{
	hodnota<6> hod;
	int a = 7;
	int b;
	tabulka([](double x) {return x * x; });
	
	auto f = [&, b](auto i)mutable constexpr  {return i * a++; };
	auto h = []<class T>(T a) {};
	auto g = [] {cout << "nazdar"<<endl;};
	auto x = f(8);
}