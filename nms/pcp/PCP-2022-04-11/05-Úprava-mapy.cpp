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
void uprav_znaky_v_mapì(multimap<K, H> &mapa, K klíè)
{
	auto [první, poslední] = mapa.equal_range(klíè);
	for (auto& [_, hodnota] : std::ranges::subrange(první, poslední))
	{
		uprav_hodnotu(hodnota);
	}
}

void tisk(std::string_view komentáø, auto const& mapa)
{
	cout << komentáø;
	for (const auto& [k, v] : mapa)
	{
		cout << "{" << k << ", '" << v << "'}";
	}
	cout << '\n';
}

int main()
{
	tisk("na poèátku: "sv, vstup);
	uprav_znaky_v_mapì(vstup, 4);
	tisk("Po úpravì: ", vstup);
}