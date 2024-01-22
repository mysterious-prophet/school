#ifndef __SEZNAM_IMPL_H__
#define __SEZNAM_IMPL_H__
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <iostream>

//using namespace std;

template<class T, template<class T> class Alokátor = std::allocator>
class seznam_impl
{
	struct prvek;
	template<class U = T>
	struct pomoc;
public:
	// Zveøejòované datové typy
	using typ_hodnot = T;
	// Konstruktory a destruktor
	seznam_impl();
	seznam_impl(std::initializer_list<T> seznam_inicializátorù);
	seznam_impl(const seznam_impl& si);
	seznam_impl(seznam_impl&& si);
	~seznam_impl();
	// Pøiøazování
	seznam_impl& operator=(seznam_impl& si);
	seznam_impl& operator=(seznam_impl&& si);
	// Stav seznamu
	std::size_t velikost() const noexcept { return poèet_prvkù; }
	bool prázdný() const noexcept { return hlava == zarážka; }
	// Pøístup k prvkùm
	typ_hodnot první();
	// Vkládání do seznamu
	void vlož_na_konec(T& co);
	void vlož_na_konec(T&& co);
	void vlož_na_zaèátek(T& co);
	void vlož_na_zaèátek(T&& co);
	// Odstraòování
	void odstraò_první();
	void vyprázdni();
	// Pro ladìní
	void vypiš();
	// Prohození obsahu dvou seznamù
	void prohoï(seznam_impl& s);
private:
	prvek *hlava, *zarážka;
	std::size_t poèet_prvkù;
	// Odlišné implementace nìkterých operací pro ukazatele
	pomoc<T> pomùcka;

	prvek *pøíprava_vložení();
	void pøikopíruj(const seznam_impl& s);
};

template<class T, template<class T> class Alokátor>
template<class U>
struct seznam_impl<T, Alokátor>::pomoc
{
	void vypiš_prvek(prvek *ten)
	{
		std::cout << ten->data << " ";
	}
	void odstraò_data(T) {}
};

template<class T, template<class T> class Alokátor>
template<class U>
struct seznam_impl<T, Alokátor>::pomoc<U*>
{
	void vypiš_prvek(prvek *ten)
	{
		std::cout << "*" << *(ten->data) << " ";
	}
	void odstraò_data(T tato_data) 
	{
		delete tato_data;
	}
};


template<class T, template<class T> class Alokátor>
struct seznam_impl<T, Alokátor>::prvek
{
	T data;
	prvek *další;
	static Alokátor<prvek> alokátor;

	prvek(T& data, prvek *další) :data(data), další(další) {}
	prvek(T&& data, prvek* další) : data(std::move(data)), další(další) {}

	void *operator new(std::size_t)
	{
		return alokátor.allocate(1);
	}

	void operator delete(void *p)
	{
		alokátor.deallocate((prvek*)p, 1);
	}
};

template<class T, template<class> class Alokátor>
Alokátor<typename seznam_impl<T, Alokátor>::prvek> seznam_impl<T, Alokátor>::prvek::alokátor;


template<class T, template<class> class Alokátor>
seznam_impl<T, Alokátor>::seznam_impl()
{
	hlava = zarážka = new prvek{ T{}, nullptr };
	poèet_prvkù = 0;
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor>::seznam_impl(std::initializer_list<T> seznam_inicializátorù)
	:seznam_impl()
{
	for (auto x : seznam_inicializátorù)
	{
		vlož_na_konec(x);
	}
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor>::seznam_impl(const seznam_impl<T, Alokátor>& si)
	: seznam_impl()
{
	pøikopíruj(si);
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor>::seznam_impl(seznam_impl<T, Alokátor>&& si)
	: seznam_impl()
{
	prohoï(si);
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor>::~seznam_impl()
{
	vyprázdni();
	delete hlava;
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor> & seznam_impl<T, Alokátor>::operator=(seznam_impl<T, Alokátor> & si)
{
	vyprázdni();
	pøikopíruj(si);
	return *this;
}

template<class T, template<class T> class Alokátor>
seznam_impl<T, Alokátor> & seznam_impl<T, Alokátor>::operator=(seznam_impl<T, Alokátor> && si)
{
	prohoï(si);
	return *this;
}

template<class T, template<class T> class Alokátor>
T seznam_impl<T, Alokátor>::první()
{
	if(prázdný)
	{
		throw std::out_of_range("Odstraòování z prázdného seznamu");
	}
	return hlava->data;
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_konec(T& co)
{
	prvek *pom = pøíprava_vložení();
	new(&pom->data) T(co);
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_konec(T&& co)
{
	prvek *pom = pøíprava_vložení();
	new(&pom->data) T(std::move(co));
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::prvek *seznam_impl<T, Alokátor>::pøíprava_vložení()
{
	prvek* pom = zarážka;
	poèet_prvkù++;
	(pom->data).~T();
	zarážka = zarážka->další = new prvek{ T{}, nullptr };
	return pom;
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::odstraò_první()
{
	if (prázdný())
	{
		throw std::out_of_range("Odstraòování z prázdného seznamu");
	}
	poèet_prvkù--;
	auto pom = hlava;
	hlava = hlava->další;
	pomùcka.odstraò_data(pom->data);
	delete pom;
}

template<class T, template<class T> class Alokátor>
void seznam_impl<T, Alokátor>::vyprázdni()
{
	while (!prázdný())
		odstraò_první();
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_zaèátek(T& co)
{
	hlava = new prvek{ co, hlava };
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_zaèátek(T&& co)
{
	hlava = new prvek{ std::move(co), hlava };
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vypiš()
{
	std::cout << "{ ";
	for (prvek *pom = hlava; pom != zarážka; pom = pom->další)
	{
		pomùcka.vypiš_prvek(pom);
	}
	std::cout << "}";
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::prohoï(seznam_impl<T, Alokátor>& s)
{
	std::swap(hlava, s.hlava);
	std::swap(zarážka, s.zarážka);
	std::swap(poèet_prvkù, s.poèet_prvkù);
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::pøikopíruj(const seznam_impl<T, Alokátor>& s)
{
	for (auto pom = s.hlava; pom != s.zarážka; pom = pom->další)
	{
		vlož_na_konec(pom->data);
	}
}

#endif //__SEZNAM_IMPL_H__
