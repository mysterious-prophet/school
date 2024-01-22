#include <iostream>
#include <string>
#include <fstream>
#include "CompressWizard.h"

using namespace std;



int main() {

	CompressWizard driver("1mb.txt", "output.txt","output_dec.txt", false);
//	driver.RLECompress();
	cout<<endl << "rle decompressed file:" << endl;
//	driver.RLEDecompress();
	cout << endl;

	//driver.SFCompress();
	cout << endl << endl << "shannon fano decompressed file:" << endl;
//	driver.SFDecompress();
	//driver.HuffmanCompress();
	//driver.HuffmanDecompress();
 	driver.FGKCompress();
	//driver.FGKDecompress();
	//driver.VitterCompress();

	system("pause");
	return 0;
}

