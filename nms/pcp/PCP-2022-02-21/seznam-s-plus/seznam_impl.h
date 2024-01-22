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
	template<class U = T> struct pomoc;
	template<bool je_konstantní> class iterátor_seznamu_impl;
public:
	// Zveøejòované datové typy
	using typ_hodnot = T;
	using iterátor_seznamu = iterátor_seznamu_impl<false>;
	using konstantní_iterátor_seznamu = iterátor_seznamu_impl<true>;

	// Konstruktory a destroktor
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
	// Pøístup k prvkùm, hledání
	typ_hodnot první();
	iterátor_seznamu najdi(const T co);
	konstantní_iterátor_seznamu najdi(const T co) const;
	// Vkládání do seznamu
	void vlož_na_konec(T& co);
	void vlož_na_konec(T&& co);
	void vlož_na_zaèátek(T& co);
	void vlož_na_zaèátek(T&& co);
	iterátor_seznamu vlož_za(iterátor_seznamu &kam, T& co);
	iterátor_seznamu vlož_za(iterátor_seznamu &kam, T&& co);
	// Odstraòování
	void odstraò_první();
	void vyprázdni();
	iterátor_seznamu odstraò(iterátor_seznamu ten);
	// Pro ladìní
	void vypiš();
	// Prohození obsahu dvou seznamù
	void prohoï(seznam_impl& s);
	// Iterátory
	iterátor_seznamu begin() noexcept;
	konstantní_iterátor_seznamu begin() const noexcept;
	konstantní_iterátor_seznamu cbegin() const noexcept;
	iterátor_seznamu end() noexcept;
	konstantní_iterátor_seznamu end() const noexcept;
	konstantní_iterátor_seznamu cend() const noexcept;
	// Spojování seznamù
	seznam_impl operator+(seznam_impl& s) &;
	seznam_impl operator+(seznam_impl && s) &;
	seznam_impl&& operator+(seznam_impl& s) &&;
	seznam_impl&& operator+(seznam_impl&& s) &&;
	seznam_impl& operator +=(seznam_impl& s) { pøikopíruj(s); return *this; }
	seznam_impl& operator +=(seznam_impl&& s) { pøipoj(move(s)); return *this; }
private:
	prvek *hlava, *zarážka;
	std::size_t poèet_prvkù;
	// Odlišné implementace nìkterých operací pro uakzatele
	pomoc<T> pomùcka;

	prvek *pøíprava_vložení();
	void pøikopíruj(const seznam_impl& s);
	void pøipoj(seznam_impl&& s);
	//prvek* najdi_ukazatel(const T co) const;
	template<typename typ_iterátoru>
	typ_iterátoru najdi_impl(T co) const;
	template<bool r_hodnota>
	iterátor_seznamu vlož_za_impl(iterátor_seznamu &kam, T&& co);
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

template<class T, template<class T> class Alokátor>
template<bool je_konstantní>
class seznam_impl<T, Alokátor>::iterátor_seznamu_impl
{
	friend class seznam_impl<T, Alokátor>;
	using ukazatel_na_prvek = std::conditional_t<je_konstantní, const prvek*, prvek*>;
	ukazatel_na_prvek ukazatel;
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using reference = std::conditional_t<je_konstantní, const T&, T&>;
	using pointer = std::conditional_t<je_konstantní, const T*, T*>;
	
	iterátor_seznamu_impl(const iterátor_seznamu_impl<false>& iter)
		: ukazatel(iter.ukazatel)
	{}

	reference operator *() const
	{
		return ukazatel->data;
	}

	pointer operator->() const
	{
		return &(ukazatel->data);
	}

	iterátor_seznamu_impl& operator++()
	{
		if (ukazatel->další)
		{
			ukazatel = ukazatel->další;
		}
		return *this;
	}
	iterátor_seznamu_impl operator++(int)
	{
		iterátor_seznamu_impl pom(*this);
		++*this;
		return pom;
	}
	bool operator ==(const iterátor_seznamu_impl& iter) const
	{
		return ukazatel == iter.ukazatel;
	}
	bool operator !=(const iterátor_seznamu_impl& iter) const
	{
		return !(*this == iter);
	}
private:
	iterátor_seznamu_impl(ukazatel_na_prvek np = nullptr)
		: ukazatel(np)
	{}

	inline ukazatel_na_prvek ukazatel_na_aktuální_prvek() const
	{
		return ukazatel;
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

template<class T, template<class T> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::najdi(const T co)
{
	//return iterátor_seznamu(najdi_ukazatel(co));
	return najdi_impl<iterátor_seznamu>(co);
}

template<class T, template<class T> class Alokátor>
typename seznam_impl<T, Alokátor>::konstantní_iterátor_seznamu seznam_impl<T, Alokátor>::najdi(const T co) const
{
	//return konstantní_iterátor_seznamu(najdi_ukazatel(co));
	return najdi_impl<konstantní_iterátor_seznamu>(co);
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

template<class T, template<class T> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::odstraò(typename seznam_impl<T, Alokátor>::iterátor_seznamu který)
{
	prvek* ten = který.ukazatel_na_aktuální_prvek();
	if (ten == zarážka)
	{
		throw std::out_of_range("Odstraòována zarážka seznamu");
	}
	poèet_prvkù--;
	prvek* následující = ten->další;
	if (následující == zarážka)
	{
		delete zarážka;
		zarážka = ten;
		zarážka->další = nullptr;
	}
	else
	{
		*ten = *následující;
		delete následující;
	}
	return iterátor_seznamu{ následující };
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_zaèátek(T& co)
{
	hlava = new prvek{ co, hlava };
	poèet_prvkù++;
}

template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::vlož_na_zaèátek(T&& co)
{
	hlava = new prvek{ std::move(co), hlava };
	poèet_prvkù++;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::vlož_za(typename seznam_impl<T, Alokátor>::iterátor_seznamu & kam, T& co)
{
	return vlož_za_impl<false>(kam, std::move(co));
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::vlož_za(typename seznam_impl<T, Alokátor>::iterátor_seznamu & kam, T&& co)
{
	return vlož_za_impl<true>(kam, std::move(co));
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

//template<class T, template<class> class Alokátor>
//typename seznam_impl<T, Alokátor>::prvek * seznam_impl<T, Alokátor>::najdi_ukazatel(const T co) const
//{
//	for (prvek *pom = hlava; pom != zarážka; pom = pom->další)
//	{
//		if (pom->data == co)
//		{
//			return pom;
//		}
//	}
//	return zarážka;
//}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::begin() noexcept
{
	return hlava;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::konstantní_iterátor_seznamu seznam_impl<T, Alokátor>::begin() const noexcept
{
	return hlava;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::konstantní_iterátor_seznamu seznam_impl<T, Alokátor>::cbegin() const noexcept
{
	return hlava;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::end() noexcept
{
	return zarážka;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::konstantní_iterátor_seznamu seznam_impl<T, Alokátor>::end() const noexcept
{
	return zarážka;
}

template<class T, template<class> class Alokátor>
typename seznam_impl<T, Alokátor>::konstantní_iterátor_seznamu seznam_impl<T, Alokátor>::cend() const noexcept
{
	return zarážka;
}

template<class T, template<class> class Alokátor>
seznam_impl<T, Alokátor> seznam_impl<T, Alokátor>::operator+(seznam_impl & s) &
{
	seznam_impl<T, Alokátor> výsledek(*this);
	výsledek.pøikopíruj(s);
	return výsledek;
}

template<class T, template<class> class Alokátor>
seznam_impl<T, Alokátor>&& seznam_impl<T, Alokátor>::operator+(seznam_impl & s) &&
{
	pøikopíruj(s);
	return move(*this);
}

template<class T, template<class> class Alokátor>
seznam_impl<T, Alokátor> seznam_impl<T, Alokátor>::operator+(seznam_impl && s) &
{
	seznam_impl<T, Alokátor> výsledek(*this);
	výsledek.pøipoj(move(s));
	return výsledek;
}

template<class T, template<class> class Alokátor>
seznam_impl<T, Alokátor>&& seznam_impl<T, Alokátor>::operator+(seznam_impl && s) &&
{
	pøipoj(move(s));
	return move(*this);
}



template<class T, template<class> class Alokátor>
void seznam_impl<T, Alokátor>::pøipoj(seznam_impl<T, Alokátor>&& s)
{
	if (s.prázdný()) return;
	zarážka->data = s.hlava->data;
	zarážka->další = s.hlava->další;
	zarážka = s.zarážka;
	delete s.hlava;
	s.hlava = s.zarážka = new prvek{ T{}, nullptr };
	poèet_prvkù += s.poèet_prvkù;
	s.poèet_prvkù = 0;
}

template<class T, template<class> class Alokátor>
template<typename typ_iterátoru>
inline typ_iterátoru seznam_impl<T, Alokátor>::najdi_impl(T co) const
{
	for (auto pom = hlava; pom != zarážka; pom = pom->další)
	{
		if (pom->data == co)
		{
			return typ_iterátoru{ pom };
		}
	}
	return typ_iterátoru{ zarážka };
}

template<class T, template<class> class Alokátor>
template<bool r_hodnota>
typename seznam_impl<T, Alokátor>::iterátor_seznamu seznam_impl<T, Alokátor>::vlož_za_impl(typename seznam_impl<T, Alokátor>::iterátor_seznamu &kam, T&& co)
{
	prvek* pom = kam.ukazatel_na_aktuální_prvek();
	if (pom == zarážka)
	{
		throw std::out_of_range{ "Vkládání za zarážku seznamu" };
	}
	poèet_prvkù++;
	prvek* následující = pom->další;
	
	if constexpr(r_hodnota)
	{
		pom->další = new prvek(std::move(co), následující);
	}
	else
	{
		pom->další = new prvek(co, následující);
	}
	return iterátor_seznamu{ pom->další };
}

#endif //__SEZNAM_IMPL_H__

