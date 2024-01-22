#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>
#include <stdlib.h>
using namespace std;
struct node
{
	char ch;
	float p;
};
class ShannonFano
{

private:
	int tsize;
	node *ptable;
	map<char, string> bits;
	static int compare_probs(const void *elem1, const void *elem2);
	void encodeRecursize(int start, int end);
	public:
		ShannonFano();
		~ShannonFano();
	void Decode(string input, string output);
	void Encode(string input, string output);
};