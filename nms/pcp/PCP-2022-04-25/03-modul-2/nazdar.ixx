module;
#include <iostream>


export module nazdar;
using namespace std;

export void pozdrav()
{
	cout << "Nazd�rek" << endl;
}

export template<class T>
T Max(T a, T b)
{
	return a > b ? a : b;
}