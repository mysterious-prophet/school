
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <condition_variable>
#include <mutex>

using namespace std;
using namespace std::this_thread;

int M = 10;

const char* verš1 = "koèka leze dírou\n";
const char* verš2 = "pes oknem\n";

condition_variable koèka;
condition_variable pes;
mutex mtx;
bool vypsána_koèka = false;
bool vypsán_pes = true;

void vypiš_koèku(const char* txt)
{
	for (int i = 0; i < M; i++)
	{
		unique_lock<mutex> zámek(mtx);
		while (!vypsán_pes)
		{
			pes.wait(zámek);
		}
		cout << txt;
		vypsána_koèka = true;
		vypsán_pes = false;
		koèka.notify_one();
	}
}

void vypiš_psa(const char* txt)
{
	for (int i = 0; i < M; i++)
	{
		unique_lock<mutex> zámek(mtx);
		while (!vypsána_koèka)
		{
			koèka.wait(zámek);
		}
		cout << txt;
		vypsán_pes = true;
		vypsána_koèka = false;
		pes.notify_one();
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	cout << "Pìjme všichni sborem:" << endl;
	thread t1{ vypiš_koèku, verš1 };
	thread t2{ vypiš_psa, verš2 };
	t1.join();
	t2.join();
	cout << "nebude-li pršet\nnezmoknem\n" << endl;
}