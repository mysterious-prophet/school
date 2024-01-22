#ifndef FILEOPS_H
#define FILEOPS_H

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

struct found_results{
    vector<int> found;
    unsigned int number_of_matches;
};

struct elapsed_time{
    time_t start_time;
    time_t end_time;
    chrono::duration<double> elapsed;
    int num_cycles;
    string alg_type;
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

//output results
void writeResult(found_results result, string pattern, int size, string alg_type){
    int number_of_matches = result.number_of_matches;
    //vector<int> found = result.found;
    ofstream output;
    string filename = "output_100mb_" + alg_type + ".csv";
    output.open(filename, ios::app);

    cout << "\nLength of text: " << size << " characters" << endl;
    if (result.found[1] != 0){
        cout << number_of_matches << " match(es) for pattern '" << pattern <<"' found with " << alg_type << " algorithm!\n"; // at positions: \n";
        /*for(int i = 0; i < number_of_matches; i++){
            cout << found[i] << endl;
        }
        cout << endl;*/
    }
    else{
        cout << "No matches for pattern '" << pattern << "' found! \n";
    }

    output << "\nLength of text: " << size << " characters" << endl;
    if (result.found[0] != 0){
        output << number_of_matches << " match(es) for pattern '" << pattern <<"' found with " << alg_type << " algorithm!\n"; // at positions: \n";
        for(int i = 0; i < number_of_matches; i++){
            output << result.found[i] << endl;
        }
        output << endl;
    }
    else{
        output << "No matches for pattern '" << pattern << "' found! \n";
    }

    output.close();
}


void writeElapsedTime(elapsed_time elapsed_struct){
    time_t start_time = elapsed_struct.start_time;
    time_t end_time = elapsed_struct.end_time;
    chrono::duration<double> elapsed = elapsed_struct.elapsed;
    int num_cycles = elapsed_struct.num_cycles;
    string alg_type = elapsed_struct.alg_type;

    string filename = "output_100mb_" + alg_type + ".csv";
    ofstream output(filename);
    output << "\nSearching started at: " << ctime(&start_time);
    output << "Searching finished at: " << ctime(&end_time);
    output << "Average elapsed time in 1 cycle out of " << num_cycles << " cycles: " << elapsed.count() << " s \n";

    cout << "\nSearching started at: " << ctime(&start_time);
    cout << "Searching finished at: " << ctime(&end_time);
    cout << "Average elapsed time in 1 cycle out of " << num_cycles << " cycles: " << elapsed.count() << " s \n";
}
#endif // FILEOPS_H
