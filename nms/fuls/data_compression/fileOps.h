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

struct elapsed_time{
    time_t start_time;
    time_t end_time;
    chrono::duration<double> elapsed;
    string alg_type;
};

string readFile(const string& path);
void writeFile(const string encoded, const string decoded, const string comp_type);
void writeElapsedTime(elapsed_time elapsed_struct);


#endif // FILEOPS_H
