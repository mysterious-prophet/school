#include <iostream>
#include <stdlib.h>
#include <thread>

using namespace std;

const int M = 10;

const char* ver�1 = "ko�ka leze d�rou\n";
const char* ver�2 = "pes oknem\n";
const char* ver�3 = "nebude-li pr�et\nnezmoknem\n";

void vypi�(const char* text)
{
	for (int i = 0; i < M; i++)
	{
		cout << text;
	}
}

int main()
{
	system("CHCP 1250 > NUL");
	thread v�pis1{ vypi�, ver�1 };
	thread v�pis2{ vypi�, ver�2 };
	//v�pis1.join();
	//v�pis2.join();
	v�pis1.detach();
	v�pis2.detach();
	cout << ver�3;
}