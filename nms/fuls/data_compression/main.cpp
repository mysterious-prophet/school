#include <iostream>
#include "fileOps.h"
#include "compDriver.h"

using namespace std;

int main()
{
    string filename = "data_100mb.csv";
    string text = readFile(filename);
    int size = text.length();

    if(size == 0){
        cout << "File does not exist or is empty! \n";
        return 1;
    }
    else{
        string comp_type;

        cout << "Program compresses and decompresses input data with selected algorithm \n";
        cout << "(De)compress with algorithm (rle, sf, hms, fgk, vit, lz77, lz78): ";
        getline(cin, comp_type);

        run(text, comp_type);

        return 0;
    }

}
