#include <utility>
#include "seznam.h"

using namespace std;

int main()
{
	const seznam<int> s{ 1,3,6 };
	//s.vlož_na_konec(8);
	s.prázdný();
	seznam<int> s1{ 8, 11 };
	//seznam<int> s3 = s + s1;
	//s3.vlož_na_zaèátek(5);
}