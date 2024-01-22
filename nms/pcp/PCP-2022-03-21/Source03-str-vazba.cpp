#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <tuple>
#include <type_traits>

using namespace std;

class komplex
{
	double x;
	double y;
public:
	komplex(double x, double y) : x(x), y(y) {}
	double& Re() { return x; }
	double& Im() { return y; }
};

template<>
class tuple_size<komplex> : public integral_constant<size_t, 2> {};

template<size_t I>
class tuple_element<I, komplex>
{
	using type = double;
};

template<int N>
double& get(komplex& z)
{
	if constexpr (N == 0)
	{
		return z.Re();
	}
	else
	{
		return z.Im();
	}
}

struct bod
{
	double x, y, z;
};

map<int, string> pozdravy()
{
	return
	{
		{1, "Nazdar"}, {2, "Ahoj"},{3, "Poklona"}, {4, "Èau"}
	};
}



int main()
{
	pair pár{ 6.6, 7 };
	komplex z(2, 4);
	auto& [x, y] = z;
	x = 9;
	bod B{ 4,6,9 };
	auto& [a, b, _] = B;
	system("CHCP 1250 > NUL");
	for (auto&& [klíè, hodnota] : pozdravy())
	{
		cout << "Pozdrav èíslo " << klíè << " je " << hodnota << endl;
	}
}