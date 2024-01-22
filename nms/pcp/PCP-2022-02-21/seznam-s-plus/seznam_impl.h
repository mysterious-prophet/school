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
	template<class U = T> struct pomoc;
	template<bool je_konstantn�> class iter�tor_seznamu_impl;
public:
	// Zve�ej�ovan� datov� typy
	using typ_hodnot = T;
	using iter�tor_seznamu = iter�tor_seznamu_impl<false>;
	using konstantn�_iter�tor_seznamu = iter�tor_seznamu_impl<true>;

	// Konstruktory a destroktor
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
	// P��stup k prvk�m, hled�n�
	typ_hodnot prvn�();
	iter�tor_seznamu najdi(const T co);
	konstantn�_iter�tor_seznamu najdi(const T co) const;
	// Vkl�d�n� do seznamu
	void vlo�_na_konec(T& co);
	void vlo�_na_konec(T&& co);
	void vlo�_na_za��tek(T& co);
	void vlo�_na_za��tek(T&& co);
	iter�tor_seznamu vlo�_za(iter�tor_seznamu &kam, T& co);
	iter�tor_seznamu vlo�_za(iter�tor_seznamu &kam, T&& co);
	// Odstra�ov�n�
	void odstra�_prvn�();
	void vypr�zdni();
	iter�tor_seznamu odstra�(iter�tor_seznamu ten);
	// Pro lad�n�
	void vypi�();
	// Prohozen� obsahu dvou seznam�
	void proho�(seznam_impl& s);
	// Iter�tory
	iter�tor_seznamu begin() noexcept;
	konstantn�_iter�tor_seznamu begin() const noexcept;
	konstantn�_iter�tor_seznamu cbegin() const noexcept;
	iter�tor_seznamu end() noexcept;
	konstantn�_iter�tor_seznamu end() const noexcept;
	konstantn�_iter�tor_seznamu cend() const noexcept;
	// Spojov�n� seznam�
	seznam_impl operator+(seznam_impl& s) &;
	seznam_impl operator+(seznam_impl && s) &;
	seznam_impl&& operator+(seznam_impl& s) &&;
	seznam_impl&& operator+(seznam_impl&& s) &&;
	seznam_impl& operator +=(seznam_impl& s) { p�ikop�ruj(s); return *this; }
	seznam_impl& operator +=(seznam_impl&& s) { p�ipoj(move(s)); return *this; }
private:
	prvek *hlava, *zar�ka;
	std::size_t po�et_prvk�;
	// Odli�n� implementace n�kter�ch operac� pro uakzatele
	pomoc<T> pom�cka;

	prvek *p��prava_vlo�en�();
	void p�ikop�ruj(const seznam_impl& s);
	void p�ipoj(seznam_impl&& s);
	//prvek* najdi_ukazatel(const T co) const;
	template<typename typ_iter�toru>
	typ_iter�toru najdi_impl(T co) const;
	template<bool r_hodnota>
	iter�tor_seznamu vlo�_za_impl(iter�tor_seznamu &kam, T&& co);
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

template<class T, template<class T> class Alok�tor>
template<bool je_konstantn�>
class seznam_impl<T, Alok�tor>::iter�tor_seznamu_impl
{
	friend class seznam_impl<T, Alok�tor>;
	using ukazatel_na_prvek = std::conditional_t<je_konstantn�, const prvek*, prvek*>;
	ukazatel_na_prvek ukazatel;
public:
	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using reference = std::conditional_t<je_konstantn�, const T&, T&>;
	using pointer = std::conditional_t<je_konstantn�, const T*, T*>;
	
	iter�tor_seznamu_impl(const iter�tor_seznamu_impl<false>& iter)
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

	iter�tor_seznamu_impl& operator++()
	{
		if (ukazatel->dal��)
		{
			ukazatel = ukazatel->dal��;
		}
		return *this;
	}
	iter�tor_seznamu_impl operator++(int)
	{
		iter�tor_seznamu_impl pom(*this);
		++*this;
		return pom;
	}
	bool operator ==(const iter�tor_seznamu_impl& iter) const
	{
		return ukazatel == iter.ukazatel;
	}
	bool operator !=(const iter�tor_seznamu_impl& iter) const
	{
		return !(*this == iter);
	}
private:
	iter�tor_seznamu_impl(ukazatel_na_prvek np = nullptr)
		: ukazatel(np)
	{}

	inline ukazatel_na_prvek ukazatel_na_aktu�ln�_prvek() const
	{
		return ukazatel;
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

template<class T, template<class T> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::najdi(const T co)
{
	//return iter�tor_seznamu(najdi_ukazatel(co));
	return najdi_impl<iter�tor_seznamu>(co);
}

template<class T, template<class T> class Alok�tor>
typename seznam_impl<T, Alok�tor>::konstantn�_iter�tor_seznamu seznam_impl<T, Alok�tor>::najdi(const T co) const
{
	//return konstantn�_iter�tor_seznamu(najdi_ukazatel(co));
	return najdi_impl<konstantn�_iter�tor_seznamu>(co);
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

template<class T, template<class T> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::odstra�(typename seznam_impl<T, Alok�tor>::iter�tor_seznamu kter�)
{
	prvek* ten = kter�.ukazatel_na_aktu�ln�_prvek();
	if (ten == zar�ka)
	{
		throw std::out_of_range("Odstra�ov�na zar�ka seznamu");
	}
	po�et_prvk�--;
	prvek* n�sleduj�c� = ten->dal��;
	if (n�sleduj�c� == zar�ka)
	{
		delete zar�ka;
		zar�ka = ten;
		zar�ka->dal�� = nullptr;
	}
	else
	{
		*ten = *n�sleduj�c�;
		delete n�sleduj�c�;
	}
	return iter�tor_seznamu{ n�sleduj�c� };
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_za��tek(T& co)
{
	hlava = new prvek{ co, hlava };
	po�et_prvk�++;
}

template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::vlo�_na_za��tek(T&& co)
{
	hlava = new prvek{ std::move(co), hlava };
	po�et_prvk�++;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::vlo�_za(typename seznam_impl<T, Alok�tor>::iter�tor_seznamu & kam, T& co)
{
	return vlo�_za_impl<false>(kam, std::move(co));
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::vlo�_za(typename seznam_impl<T, Alok�tor>::iter�tor_seznamu & kam, T&& co)
{
	return vlo�_za_impl<true>(kam, std::move(co));
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

//template<class T, template<class> class Alok�tor>
//typename seznam_impl<T, Alok�tor>::prvek * seznam_impl<T, Alok�tor>::najdi_ukazatel(const T co) const
//{
//	for (prvek *pom = hlava; pom != zar�ka; pom = pom->dal��)
//	{
//		if (pom->data == co)
//		{
//			return pom;
//		}
//	}
//	return zar�ka;
//}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::begin() noexcept
{
	return hlava;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::konstantn�_iter�tor_seznamu seznam_impl<T, Alok�tor>::begin() const noexcept
{
	return hlava;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::konstantn�_iter�tor_seznamu seznam_impl<T, Alok�tor>::cbegin() const noexcept
{
	return hlava;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::end() noexcept
{
	return zar�ka;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::konstantn�_iter�tor_seznamu seznam_impl<T, Alok�tor>::end() const noexcept
{
	return zar�ka;
}

template<class T, template<class> class Alok�tor>
typename seznam_impl<T, Alok�tor>::konstantn�_iter�tor_seznamu seznam_impl<T, Alok�tor>::cend() const noexcept
{
	return zar�ka;
}

template<class T, template<class> class Alok�tor>
seznam_impl<T, Alok�tor> seznam_impl<T, Alok�tor>::operator+(seznam_impl & s) &
{
	seznam_impl<T, Alok�tor> v�sledek(*this);
	v�sledek.p�ikop�ruj(s);
	return v�sledek;
}

template<class T, template<class> class Alok�tor>
seznam_impl<T, Alok�tor>&& seznam_impl<T, Alok�tor>::operator+(seznam_impl & s) &&
{
	p�ikop�ruj(s);
	return move(*this);
}

template<class T, template<class> class Alok�tor>
seznam_impl<T, Alok�tor> seznam_impl<T, Alok�tor>::operator+(seznam_impl && s) &
{
	seznam_impl<T, Alok�tor> v�sledek(*this);
	v�sledek.p�ipoj(move(s));
	return v�sledek;
}

template<class T, template<class> class Alok�tor>
seznam_impl<T, Alok�tor>&& seznam_impl<T, Alok�tor>::operator+(seznam_impl && s) &&
{
	p�ipoj(move(s));
	return move(*this);
}



template<class T, template<class> class Alok�tor>
void seznam_impl<T, Alok�tor>::p�ipoj(seznam_impl<T, Alok�tor>&& s)
{
	if (s.pr�zdn�()) return;
	zar�ka->data = s.hlava->data;
	zar�ka->dal�� = s.hlava->dal��;
	zar�ka = s.zar�ka;
	delete s.hlava;
	s.hlava = s.zar�ka = new prvek{ T{}, nullptr };
	po�et_prvk� += s.po�et_prvk�;
	s.po�et_prvk� = 0;
}

template<class T, template<class> class Alok�tor>
template<typename typ_iter�toru>
inline typ_iter�toru seznam_impl<T, Alok�tor>::najdi_impl(T co) const
{
	for (auto pom = hlava; pom != zar�ka; pom = pom->dal��)
	{
		if (pom->data == co)
		{
			return typ_iter�toru{ pom };
		}
	}
	return typ_iter�toru{ zar�ka };
}

template<class T, template<class> class Alok�tor>
template<bool r_hodnota>
typename seznam_impl<T, Alok�tor>::iter�tor_seznamu seznam_impl<T, Alok�tor>::vlo�_za_impl(typename seznam_impl<T, Alok�tor>::iter�tor_seznamu &kam, T&& co)
{
	prvek* pom = kam.ukazatel_na_aktu�ln�_prvek();
	if (pom == zar�ka)
	{
		throw std::out_of_range{ "Vkl�d�n� za zar�ku seznamu" };
	}
	po�et_prvk�++;
	prvek* n�sleduj�c� = pom->dal��;
	
	if constexpr(r_hodnota)
	{
		pom->dal�� = new prvek(std::move(co), n�sleduj�c�);
	}
	else
	{
		pom->dal�� = new prvek(co, n�sleduj�c�);
	}
	return iter�tor_seznamu{ pom->dal�� };
}

#endif //__SEZNAM_IMPL_H__

