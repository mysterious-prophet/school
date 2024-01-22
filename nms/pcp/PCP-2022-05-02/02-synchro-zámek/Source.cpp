//Ukázka sporu
//Blikaè, skonèí pro nekonzistenci dat   RAII

#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <Windows.h>
#include <shared_mutex>
#include <limits.h>
#include <stdio.h>

using namespace std;

const int M = INT_MAX;

mutex m;

class blikaè
{
private:
	int první = 1, druhý = 0;
	int poèítadlo = 0;
	
	void kontrola() const
	{
		if (první + druhý != 1)
		{
			string text = string("") + "Nekonzistence po " + to_string(poèítadlo) + " pøepnutích";
			MessageBoxA(0, text.data(), "Konèíme", MB_OK);
			cout << "Konèíme. " << text << endl;
			exit(1);
		}
	}
public:
	string text() const
	{
		lock_guard<mutex> zámek(m);
		char pom1[3], pom2[3];
		kontrola();   // Už není potøeba
		return string("") + to_string(první) + " " + to_string(druhý);
	}

	void prohoï()
	{
		lock_guard<mutex> zámek(m);
		druhý = první;
		první = 1 - druhý;
		poèítadlo++;
	}
};

blikaè blikadlo;
bool hotovo = false;

mt19937 generátor;

void pøepni()
{
	for (int i = 1; i < M; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(generátor() % 10));
		if (hotovo) break;
		blikadlo.prohoï();
	}
}


//pøepínaè pøepínadlo;

class vypisovaè
{
private:
	string minulé = "";
public:
	void vypiš()
	{
		while (!hotovo)
		{
			if (hotovo) break;
			string text = blikadlo.text();
			if (text != minulé)
			{
				minulé = text;
				cout << text << endl;
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	}
	void operator()()
	{
		vypiš();
	}
};

void pøerušovaè()
{
	getchar();
	hotovo = true;
}

int main()
{
	cout << "Pro ukonèení stiskni Enter" << endl;
	this_thread::sleep_for(2s);
	thread pøepínající{ pøepni };
	//pøepni();
	//vypiš();
	thread vypisující{ vypisovaè() };
	thread pøerušující{ pøerušovaè };
	pøepínající.join();
	vypisující.join();
	pøerušující.join();
	cout << "Dokonèeno jest." << endl;
}