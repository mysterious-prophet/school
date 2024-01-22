#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;

const int M = 10;

const char* verš1 = "koèka leze dírou\n";
const char* verš2 = "pes oknem\n";
const char* verš3 = "nebude-li pršet\nnezmoknem\n";

void vypiš(const char* text)
{
	for (int i = 0; i < M; i++)
	{
		cout << text;
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	thread výpis1{ vypiš, verš1 };
	thread výpis2{ vypiš, verš2 };
	//výpis1.join();
	//výpis2.join();
	výpis1.detach();
	výpis2.detach();
	cout << verš3;
}