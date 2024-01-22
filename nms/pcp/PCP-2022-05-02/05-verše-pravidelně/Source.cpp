
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <condition_variable>
#include <mutex>

using namespace std;
using namespace std::this_thread;

int M = 10;

const char* ver�1 = "ko�ka leze d�rou\n";
const char* ver�2 = "pes oknem\n";

condition_variable ko�ka;
condition_variable pes;
mutex mtx;
bool vyps�na_ko�ka = false;
bool vyps�n_pes = true;

void vypi�_ko�ku(const char* txt)
{
	for (int i = 0; i < M; i++)
	{
		unique_lock<mutex> z�mek(mtx);
		while (!vyps�n_pes)
		{
			pes.wait(z�mek);
		}
		cout << txt;
		vyps�na_ko�ka = true;
		vyps�n_pes = false;
		ko�ka.notify_one();
	}
}

void vypi�_psa(const char* txt)
{
	for (int i = 0; i < M; i++)
	{
		unique_lock<mutex> z�mek(mtx);
		while (!vyps�na_ko�ka)
		{
			ko�ka.wait(z�mek);
		}
		cout << txt;
		vyps�n_pes = true;
		vyps�na_ko�ka = false;
		pes.notify_one();
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	cout << "P�jme v�ichni sborem:" << endl;
	thread t1{ vypi�_ko�ku, ver�1 };
	thread t2{ vypi�_psa, ver�2 };
	t1.join();
	t2.join();
	cout << "nebude-li pr�et\nnezmoknem\n" << endl;
}