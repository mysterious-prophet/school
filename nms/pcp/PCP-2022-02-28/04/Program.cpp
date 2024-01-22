// Redukce balíku

//(balík @ ...) unární pravá redukce (E @ ...) -> E1 @  ... @(En-1 @ En)...)
//(... @ balík) unární levá redukce  (...(E1 @ E2) @ ... ) @ En
//(balík @ ... @ init)  binární pravá E1 @ (... En-1 @ (En @ Init )...)
//(init @ ... @ balík) binární levá  (....(init @ E1) @ ....) @ En

#include <iostream>
using namespace std;

template<typename ... T>
auto souèet_parametrù(T ... param)
{
	return (... + param);
}

template<typename ... Param>
void tisk(Param&& ... param)
{
	(cout << ... << param) << endl;
}

// Souèin hodnot z balíku
template <size_t ... numera>
constexpr size_t souèin(index_sequence<numera...>)
{
	return ((numera + 1) * ...);
}

template<size_t N>
constexpr size_t faktoriál()
{
	return souèin(make_index_sequence<N>{});
}

// Formátovaný tisk 
// Tato funkce zastaví rekurzi
void tprintf(const char *formát)
{
	cout << formát;
}

template<class T, class ... typy>
void tprintf(const char *formát, T hodnota, typy ... param)
{
	for (; *formát != '\0'; formát++)
	{
		if (*formát == '%')
		{
			cout << hodnota;
			tprintf(formát + 1, param...);
			return;
		}
		cout << *formát;
	}
}

template<typename T, typename ... typy>
void vytiskni(std::ostream& proud, T const& první, typy const& ... zbytek)
{
	cout << první;
	if constexpr(sizeof...(zbytek) > 0)
	{
		vytiskni(proud, zbytek...);
	}
	cout << endl;
}

int main()
{
	int a = 2;
	cout << souèet_parametrù(1, 2, 3, a) << endl;
	tisk(1, 2, 3, "abc");
	int A[faktoriál<3>()]{};

	tprintf("Byla tam % lidí a % psù.", 10, 12);
	vytiskni(cout, 1, "pozdravuji");
}
