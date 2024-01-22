// Odvození balíku parametrù: výpoèet faktoriálu v dobì pøekladu
#include <iostream>
#include <type_traits>

using namespace std;

template<size_t ... data>
constexpr size_t souèin(std::index_sequence<data...>)
{
	return ((data + 1) * ...);
}

template<size_t N>
constexpr size_t faktoriál()
{
	return souèin(make_index_sequence<N>{});
}

int main()
{
	auto y = souèin(index_sequence<2, 2, 2>{});
	cout << y << endl;
	int A[faktoriál<3>()];
}