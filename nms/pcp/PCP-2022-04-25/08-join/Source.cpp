#include <iostream>
#include <stdlib.h>
#include <thread>

// soubìh pøi výstupu

using namespace std;

const int M = 10;

const char* verš1 = "koèka leze dírou";
const char* verš2 = "pes oknem";
const char* verš3 = "nebude-li pršet\nnezmoknem";

void vypiš(const char* text)
{
	for (int i = 0; i < M; i++)
	{
		cout << text << endl;
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	thread výpis1{ vypiš, verš1 };
	thread výpis2{ vypiš, verš2 };
	výpis1.join();
	výpis2.join();
	cout << verš3 << endl;
}