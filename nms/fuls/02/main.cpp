#include "timeMeasure.h"

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
        // suggested search patterns for text1: "joy", "shall", "night", "delight", "heaven"
        // suggested search patterns for text2: "prince", "russia", "st. petersburg", "pavlovna", "a"
        // suggested search patterns for data.csv: "quam", "dolorem", "magnam", "sit"

        string pattern;
        string alg_type;
        int num_cycles;
        cout << "Program measures the time needed for searching for given pattern over n cycles in file: " << filename << endl;
        cout << "Search with algorithm (el, kmp, bm, ac, cw, fa): ";
        getline(cin, alg_type);
        cout << "Search for pattern: ";
        getline(cin, pattern);
        cout << "Over number of cycles: ";
        cin >> num_cycles;

        measureTime(pattern, text, size, alg_type, num_cycles);

        return 0;
    }
}
