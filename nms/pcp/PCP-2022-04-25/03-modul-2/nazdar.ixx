module;
#include <iostream>


export module nazdar;
using namespace std;

export void pozdrav()
{
	cout << "Nazdárek" << endl;
}

export template<class T>
T Max(T a, T b)
{
	return a > b ? a : b;
}