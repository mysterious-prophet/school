#ifndef KMPSEARCH_H
#define KMPSEARCH_H

#include "fileOps.h"

void computeLPS(string pattern, int n, vector<int> &lps){
    int prev_length = 0;

    lps[0] = 0;

    int i = 1;
    while(i < n){
        if(pattern[i] == pattern[prev_length]){
            prev_length++;
            lps[i] = prev_length;
            i++;
        }
        else{
            if(prev_length != 0){
                prev_length = lps[prev_length-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

found_results kmpSearch(string pattern, string text){
    unsigned int N = text.length();
    unsigned int n = pattern.length();
    unsigned int k = 0;
    vector<int> found(N, 0);

    vector<int> lps(n, 0);

    computeLPS(pattern, n, lps);

    unsigned int i = 0;
    unsigned int j = 0;
    while(i < N){
        if(pattern[j] == text[i]){
            i++;
            j++;
        }
        if(j == n){
            found[k] = i - j;
            k++;
            j = lps[j-1];
        }
        else if(i < N && pattern[j] != text[i]){
            if(j != 0){
                j = lps[j-1];
            }
            else{
                i++;
            }
        }
    }

    found_results result = {found, k};
    return result;
}

#endif // KMPSEARCH_H
