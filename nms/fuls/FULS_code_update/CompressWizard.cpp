#include "CompressWizard.h"
#include <iostream>
#include <fstream>

using namespace std;

std::string CompressWizard::RLEEncode(std::string str)
{
	int n = str.length();
	string result = "";
	for (int i = 0; i < n; i++) {
		// Count occurrences of current character
		int count = 1;
		while (i < n - 1 && str[i] == str[i + 1]) {
			count++;
			i++;
		}
		result.append(to_string(count));
		result.append(1, str[i]);

	}
	// Print character and its count
	if (debug) cout << result << endl;
	return result;
}

std::string CompressWizard::RLEDecode(std::string str)
{
	int n = str.length();
	string result = "";
	for (int i = 0; i < n - 1; i++) {
		if (!isdigit(str[i])) continue;
		int k = 1;
		for (; k < str.length()-i; k++) { if (!isdigit(str[i+k])) break; }

		// remove the first chars, which aren't digits
		string substr = str.substr(i,k);

		// convert the remaining text to an integer
		int num = atoi(substr.c_str());
		for (int j = 0; j < num; j++) {
			result.append(1, str[i+k]);
		}
	}
	
	// Print character and its count
	if (debug) cout << result << endl;
	return result;
}

void CompressWizard::print()
{
	cout << "File before compression:" << endl;
	// Create a text string, which is used to output the text file
	string line;
	// Read from the text file
	ifstream inStream(input);
	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {

		cout << line << endl;
	}
	// Close the file
	inStream.close();

}


CompressWizard::CompressWizard(string _input, string _output, string _outputDec, bool _debug) :input(_input), output(_output), outputDec(_outputDec), debug(_debug)
{
}

void CompressWizard::RLECompress()
{
	print();
	cout <<endl<< "rle compressed file:" << endl;
	// Create a text string, which is used to output the text file
	string line;

	// Read from the text file
	ifstream inStream(input);
	ofstream outStream(output);


	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {

		outStream << RLEEncode(line) << endl;;
	}

	// Close the file
	inStream.close();
	outStream.close();
}


void CompressWizard::RLEDecompress()
{
	// Create a text string, which is used to output the text file
	string line;

	// Read from the text file
	ifstream inStream(output);
	ofstream outStream(outputDec);


	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {

		outStream << RLEDecode(line)<<endl;
	}

	// Close the file
	inStream.close();
	outStream.close();
}

void CompressWizard::SFCompress()
{
	print();
	ShannonFano f;
	f.Encode(input, output);

	cout << "Shannon fano after compression" << endl;
	string line;
	// Read from the text file
	ifstream inStream(output);
	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {
		cout << line << endl;
	}
	// Close the file
	inStream.close();
}

void CompressWizard::SFDecompress()
{
	ShannonFano f;
	f.Decode(output, outputDec);
	// Create a text string, which is used to output the text file
	string line;
	// Read from the text file
	ifstream inStream(outputDec);

	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {
		cout << line << endl;
	}
	// Close the file
	inStream.close();
}

void CompressWizard::HuffmanCompress()
{
	print();
	// Create a text string, which is used to output the text file
	string line;

	// Read from the text file
	ifstream inStream(input);
	ofstream outStream(output);

	Huffman f;
	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {

		f.Encode(line, output, outputDec);
	}
	ifstream outEnc(output);
	cout << "huffman compressed:" << endl;

	while (getline(outEnc, line)) {
		cout << line << endl;
	}
	// Close the file
	inStream.close();
	outEnc.close();
	outStream.close();
}

void CompressWizard::HuffmanDecompress()
{
	
	// Create a text string, which is used to output the text file
	string line;

	// Read from the text file
	ifstream inStream(outputDec);
	cout << "huffman decompressed:" << endl;
	Huffman f;
	// Use a while loop together with the getline() function to read the file line by line
	while (getline(inStream, line)) {

		cout << line << endl;
	}
	
	inStream.close();
}



CompressWizard::~CompressWizard()
{
	ifstream in(outputDec);
	string line;
	cout << "huffman decompressed:" << endl;
	while (getline(in, line)) {
		cout << line << endl;
	}
	in.close();
}

