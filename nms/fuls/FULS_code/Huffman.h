#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;
// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};
// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node* l, const Node* r) const
	{
		// the highest priority item has the lowest frequency
		return l->freq > r->freq;
	}
};

class Huffman
{
	Node* getNode(char ch, int freq, Node* left, Node* right);
	bool isLeaf(Node* root);
	void encode(Node* root, string str, unordered_map<char, string> &huffmanCode);
	void decode(Node* root, int &index, string str, string output);
public:
	Huffman();
	void Encode(string text,string output, string outputDec);
	~Huffman();
};

