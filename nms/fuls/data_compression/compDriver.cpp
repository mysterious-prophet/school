#include<string>
#include<iostream>
#include "compDriver.h"
#include "fileOps.h"
#include "rle.h"
#include "sf.h"
#include "huffstat.h"
#include "fgk.h"
#include "vit.h"
#include "lz77.h"
#include "lz78.h"

using namespace std;



void run(string text, string comp_type){
    if(comp_type.compare("rle") == 0){
        auto start = chrono::system_clock::now();
        rle r;
        string encoded = r.encode(text);
        auto end = chrono::system_clock::now();
        //string decoded = r.decode(encoded);
        string decoded = "";

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);
        writeFile(encoded, decoded, comp_type);

    }
    else if(comp_type.compare("sf") == 0){
        sf s;
        auto start = chrono::system_clock::now();
        string encoded = s.encode(text);
        auto end = chrono::system_clock::now();
        //string decoded = s.decode(encoded);
        string decoded = "";

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);

        writeFile(encoded, decoded, comp_type);

    }
    else if(comp_type.compare("hms") == 0){
        huffStat hs(text);

    }
    else if(comp_type.compare("fgk") == 0){
        auto start = chrono::system_clock::now();
        fgk f("data_100bm.csv", "output_100mb_fgk.csv", 0);
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);
    }
    else if(comp_type.compare("vit") == 0){
        std::ifstream in;
        in.open("data_100mb.csv", std::ios::in | std::ios::binary);
        std::ofstream out;
        out.open("output_100mb_vitter.csv", std::ios::out | std::ios::binary);
        auto start = chrono::system_clock::now();
        vitter::compress(&in, &out);
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);
    }
    else if(comp_type.compare("lz77") == 0){
        LZ77 l;
        std::ofstream out;
        out.open("output_100mb_lz77.csv", std::ios::out | std::ios::binary);
        auto start = chrono::system_clock::now();
        l.LZ77_ENC(text, out);
        //string encoded = l.driver(text, 1);
        auto end = chrono::system_clock::now();
        string decoded = "";

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);

        //writeFile(encoded, decoded, comp_type);
    }
    else if(comp_type.compare("lz78") == 0){
        LZ78 l;
        auto start = chrono::system_clock::now();
        l.compress("data_100mb.csv", "output_100mb_lz78.csv");
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start);
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);
        elapsed_time elapse_struct = {start_time, end_time, elapsed, comp_type};

        writeElapsedTime(elapse_struct);
    }
    else{
        cout << "\nPlease enter a valid algorithm name! \n";
    }
}
