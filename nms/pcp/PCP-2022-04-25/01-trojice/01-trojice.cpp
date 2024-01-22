#include <iostream>
#include <ranges>
#include <algorithm>


using namespace std;
namespace rv = std::ranges::views;

struct trojice
{
	int a, b, c;
	static const trojice v�choz�;
};

const trojice trojice::v�choz�{ 3, 2, 1 };

trojice& operator++(trojice& dan�_trojice)
{
	if (dan�_trojice.c < dan�_trojice.b - 1)
	{
		dan�_trojice.c++;
	}
	else if (dan�_trojice.b < dan�_trojice.a - 1)
	{
		dan�_trojice.b++;
		dan�_trojice.c = 1;
	}
	else
	{
		dan�_trojice.a++;
		dan�_trojice.b = 2;
		dan�_trojice.c = 1;
	}
	return dan�_trojice;
}

trojice operator++(trojice & dan�_trojice, int)
{
	auto v�sledek = dan�_trojice;
	++dan�_trojice;
	return v�sledek;
}

ostream& operator<<(ostream& proud, const trojice& dan�_trojice)
{
	return proud << "(" << dan�_trojice.a << ", " << dan�_trojice.b << ", " << dan�_trojice.c << ")";
}

auto dvojmoc(auto n)
{
	return n * n;
}

bool je_pythagorejsk�(trojice dan�_trojice)
{
	auto& [a, b, c] = dan�_trojice;
	return dvojmoc(a) == dvojmoc(b) + dvojmoc(c);
}

/* 
// Tato konstrukce nefunguje spr�vn�
trojice pomocn�_trojice = trojice::v�choz�;

auto int_na_trojici(int i)
{
	return pomocn�_trojice++;
}
*/

// hloup�, ale funguje
auto int_na_trojici(int n)
{
	auto v�sledek = trojice::v�choz�;
	for (int j = 1; j < n; j++)
	{
		++v�sledek;
	}
	return v�sledek;
}

// Nepot�ebujeme, ale slou�ilo k hled�n� chyby
constexpr void iota(forward_iterator auto prvn�, forward_iterator auto posledn�, auto hodnota)
{
	while (prvn� != posledn�)
	{
		*prvn�++ = hodnota;
		++hodnota;
	}
}

template<ranges::range Rozsah, class T>
constexpr void iota(Rozsah&& rozsah, T hodnota)
{
	iota(begin(rozsah), end(rozsah), hodnota);
}



void vypi�(ranges::range auto rozsah)
{
	ranges::for_each(rozsah, [](auto x) {cout << x << endl; });
}

int main()
{
	vypi�(views::iota(1) | rv::transform(int_na_trojici) | rv::filter(je_pythagorejsk�) | rv::take(10));
} 