#include "fileOps.h"

using namespace std;


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


void writeFile(const string encoded, const string decoded, const string comp_type){
      ofstream output;
      string filename = "output_100mb_" + comp_type + ".csv";
      output.open(filename, ios::out);
/*
      cout << "Length of " + comp_type + " encoded text: " << encoded.length() << endl;
      cout << "Length of " + comp_type + " decoded text: " << decoded.length() << endl;
      cout << comp_type + " encoded text: \n";
      cout << encoded;
      cout << "\n" + comp_type + " decoded text: \n";
      cout << decoded << endl;*/

      output << "\nLength of " + comp_type + " encoded text: " << encoded.length() << endl;
      output << "Length of " + comp_type + " decoded text: " << decoded.length() << endl;
      output << comp_type + " encoded text: \n";
      output << encoded;
      output << "\n" + comp_type + " decoded text: \n";
      output << decoded << endl;
      output.close();
}

void writeElapsedTime(elapsed_time elapsed_struct){
    time_t start_time = elapsed_struct.start_time;
    time_t end_time = elapsed_struct.end_time;
    chrono::duration<double> elapsed = elapsed_struct.elapsed;
    string alg_type = elapsed_struct.alg_type;

    string filename = "measure_100mb_" + alg_type + ".csv";
    ofstream output(filename);
    output << "\nCompression started at: " << ctime(&start_time);
    output << "Compression finished at: " << ctime(&end_time);
    output << "Elapsed time: " << elapsed.count() << " s \n";

    /*cout << "\nSearching started at: " << ctime(&start_time);
    cout << "Searching finished at: " << ctime(&end_time);
    cout << "Average elapsed time in 1 cycle out of " << num_cycles << " cycles: " << elapsed.count() << " s \n";*/
}
