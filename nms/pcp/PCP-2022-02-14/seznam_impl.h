#ifndef __SEZNAM_IMPL_H__
#define __SEZNAM_IMPL_H__
#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include <iostream>

//using namespace std;

template<class T, template<class T> class Alok�tor = std::allocator>
class seznam_impl
{
	struct prvek;
	template<class U = T>
	struct pomoc;
public:
	// Zve�ej�ovan� datov� typy
	using typ_hodnot = T;
	// Konstruktory a destruktor
	seznam_impl();
	seznam_impl(std::initializer_list<T> seznam_inicializ�tor�);
	seznam_impl(const seznam_impl& si);
	seznam_impl(seznam_impl&& si);
	~seznam_impl();
	// P�i�azov�n�
	seznam_impl& operator=(seznam_impl& si);
	seznam_impl& operator=(seznam_impl&& si);
	// Stav seznamu
	std::size_t velikost() const noexcept { return po�et_prvk�; }
	bool pr�zdn�() const noexcept { return hlava == zar�ka; }
	// P��stup k prvk�m
	typ_hodnot prvn�();
	// Vkl�d�n� do seznamu
	void vlo�_na_konec(T& co);
	void vlo�_na_konec(T&& co);
	void vlo�_na_za��tek(T& co);
	void vlo�_na_za��tek(T&& co);
	// Odstra�ov�n�
	void odstra�_prvn�();
	void vypr�zdni();
	// Pro lad�n�
	void vypi�();
	// Prohozen� obsahu dvou seznam�
	void proho�(seznam_impl& s);
private:
	prvek *hlava, *zar�ka;
	std::size_t po�et_prvk�;
	// Odli�n� implementace n�kter�ch operac� pro ukazatele
	pomoc<T> pom�cka;

	prvek *p��prava_vlo�en�();
	void p�ikop�ruj(const seznam_impl& s);
};

template<class T, template<class T> class Alok�tor>
template<class U>
struct seznam_impl<T, Alok�tor>::pomoc
{
	void vypi�_prvek(prvek *ten)
	{
		std::cout << ten->data << " ";
	}
	void odstra�_data(T) {}
};

template<class T, template<class T> class Alok�tor>
template<class U>
struct seznam_impl<T, Alok�tor>::pomoc<U*>
{
	void vypi�_prvek(prvek *ten)
	{
		std::cout << "*" << *(ten->data) << " ";
	}
	void odstra�_data(T tato_data) 
	{
		delete tato_data;
	}
};


template<class T, template<class T> class Alok�tor>
struct seznam_impl<T, Alok�tor>::prvek
{
	T data;
	prvek *dal��;
	static Alok�tor<prvek> alok�tor;

	prvek(T& data, prvek *dal��) :data(data), dal��(dal��) {}
	prvek(T&& data, prvek* dal��) : data(std::move(data)), dal��(dal��) {}

	void *operator new(std::size_t)
	{
		return alok�tor.allocate(1);
	}

	void operator delete(void *p)
	{
		alok�tor.deallocate((prvek*)p, 1);
	}
};

template<class T, template<class> class Alok�tor>
Alok�tor<typename seznam_impl<T, Alok�tor>::prvek> seznam_impl<T, Alok�tor>::prvek::alok�tor;


template<class T, template<class> class Alok�tor>
seznam_impl<T, Alok�tor>::seznam_impl()
{
	hlava = zar�ka = new prvek{ T{}, nullptr };
	po�et_prvk� = 0;
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor>::seznam_impl(std::initializer_list<T> seznam_inicializ�tor�)
	:seznam_impl()
{
	for (auto x : seznam_inicializ�tor�)
	{
		vlo�_na_konec(x);
	}
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor>::seznam_impl(const seznam_impl<T, Alok�tor>& si)
	: seznam_impl()
{
	p�ikop�ruj(si);
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor>::seznam_impl(seznam_impl<T, Alok�tor>&& si)
	: seznam_impl()
{
	proho�(si);
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor>::~seznam_impl()
{
	vypr�zdni();
	delete hlava;
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor> & seznam_impl<T, Alok�tor>::operator=(seznam_impl<T, Alok�tor> & si)
{
	vypr�zdni();
	p�ikop�ruj(si);
	return *this;
}

template<class T, template<class T> class Alok�tor>
seznam_impl<T, Alok�tor> & seznam_impl<T, Alok�tor>::operator=(seznam_impl<T, Alok�tor> && si)
{
	proho�(si);
	return *this;
}

template<class T, template<class T> class Alok�tor>
T seznam_impl<T, Alok�tor>::prvn�()
{
	if(pr�zdn�)
	{
		throw std::out_of_range("Odstra�ov�n� z pr�zdn�ho seznamu");
	}
	return hlava->data;
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_konec(T& co)
{
	prvek *pom = p��prava_vlo�en�();
	new(&pom->data) T(co);
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_konec(T&& co)
{
	prvek *pom = p��prava_vlo�en�();
	new(&pom->data) T(std::move(co));
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::prvek *seznam_impl<T, Alok�tor>::p��prava_vlo�en�()
{
	prvek* pom = zar�ka;
	po�et_prvk�++;
	(pom->data).~T();
	zar�ka = zar�ka->dal�� = new prvek{ T{}, nullptr };
	return pom;
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::odstra�_prvn�()
{
	if (pr�zdn�())
	{
		throw std::out_of_range("Odstra�ov�n� z pr�zdn�ho seznamu");
	}
	po�et_prvk�--;
	auto pom = hlava;
	hlava = hlava->dal��;
	pom�cka.odstra�_data(pom->data);
	delete pom;
}

template<class T, template<class T> class Alok�tor>
void seznam_impl<T, Alok�tor>::vypr�zdni()
{
	while (!pr�zdn�())
		odstra�_prvn�();
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_za��tek(T& co)
{
	hlava = new prvek{ co, hlava };
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_za��tek(T&& co)
{
	hlava = new prvek{ std::move(co), hlava };
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vypi�()
{
	std::cout << "{ ";
	for (prvek *pom = hlava; pom != zar�ka; pom = pom->dal��)
	{
		pom�cka.vypi�_prvek(pom);
	}
	std::cout << "}";
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::proho�(seznam_impl<T, Alok�tor>& s)
{
	std::swap(hlava, s.hlava);
	std::swap(zar�ka, s.zar�ka);
	std::swap(po�et_prvk�, s.po�et_prvk�);
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::p�ikop�ruj(const seznam_impl<T, Alok�tor>& s)
{
	for (auto pom = s.hlava; pom != s.zar�ka; pom = pom->dal��)
	{
		vlo�_na_konec(pom->data);
	}
}

#endif //__SEZNAM_IMPL_H__
