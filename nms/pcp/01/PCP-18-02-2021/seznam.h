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
	void vlo�_na_konec(T& data) { u_seznam->vlo�_na_konec(data); }
	void vlo�_na_konec(T&& data) { u_seznam->vlo�_na_konec(move(data)); }
	void vlo�_na_za��tek(T& data) { u_seznam->vlo�_na_za��tek(data); }
	void vlo�_na_za��tek(T&& data) { u_seznam->vlo�_na_za��tek(move(data)); }
	void odstra�_prvn�() { u_seznam->odstra�_prvn�(); }
	void vypr�zdni();
	bool pr�zdn�() const final { return u_seznam->pr�zdn�(); }
	bool pr�zdn�() { return u_seznam->pr�zdn�();}

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
	seznam<T, SEZNAM_IMPL> v�sledek;
	v�sledek.u_seznam = new SEZNAM_IMPL((*u_seznam) + (*data.u_seznam));
	return v�sledek;
}


template<class T, class SEZNAM_IMPL>
seznam<T, SEZNAM_IMPL>::~seznam()
{
	delete u_seznam;
}

template<typename T, typename SEZNAM_IMPL>
inline void seznam<T, SEZNAM_IMPL>::vypr�zdni()
{
	u_seznam->vypr�zdni();
}




#endif // __SEZNAM_H__
