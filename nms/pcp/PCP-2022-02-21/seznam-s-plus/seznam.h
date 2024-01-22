#ifndef __SEZNAM_H__
#define __SEZNAM_H__

#include <memory>
#include "seznam_impl.h"

template<class T, 
	template<class T> class Alokátor = std::allocator,
	class Implementace = seznam_impl<T, Alokátor>
>
class seznam
{
	Implementace *u_seznam;
public:
	// Zveøejòované datové typy
	using typ_hodnot = typename Implementace::typ_hodnot;
	using iterátor_seznamu = typename Implementace::iterátor_seznamu;
	using konstantní_iterátor_seznamu = typename Implementace::konstantní_iterátor_seznamu;
	// Konstruktory a destruktor
	seznam() { u_seznam = new Implementace(); }
	seznam(std::initializer_list<T> seznam_inicializátorù);
	seznam(const seznam& s) { u_seznam = new Implementace(*(s.u_seznam)); }
	seznam(seznam&& s) : seznam() {	prohoï(s); }
	~seznam() { delete u_seznam; }
	// Pøiøazování
	seznam& operator = (const seznam& s) { *(this->u_seznam) = *(s.u_seznam); return *this;	}
	seznam& operator = (seznam&& s) { prohoï(s); return *this; }
	// Stav seznamu
	bool prázdný() const noexcept { return u_seznam->prázdný(); }
	std::size_t velikost() const noexcept { return u_seznam->velikost(); }
	// Pøístup k prvkùm
	typ_hodnot první() { return u_seznam->první(); }
	iterátor_seznamu najdi(const T co) { return u_seznam->najdi(co); }
	// Vkládání do seznamu
	void vlož_na_konec(const typ_hodnot &co){ u_seznam->vlož_na_konec(co); }
	void vlož_na_konec(typ_hodnot &&co) { u_seznam->vlož_na_konec(co); }
	void vlož_na_zaèátek(const typ_hodnot& co) { u_seznam->vlož_na_zaèátek(co); }
	void vlož_na_zaèátek(typ_hodnot&& co) { u_seznam->vlož_na_zaèátek(std::move(co)); }
	iterátor_seznamu vlož_za(iterátor_seznamu kam, T& co) { return u_seznam->vlož_za(kam, co); }
	iterátor_seznamu vlož_za(iterátor_seznamu kam, T&& co) { return u_seznam->vlož_za(kam, std::move(co)); }
	// Ostraòování
	void odstraò_první() { u_seznam->odstraò_první(); }
	iterátor_seznamu odstraò(iterátor_seznamu ten) { return u_seznam->odstraò(ten); }
	void vyprázdni() { u_seznam->vyprázdni(); }
	// Pro ladìní
	void vypiš() { u_seznam->vypiš(); }
	// Prohození obsahu dvou seznamù
	void prohoï(seznam &s) { std::swap(u_seznam, s.u_seznam); }
	// Iterátory
	iterátor_seznamu begin() noexcept { return u_seznam->begin(); };
	konstantní_iterátor_seznamu begin() const noexcept { return u_seznam->begin(); };
	konstantní_iterátor_seznamu cbegin() const noexcept { return u_seznam->cbegin(); };
	iterátor_seznamu end() noexcept { return u_seznam->end(); };
	konstantní_iterátor_seznamu end() const noexcept { return u_seznam->end(); };
	konstantní_iterátor_seznamu cend() const noexcept { return u_seznam->cend(); };
	// Spojování seznamù
	seznam operator+(seznam& s) &;
	seznam operator+(seznam&& s) &;
	seznam operator+(seznam& s) &&;
	seznam operator+(seznam&& s) &&;
	seznam operator+=(seznam& s) { *u_seznam += *s.u_seznam; return *this; }
	seznam operator+=(seznam&& s) { *u_seznam += std::move(*s.u_seznam); return *this; }
private:
	seznam(Implementace* impl): u_seznam(impl){}
	template<bool levá_r_hodnota, bool pravá_r_hodnota>
	seznam operátor_plus_impl(seznam& a);
};

template<class T, template<class T> class Alokátor, class Implementace>
template<bool levá_r_hodnota, bool pravá_r_hodnota>
seznam<T, Alokátor, Implementace>
seznam<T, Alokátor, Implementace>::operátor_plus_impl(seznam& a)
{
	seznam<T, Alokátor, Implementace> výsledek;
	Implementace pom;
	if constexpr (!levá_r_hodnota && !pravá_r_hodnota)
	{
		pom = *u_seznam + *a.u_seznam;
	}
	else if constexpr (!levá_r_hodnota && pravá_r_hodnota)
	{
		pom = *u_seznam + std::move(*a.u_seznam);
	}
	else if constexpr (levá_r_hodnota && !pravá_r_hodnota)
	{
		pom = std::move(*u_seznam) + *a.u_seznam;
	}
	else
	{
		pom = std::move(*u_seznam) + std::move(*a.u_seznam);
	}
	výsledek.u_seznam->prohoï(pom);
	return výsledek;
}

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace>::seznam(std::initializer_list<T> seznam_inicializátorù)
{
	u_seznam = new seznam_impl<T, Alokátor>(seznam_inicializátorù);
}

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace> seznam<T, Alokátor, Implementace>::operator+(seznam & s) &
{
	return operátor_plus_impl<false, false>(s);
}

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace> seznam<T, Alokátor, Implementace>::operator+(seznam && s) &
{
	return operátor_plus_impl<false, true>(s);
}

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace> seznam<T, Alokátor, Implementace>::operator+(seznam & s) &&
{
	return operátor_plus_impl<true, false>(s);
}

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace> seznam<T, Alokátor, Implementace>::operator+(seznam && s) &&
{
	return operátor_plus_impl<true, true>(s);
}
#endif //__SEZNAM_H__
