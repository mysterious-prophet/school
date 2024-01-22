#include "Huffman.h"
#include <fstream>
using namespace std;

#define EMPTY_STRING ""

Huffman::Huffman()
{
}



// Function to allocate a new tree node
Node* Huffman::getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}


// Utility function to check if Huffman Tree contains only a single node
bool Huffman::isLeaf(Node* root) {
	return root->left == nullptr && root->right == nullptr;
}

// Traverse the Huffman Tree and store Huffman Codes in a map.
void Huffman::encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (isLeaf(root)) {
		huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// Traverse the Huffman Tree and decode the encoded string
void Huffman::decode(Node* root, int &index, string str, string output)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (isLeaf(root))
	{
		ofstream f(output, ofstream::app);
		f << root->ch;
		f.close();
		return;
	}

	index++;

	if (str[index] == '0') {
		decode(root->left, index, str, output);
	}
	else {
		decode(root->right, index, str, output);
	}
}

// Builds Huffman Tree and decodes the given input text
void Huffman::Encode(string text, string output, string outputDec)
{
	// base case: empty string
	if (text == EMPTY_STRING) {
		return;
	}

	// count the frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of the Huffman tree
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of the highest priority
		// (the lowest frequency) from the queue

		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();    pq.pop();

		// create a new internal node with these two nodes as children and
		// with a frequency equal to the sum of the two nodes' frequencies.
		// Add the new node to the priority queue.

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// `root` stores pointer to the root of Huffman Tree
	Node* root = pq.top();

	// Traverse the Huffman Tree and store Huffman Codes
	// in a map. Also, print them
	unordered_map<char, string> huffmanCode;
	encode(root, EMPTY_STRING, huffmanCode);

	cout << "Huffman Codes are:\n" << endl;
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << endl;
	}

	//cout << "\nThe original string is:\n" << text << endl;

	// Print encoded string
	string str;
	for (char ch : text) {
		str += huffmanCode[ch];
	}
	ofstream outDecStream(outputDec);
	ofstream outStream(output);
	outStream << str << endl;
	outStream.close();
	//cout << "\nhuffman decoded:\n";

	if (isLeaf(root))
	{
		// Special case: For input like a, aa, aaa, etc.
		string res = "";
		while (root->freq--) {
			res += root->ch;
		}
		outDecStream << res;
		outDecStream.close();
	}
	else {
		// Traverse the Huffman Tree again and this time,
		// decode the encoded string
		int index = -1;
		while (index < (int)str.size() - 1) {
			decode(root, index, str, outputDec);
		}
	}
}


Huffman::~Huffman()
{
}
