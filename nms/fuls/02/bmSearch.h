#ifndef BMSEARCH_H
#define BMSEARCH_H

#include "fileOps.h"

using namespace std;

void badCharHeur(string pattern, int n, vector<int> &badchar){
    for (int i = 0; i < n; i++){
            badchar[(int) pattern[i]] = i;
    }
}

found_results bmSearch(string pattern, string text){
    unsigned int N = text.length();
    unsigned int n = pattern.length();
    unsigned int k = 0; // number of matches
    vector<int> found(N, 0); //initialize vector of positions
    vector<int> badchar(256, -1);

    badCharHeur(pattern, n, badchar);

    int shift = 0;
    while(shift <= (N-n)){
        int j = n-1;
        while(j >= 0 && pattern[j] == text[shift+j]){
            j--;
        }

        if(j < 0){
            found[k] = shift;
            k++;
            shift += (shift+n < N) ? n-badchar[text[shift+n]] : 1;
        }
        else{
            shift += max(1, j-badchar[text[shift+j]]);
        }
    }

    found_results result = {found, k};
    return result;
}

#endif // BMSEARCH_H
