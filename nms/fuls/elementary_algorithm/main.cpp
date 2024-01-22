#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

// results structure - found positions and number of matches
struct found_results{
    vector<int> found;
    int number_of_matches;
};

// reads input text into string, converts to lowercase
string readFile(const string& path){
    ifstream input(path);
    if(input){
       string content((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
       input.close();
       transform(content.begin(), content.end(), content.begin(),
           [](unsigned char c){ return tolower(c); });
       return content;
    }
    return "";
}

// implements naive searching method, returns positions if pattern found and number of matches in struct found_results
found_results elementarySearch(string pattern, string text){
    int N = text.length();
    int n = pattern.length();
    int k = 0; // number of matches
    vector<int> found(N, 0); //initialize vector of positions

    for (int i = 0; i < N-n; i++){
        int j;
        for (j = 0; j < n; j++){
            if(text[i + j] != pattern[j]){
                break;
            }
        }
        if (j == n){
            found[k] = i;
            k++;
        }
    }

    found_results result = {found, k};
    return result;
}

//output results
void writeResult(found_results result, string pattern, int size){
    int number_of_matches = result.number_of_matches;
    vector<int> found = result.found;

    cout << "\nLength of text: " << size << " characters" << endl;
    if (found[0] != 0){
        cout << number_of_matches << " match(es) for pattern '" << pattern <<"' found at positions: \n";
        for(int i = 0; i < number_of_matches; i++){
            cout << found[i] << endl;
        }
        cout << endl;
    }
    else{
        cout << "No matches for pattern '" << pattern << "' found! \n";
    }
}


int main()
{
    string filename = "text2.txt";
    string text = readFile(filename);
    int size = text.length();

    if(size == 0){
        cout << "File does not exist or is empty! \n";
        return 1;
    }
    else{
        // suggested search patterns for text1: "joy", "shall", "night", "delight", "heaven"
        // suggested search patterns for text2: "prince", "russia", "st. petersburg", "pavlovna", "a"

        string pattern;
        cout << "Program searches for input pattern in text: " << filename << endl;
        cout << "Search for pattern: ";
        getline(cin, pattern);

        // measure elapsed time
        auto start = chrono::system_clock::now();
        found_results result = elementarySearch(pattern, text);
        writeResult(result, pattern, size);
        auto end = chrono::system_clock::now();

        // calculate elapsed time
        chrono::duration<double> elapsed = end - start;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        cout << "Searching started at: " << ctime(&start_time);
        cout << "Searching finished at: " << ctime(&end_time);
        cout << "Elapsed time: " << elapsed.count() << "s \n";

        return 0;
    }
}
