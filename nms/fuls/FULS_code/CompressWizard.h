#include <string>
#include <sstream>
#include <bitset>
#include "ShannonFano.h"
#include "Huffman.h"
#include "FGK.cpp"
#include <algorithm>
#include <chrono>
#pragma once


class CompressWizard
{
	std::string input;
	std::string output;
	std::string outputDec;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	bool debug;
	std::string RLEEncode(std::string str);
	std::string RLEDecode(std::string str);
	void print();
	string binToAs(string data) {
		std::stringstream sstream(data);
		std::string output;
		while (sstream.good())
		{
			std::bitset<8> bits;
			sstream >> bits;
			char c = char(bits.to_ulong());
			output += c;
		}
		std::cout << output << std::endl;
		return output;

	}
	void toBinary(string file);
	void tic()
	{
		begin = std::chrono::steady_clock::now();
	}

	void tac()
	{
		end = std::chrono::steady_clock::now();
		std::cout << "Estimated time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << std::endl;

	}
public:
	CompressWizard(std::string _input, std::string _output, std::string _outputDec, bool debug=true);
	void RLECompress();
	void RLEDecompress();
	void SFCompress();
	void SFDecompress();
	void HuffmanCompress();
	void HuffmanDecompress();
	void FGKCompress();
	void FGKDecompress();
	void VitterCompress();
	~CompressWizard();
};

