#include <iostream>
#include <ranges>
#include <algorithm>


using namespace std;
namespace rv = std::ranges::views;

struct trojice
{
	int a, b, c;
	static const trojice výchozí;
};

const trojice trojice::výchozí{ 3, 2, 1 };

trojice& operator++(trojice& daná_trojice)
{
	if (daná_trojice.c < daná_trojice.b - 1)
	{
		daná_trojice.c++;
	}
	else if (daná_trojice.b < daná_trojice.a - 1)
	{
		daná_trojice.b++;
		daná_trojice.c = 1;
	}
	else
	{
		daná_trojice.a++;
		daná_trojice.b = 2;
		daná_trojice.c = 1;
	}
	return daná_trojice;
}

trojice operator++(trojice & daná_trojice, int)
{
	auto výsledek = daná_trojice;
	++daná_trojice;
	return výsledek;
}

ostream& operator<<(ostream& proud, const trojice& daná_trojice)
{
	return proud << "(" << daná_trojice.a << ", " << daná_trojice.b << ", " << daná_trojice.c << ")";
}

auto dvojmoc(auto n)
{
	return n * n;
}

bool je_pythagorejská(trojice daná_trojice)
{
	auto& [a, b, c] = daná_trojice;
	return dvojmoc(a) == dvojmoc(b) + dvojmoc(c);
}

/* 
// Tato konstrukce nefunguje správnì
trojice pomocná_trojice = trojice::výchozí;

auto int_na_trojici(int i)
{
	return pomocná_trojice++;
}
*/

// hloupé, ale funguje
auto int_na_trojici(int n)
{
	auto výsledek = trojice::výchozí;
	for (int j = 1; j < n; j++)
	{
		++výsledek;
	}
	return výsledek;
}

// Nepotøebujeme, ale sloužilo k hledání chyby
constexpr void iota(forward_iterator auto první, forward_iterator auto poslední, auto hodnota)
{
	while (první != poslední)
	{
		*první++ = hodnota;
		++hodnota;
	}
}

template<ranges::range Rozsah, class T>
constexpr void iota(Rozsah&& rozsah, T hodnota)
{
	iota(begin(rozsah), end(rozsah), hodnota);
}



void vypiš(ranges::range auto rozsah)
{
	ranges::for_each(rozsah, [](auto x) {cout << x << endl; });
}

int main()
{
	vypiš(views::iota(1) | rv::transform(int_na_trojici) | rv::filter(je_pythagorejská) | rv::take(10));
} 