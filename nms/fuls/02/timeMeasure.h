#ifndef TIMEMEASURE_H
#define TIMEMEASURE_H

#include "fileOps.h"
#include "elSearch.h"
#include "kmpSearch.h"
#include "bmSearch.h"
#include "acSearch.h"
#include "cwSearch.h"
#include "faSearch.h"

using namespace std;

found_results measuring(string pattern, string text, string alg_type, int num_cycles){
    if(alg_type.compare("el") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            found_results result = elSearch(pattern, text);
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        found_results result = elSearch(pattern, text);
        return result;
    }
    else if(alg_type.compare("kmp") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            found_results result = kmpSearch(pattern, text);
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        found_results result = kmpSearch(pattern, text);
        return result;
    }
    else if(alg_type.compare("bm") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            found_results result = bmSearch(pattern, text);
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        found_results result = bmSearch(pattern, text);
        return result;
    }
    else if(alg_type.compare("ac") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            acSearch ac(pattern, text);
            found_results result = ac.getResult();
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        acSearch ac(pattern, text);
        found_results result = ac.getResult();
        return result;
    }
    else if(alg_type.compare("cw") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            cwSearch cw(pattern, text);
            found_results result = cw.getResult();
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        cwSearch cw(pattern, text);
        found_results result = cw.getResult();
        return result;
    }
    else if(alg_type.compare("fa") == 0){
        auto start = chrono::system_clock::now();
        for(int i = 0; i < num_cycles; i++){
            found_results result = faSearch(pattern, text);
        }
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed = (end - start)/num_cycles;
        time_t start_time = chrono::system_clock::to_time_t(start);
        time_t end_time = chrono::system_clock::to_time_t(end);

        elapsed_time elapse_struct = {start_time, end_time, elapsed, num_cycles, alg_type};
        writeElapsedTime(elapse_struct);

        found_results result = faSearch(pattern, text);
        return result;
    }
    else{
        cout << "\nPlease enter a valid algorithm name! \n";
        EXIT_FAILURE;
    }
}

// measure elapsed time
void measureTime(string pattern, string text, int size, string alg_type, int num_cycles){
    found_results result = measuring(pattern, text, alg_type, num_cycles);
    writeResult(result, pattern, size, alg_type);
}

#endif // TIMEMEASURE_H
