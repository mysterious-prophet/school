#include <utility>
#include "seznam.h"

using namespace std;

int main()
{
	const seznam<int> s{ 1,3,6 };
	//s.vlo�_na_konec(8);
	s.pr�zdn�();
	seznam<int> s1{ 8, 11 };
	//seznam<int> s3 = s + s1;
	//s3.vlo�_na_za��tek(5);
}