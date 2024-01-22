#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>

using namespace std;

//using namespace std::chrono;
//using namespace std::literals::chrono_literals;

const int M = 10;

const char* verš1 = "koèka leze dírou\n";
const char* verš2 = "pes oknem\n";
const char* verš3 = "nebude-li pršet\nnezmoknem\n";
const char* úvod = "Pìjme všichni sborem:\n";

void vypiš(const char* text)
{
	for (int i = 0; i < M; i++)
	{
		cout << text;
		this_thread::yield();
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	cout << úvod;
	//this_thread::sleep_for(1s);
	this_thread::sleep_for(chrono::milliseconds(2000));
	thread výpis1{ vypiš, verš1 };
	thread výpis2{ vypiš, verš2 };
	výpis1.join();
	výpis2.join();
	cout << verš3;
}