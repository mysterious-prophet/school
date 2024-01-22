#include <iostream>
#include <stdlib.h>
#include <thread>

// soub�h p�i v�stupu

using namespace std;

const int M = 10;

const char* ver�1 = "ko�ka leze d�rou";
const char* ver�2 = "pes oknem";
const char* ver�3 = "nebude-li pr�et\nnezmoknem";

void vypi�(const char* text)
{
	for (int i = 0; i < M; i++)
	{
		cout << text << endl;
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	thread v�pis1{ vypi�, ver�1 };
	thread v�pis2{ vypi�, ver�2 };
	v�pis1.join();
	v�pis2.join();
	cout << ver�3 << endl;
}