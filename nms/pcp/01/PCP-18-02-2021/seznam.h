#ifndef __SEZNAM_H__
#define __SEZNAM_H__
#include <initializer_list>

#include "seznam_impl.h"

using namespace std;

template<typename T, typename SEZNAM_IMPL = seznam_impl<T>>
class seznam
{
public:
	seznam();
	seznam(initializer_list<T> data);
	seznam(seznam& vzor);
	seznam(seznam&& vzor);  
	seznam<T, SEZNAM_IMPL>& operator=(seznam<T, SEZNAM_IMPL>& vzor);
	seznam<T, SEZNAM_IMPL>& operator=(seznam<T, SEZNAM_IMPL>&& vzor);
	seznam<T, SEZNAM_IMPL> operator+(seznam<T, SEZNAM_IMPL>& data);
	~seznam();
	void vlož_na_konec(T& data) { u_seznam->vlož_na_konec(data); }
	void vlož_na_konec(T&& data) { u_seznam->vlož_na_konec(move(data)); }
	void vlož_na_zaèátek(T& data) { u_seznam->vlož_na_zaèátek(data); }
	void vlož_na_zaèátek(T&& data) { u_seznam->vlož_na_zaèátek(move(data)); }
	void odstraò_první() { u_seznam->odstraò_první(); }
	void vyprázdni();
	bool prázdný() const final { return u_seznam->prázdný(); }
	bool prázdný() { return u_seznam->prázdný();}

private:
	SEZNAM_IMPL* u_seznam;
};

template<class T, class SEZNAM_IMPL>
seznam<T, SEZNAM_IMPL>::seznam()
{
	u_seznam = new SEZNAM_IMPL();
}

template<class T, class SEZNAM_IMPL>
seznam<T, SEZNAM_IMPL>::seznam(initializer_list<T> data)
{
	u_seznam = new SEZNAM_IMPL(data);
}

template<typename T, typename SEZNAM_IMPL>
inline seznam<T, SEZNAM_IMPL>::seznam(seznam & vzor)
{
	u_seznam = new SEZNAM_IMPL(*vzor.u_seznam);
}

template<typename T, typename SEZNAM_IMPL>
inline seznam<T, SEZNAM_IMPL>::seznam(seznam && vzor)
	:seznam()
{
	swap(u_seznam, vzor.u_seznam);
}

template<typename T, typename SEZNAM_IMPL>
inline seznam<T, SEZNAM_IMPL>& seznam<T, SEZNAM_IMPL>::operator=(seznam & vzor)
{
	if (u_seznam != vzor.u_seznam)
	{
		delete u_seznam;
		u_seznam = new SEZNAM_IMPL(*vzor.u_seznam);
	}
	return *this;
}

template<typename T, typename SEZNAM_IMPL>
inline seznam<T, SEZNAM_IMPL>& seznam<T, SEZNAM_IMPL>::operator=(seznam<T, SEZNAM_IMPL>&& vzor)
{
	swap(u_seznam, vzor.u_seznam);
	return *this;
}

template<typename T, typename SEZNAM_IMPL>
inline seznam<T, SEZNAM_IMPL> seznam<T, SEZNAM_IMPL>::operator+(seznam<T, SEZNAM_IMPL>& data)
{
	seznam<T, SEZNAM_IMPL> výsledek;
	výsledek.u_seznam = new SEZNAM_IMPL((*u_seznam) + (*data.u_seznam));
	return výsledek;
}


template<class T, class SEZNAM_IMPL>
seznam<T, SEZNAM_IMPL>::~seznam()
{
	delete u_seznam;
}

template<typename T, typename SEZNAM_IMPL>
inline void seznam<T, SEZNAM_IMPL>::vyprázdni()
{
	u_seznam->vyprázdni();
}




#endif // __SEZNAM_H__
