#include <iostream>
#include <stdlib.h>
#include <thread>
#include <chrono>

using namespace std;

//using namespace std::chrono;
//using namespace std::literals::chrono_literals;

const int M = 10;

const char* ver�1 = "ko�ka leze d�rou\n";
const char* ver�2 = "pes oknem\n";
const char* ver�3 = "nebude-li pr�et\nnezmoknem\n";
const char* �vod = "P�jme v�ichni sborem:\n";

void vypi�(const char* text)
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
	cout << �vod;
	//this_thread::sleep_for(1s);
	this_thread::sleep_for(chrono::milliseconds(2000));
	thread v�pis1{ vypi�, ver�1 };
	thread v�pis2{ vypi�, ver�2 };
	v�pis1.join();
	v�pis2.join();
	cout << ver�3;
}