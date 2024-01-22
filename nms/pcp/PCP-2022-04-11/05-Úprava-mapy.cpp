#include <iostream>
#include <map>
#include <ranges>
#include <ctype.h>
#include <stdlib.h>
#include <string>

using namespace std;

std::multimap<int, char> vstup
{
	{4, 'Z'}, {3, 'D'}, {4, 'b'}, {5, 'e'}, {4, 'c'}
};

template<class T>
void uprav_hodnotu(T& hodnota)
{
	if (islower(hodnota))
	{
		hodnota = toupper(hodnota);
	}
}

template<class K, class H>
void uprav_znaky_v_map�(multimap<K, H> &mapa, K kl��)
{
	auto [prvn�, posledn�] = mapa.equal_range(kl��);
	for (auto& [_, hodnota] : std::ranges::subrange(prvn�, posledn�))
	{
		uprav_hodnotu(hodnota);
	}
}

void tisk(std::string_view koment��, auto const& mapa)
{
	cout << koment��;
	for (const auto& [k, v] : mapa)
	{
		cout << "{" << k << ", '" << v << "'}";
	}
	cout << '\n';
}

int main()
{
	tisk("na po��tku: "sv, vstup);
	uprav_znaky_v_map�(vstup, 4);
	tisk("Po �prav�: ", vstup);
}