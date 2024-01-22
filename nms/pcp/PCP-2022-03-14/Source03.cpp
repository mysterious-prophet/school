// SFINAE
// Pou�it� SFINAE pro volbu jedn� z funkc� (podle parity parametru �ablony)

#include <iostream>
#include <stdlib.h>



template<int N>
void test(char(*)[N % 2 == 0] = 0)
{
	std::cout << "Parametr " << N << " je sud� " << std::endl;
}

template<int N>
void test(char(*)[N % 2 == 1] = 0)
{
	std::cout << "Parametr " << N << " je lich� " << std::endl;
}

int main()
{
	system("CHCP 1250 > NUL");
	test<3>();
	test<4>();
}