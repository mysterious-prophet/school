#include <string>
#include "ShannonFano.h"
#include "Huffman.h"
#pragma once


class CompressWizard
{
	std::string input;
	std::string output;
	std::string outputDec;
	bool debug;
	std::string RLEEncode(std::string str);
	std::string RLEDecode(std::string str);
	void print();


public:
	CompressWizard(std::string _input, std::string _output, std::string _outputDec, bool debug=true);
	void RLECompress();
	void RLEDecompress();
	void SFCompress();
	void SFDecompress();
	void HuffmanCompress();
	void HuffmanDecompress();
	~CompressWizard();
};

