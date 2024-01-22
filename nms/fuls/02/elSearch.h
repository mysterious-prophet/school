#ifndef ELEMENTARYSEARCH_H
#define ELEMENTARYSEARCH_H

#include "fileOps.h"

using namespace std;

// implements naive searching method, returns positions if pattern found and number of matches in struct found_results
found_results elSearch(string pattern, string text){
    unsigned int N = text.length();
    unsigned int n = pattern.length();
    unsigned int k = 0; // number of matches
    vector<int> found(N, 0); //initialize vector of positions

    for (unsigned int i = 0; i < N-n; i++){
        unsigned int j;
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

#endif // ELEMENTARYSEARCH_H
