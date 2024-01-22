#ifndef ACSEARCH_H
#define ACSEARCH_H

#include <bits/stdc++.h>
#include "fileOps.h"

using namespace std;

class acSearch{
    unsigned int max_states;
    const unsigned int max_chars_alphabet = 40; //possible chars: a..b, 0..9, ';', '.', ' ', '\n'
    found_results result;

    int buildMachine(string pattern, vector<int> &output, vector<int> &failure, vector<vector<int>> &go);
    int findNextState(int cur_state, char next_char, vector<int> &failure, vector<vector<int>> &go);
    void search(string pattern, string text, vector<int> output, vector<int> failure, vector<vector<int>> go);
    int getMaxStates(string pattern);
    int getCurChar(char ch);

public:
    acSearch(string pattern, string text);
    found_results getResult(){ return result; };
};

int acSearch::getMaxStates(string pattern){
    int k = 1; //sizeof (patts) / sizeof (patts[0]);
    int temp_max_states = 0;
    for (int i = 0; i < k; i++){
        temp_max_states += pattern.length();
    }
    return (temp_max_states+1);
}

acSearch::acSearch(string pattern, string text){
    max_states = getMaxStates(pattern);

    vector<int> output(max_states, 0);
    vector<int> failure(max_states, -1);
    vector<vector<int>> go(max_states, vector<int> (max_chars_alphabet, -1));

    search(pattern, text, output, failure, go);
}

void acSearch::search(string pattern, string text, vector<int> output, vector<int> failure, vector<vector<int>> go){
    buildMachine(pattern, output, failure, go);
    int k = 1; //sizeof (patts) / sizeof (patts[0]);

    int N = text.size();
    vector<int> found(N, 0);
    unsigned int l = 0;
    int cur_state = 0;
    for(int i = 0; i < N; ++i){
        cur_state = findNextState(cur_state, text[i], failure, go);

        if(output[cur_state] == 0){
            continue;
        }

        for(int j = 0; j < k; ++j){
            if(output[cur_state] & (1 << j)){
                found[l] = i - pattern.size() + 1;
                l++;
            }
        }
    }

    result = {found, l};
}

int acSearch::getCurChar(char ch){
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

int acSearch::findNextState(int cur_state, char next_char, vector<int> &failure, vector<vector<int>> &go){
    int res = cur_state;
    int temp_char = getCurChar(next_char);

    while(go[res][temp_char] == -1){
        res = failure[res];
    }

    return go[res][temp_char];
}

int acSearch::buildMachine(string pattern, vector<int> &output, vector<int> &failure, vector<vector<int>> &go){
    int states = 1;
    unsigned int k = 1; //sizeof (patts) / sizeof (patts[0]);

    for(unsigned int i = 0; i < k; ++i){
        int cur_state = 0;

        for(unsigned int j = 0; j < pattern.size(); ++j){
            int ch = getCurChar(pattern[j]);

            if(go[cur_state][ch] == -1){
                go[cur_state][ch] = states++;
            }

            cur_state = go[cur_state][ch];
        }

        output[cur_state] |= (1 << i);
    }

    queue<int> q;
    for(unsigned int i = 0; i < max_chars_alphabet; ++i){
        if(go[0][i] == -1){
            go[0][i] = 0;
        }
        if(go[max_states-1][i] == -1){
            go[max_states-1][i] = 0;
        }

        if(go[0][i] != 0){
            failure[go[0][i]] = 0;
            q.push(go[0][i]);
        }
    }

    while(q.size()){
        unsigned int state = q.front();
        q.pop();

        for(unsigned int i = 0; i < max_chars_alphabet; ++i){
            if(state == (max_states-1)){
                return states;
            }

            else if(go[state][i] != -1){
                int fail = failure[state];

                while(go[fail][i] == -1){
                    fail = failure[fail];
                }

                fail = go[fail][i];
                failure[go[state][i]] = fail;

                output[go[state][i]] |= output[fail];

                q.push(go[state][i]);
            }
        }
    }

   return states;
}





#endif // ACSEARCH_H
