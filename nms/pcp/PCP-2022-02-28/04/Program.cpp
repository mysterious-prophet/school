// Redukce bal�ku

//(bal�k @ ...) un�rn� prav� redukce (E @ ...) -> E1 @  ... @(En-1 @ En)...)
//(... @ bal�k) un�rn� lev� redukce  (...(E1 @ E2) @ ... ) @ En
//(bal�k @ ... @ init)  bin�rn� prav� E1 @ (... En-1 @ (En @ Init )...)
//(init @ ... @ bal�k) bin�rn� lev�  (....(init @ E1) @ ....) @ En

#include <iostream>
using namespace std;

template<typename ... T>
auto sou�et_parametr�(T ... param)
{
	return (... + param);
}

template<typename ... Param>
void tisk(Param&& ... param)
{
	(cout << ... << param) << endl;
}

// Sou�in hodnot z bal�ku
template <size_t ... numera>
constexpr size_t sou�in(index_sequence<numera...>)
{
	return ((numera + 1) * ...);
}

template<size_t N>
constexpr size_t faktori�l()
{
	return sou�in(make_index_sequence<N>{});
}

// Form�tovan� tisk 
// Tato funkce zastav� rekurzi
void tprintf(const char *form�t)
{
	cout << form�t;
}

template<class T, class ... typy>
void tprintf(const char *form�t, T hodnota, typy ... param)
{
	for (; *form�t != '\0'; form�t++)
	{
		if (*form�t == '%')
		{
			cout << hodnota;
			tprintf(form�t + 1, param...);
			return;
		}
		cout << *form�t;
	}
}

template<typename T, typename ... typy>
void vytiskni(std::ostream& proud, T const& prvn�, typy const& ... zbytek)
{
	cout << prvn�;
	if constexpr(sizeof...(zbytek) > 0)
	{
		vytiskni(proud, zbytek...);
	}
	cout << endl;
}

int main()
{
	int a = 2;
	cout << sou�et_parametr�(1, 2, 3, a) << endl;
	tisk(1, 2, 3, "abc");
	int A[faktori�l<3>()]{};

	tprintf("Byla tam % lid� a % ps�.", 10, 12);
	vytiskni(cout, 1, "pozdravuji");
}
