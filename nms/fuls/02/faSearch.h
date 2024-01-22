#ifndef FASEARCH_H
#define FASEARCH_H

#include <bits/stdc++.h>
#include "fileOps.h"

using namespace std;
//#define NO_OF_CHARS 256
const unsigned int max_chars_alphabet = 40;

int getCurChar(char ch){
    int res = 0;
    if((ch - 'a') < 26 && (ch - 'a') >= 0){ // a..z
        res = ch - 'a';
    }
    else if((ch - 'a') == -65){ // char ''
        res = 26;
    }
    else if((ch - '0') < 10 && (ch - '0') >= 0){ // 0..9
        res = 27 + (ch - '0');
    }
    else if((ch - ';') == 0){ // ';'
        res = 37;
    }
    else if((ch - '.') == 0){ // '.'
        res = 38;
    }
    else if((ch - '\n') == 0){ // '\n'
        res = 39;
    }

    return res;
}

/*int getNextState(string pattern, int n, int state, int ch) {
    // If the character ch is same as next character
    // in pattern,then simply increment state
    int cur_char = getCurChar(pattern[state]);
    if (state < n && ch == cur_char)
        return (state+1);

    // next_state finally contains the longest prefix
    // which is also suffix in "pat[0..state-1]ch"

    // Start from the largest possible value
    // and stop when you find a prefix which
    // is also suffix
    int i = 0;
    for (int next_state = state; next_state > 0; next_state--){
        cur_char = getCurChar(pattern[next_state-1]);
        if (cur_char == ch){
            for (i = 0; i < next_state-1; i++){
                if (pattern[i] != pattern[state-next_state+1+i]){
                    break;
                }
            }

            if (i == next_state-1){
                return next_state;
            }
        }
    }

    return 0;
}

 This function builds the TF table which represents4
    Finite Automata for a given pattern
void compTransFunc(string pattern, unsigned int n, vector<vector<int>> &TF){
    //int state, ch;
    for (unsigned int state = 0; state <= n; ++state){
        for (unsigned int ch = 0; ch < max_chars_alphabet; ++ch){
            TF[state][ch] = getNextState(pattern, n, state, ch);
        }
    }
}


 Prints all occurrences of pat in txt
found_results faSearch(string pattern, string text){
    int n = pattern.size();
    int N = text.size();
    unsigned int k = 0;
    vector<int> found(N, 0);

    //int TF[n+1][NO_OF_CHARS];
    vector<vector<int>> TF(n+1, vector<int>(max_chars_alphabet, 0));

    compTransFunc(pattern, n, TF);

    // Process text over FA.
    int state = 0;
    for (int i = 0; i < N; i++){
        state = TF[state][getCurChar(text[i])];
        if (state == n){
            found[k] = i-n+1;
            k++;
        }
    }

    found_results result = {found, k};
    return result;
}*/


/* This function builds the TF table
which represents Finite Automata for a
given pattern */
void computeTransFun(string pattern, unsigned int n, vector<vector<int>> &TF)
{
    unsigned int i, lps = 0, x;

    // Fill entries in first row
    for (x = 0; x < max_chars_alphabet; x++){
        TF[0][x] = 0;
    }
    TF[0][getCurChar(pattern[0])] = 1;

    // Fill entries in other rows
    for (i = 1; i <= n; i++) {
        // Copy values from row at index lps
        for (x = 0; x < max_chars_alphabet; x++)
            TF[i][x] = TF[lps][x];

        // Update the entry corresponding to this character
        TF[i][getCurChar(pattern[i])] = i + 1;

        // Update lps for next row to be filled
        if (i < n)
            lps = TF[lps][getCurChar(pattern[i])];
    }
}

/* Prints all occurrences of pat in txt */
found_results faSearch(string pattern, string text)
{
    unsigned int n = pattern.size();
    unsigned int N = text.size();
    unsigned int k = 0;
    vector<int> found(N, 0);

    //int TF[M + 1][NO_OF_CHARS];
    vector<vector<int>> TF(n+1, vector<int>(max_chars_alphabet, 0));

    computeTransFun(pattern, n, TF);

    // process text over FA.
    unsigned int j = 0;
    for (unsigned int i = 0; i < N; i++) {
        j = TF[j][getCurChar(text[i])];
        if (j == n) {
            found[k] = i-n+1;
            k++;
        }
    }

    found_results result = {found, k};
    return result;
}


#endif // FASEARCH_H
