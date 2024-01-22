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
	// Konstruktory a destruktor
	seznam() { u_seznam = new Implementace(); }
	seznam(std::initializer_list<T> seznam_inicializátorù);
	seznam(const seznam& s) { u_seznam = new seznam_impl(*(s.u_seznam)); }
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
	// Vkládání do seznamu
	void vlož_na_konec(const typ_hodnot &co){ u_seznam->vlož_na_konec(co); }
	void vlož_na_konec(typ_hodnot &&co) { u_seznam->vlož_na_konec(std::move(co)); }
	void vlož_na_zaèátek(const typ_hodnot& co) { u_seznam->vlož_na_zaèátek(co); }
	void vlož_na_zaèátek(typ_hodnot&& co) { u_seznam->vlož_na_zaèátek(std::move(co)); }
	// Ostraòování
	void odstraò_první() { u_seznam->odstraò_první(); }
	void vyprázdni() { u_seznam->vyprázdni(); }
	// Pro ladìní
	void vypiš() { u_seznam->vypiš(); }
	// Prohození obsahu dvou seznamù
	void prohoï(seznam &s) { std::swap(u_seznam, s.u_seznam); }
};

template<class T, template<class T> class Alokátor, class Implementace>
seznam<T, Alokátor, Implementace>::seznam(std::initializer_list<T> seznam_inicializátorù)
{
	u_seznam = new seznam_impl<T, Alokátor>(seznam_inicializátorù);
}


#endif //__SEZNAM_H__
