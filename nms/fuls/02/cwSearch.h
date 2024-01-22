#ifndef CWSEARCH_H
#define CWSEARCH_H

#include <bits/stdc++.h>
#include "fileOps.h"
#include <algorithm>

class cwSearch{
private:
    unsigned int max_states = 0; //max number of states in automaton
    const unsigned int max_chars_alphabet = 40; // number of chars in alphabet - a..z, 0..9, ".", ";", "\n", ""
    found_results result; // result structure - positions and number of matches
    int wmin; // min and max length of searched patterns
    int wmax;

    //preprocessing
    int buildMachine(const string pattern, vector<int> &output, vector<int> &failure, vector<vector<int>> &go, vector<int> &state_depth, vector<int> &set2, vector<int> &charADepth, vector<int> &shift1, vector<int> &shift2);
    //find next state based on current state and next char in text
    int findNextState(int cur_state, int next_char, vector<int> &failure, vector<vector<int>> &go);
    // search
    void search(const string pattern, const string text, vector<int> output, vector<int> failure, vector<vector<int>> go, vector<int> state_depth, vector<int> set2, vector<int> charADepth, vector<int> shift1, vector<int> shift2);

    int getMaxStates(const string pattern); //get max number of states in trie
    int getCurChar(const char ch); // map next char in text onto 0..39
    string reversePatterns(const string pattern); // reverse string for cw
    int calcShift1(int cur_state, vector<int> &failure, vector<int> &state_depth); // calculate shift1
    int calcShift2(int cur_state, vector<int> &set2, vector<int> &state_depth); // calculate shift2
    int charADepth(int ch, vector<vector<int>> &go); // get min depth of state that is accessed by inputing char ch
    int getStateDepth(int cur_state, vector<vector<int>> &go); // get depth of current state
    int getWMin(const string pattern); // return length of shortest pattern
    int getWmax(const string pattern); // return lenght of longest pattern

public:
    // contructor and getResult for fileops.h access
    cwSearch(const string pattern, const string text);
    found_results getResult(){ return result; };
};

// max states is number of chars of all patterns + 1
int cwSearch::getMaxStates(const string pattern){
    int k = 1; //sizeof (patts) / sizeof (patts[0]);
    int max_states = 0;
    // number of states upper limit is length of all searched patterns
    for (int i = 0; i < k; i++){
        max_states += pattern.length();
    }
    return (max_states + 1);
}

// find shortest word and return lenght
int cwSearch::getWMin(const string pattern){
    return pattern.length();
}

// find longest word and return length
int cwSearch::getWmax(const string pattern){
    return pattern.length();
}


// get depth of current state
int cwSearch::getStateDepth(int cur_state, vector<vector<int>> &go){
    if(cur_state == 0){
        return 0;
    }
    else{
        for(unsigned int i = 0; i < max_states-1; i++){
            for(unsigned int j = 0; j < max_chars_alphabet; j++){
                if(go[i][j] == cur_state){
                    return i+1;
                }
            }
        }
    }
}


//reverse pattern for cw automaton building
string cwSearch::reversePatterns(const string pattern){
    return string(pattern.rbegin(), pattern.rend());
}


// initialize vectors and other values
cwSearch::cwSearch(const string pattern, const string text){
    max_states = getMaxStates(pattern);

    // output, failure (set1), goto function inicialization - from ac
    vector<int> output(max_states, 0);
    vector<int> failure(max_states, -1);
    vector<vector<int>> go(max_states, vector<int> (max_chars_alphabet, -1));

    // depth of each state, set2, charA, shift1, shift2 - cw
    vector<int> state_depth(max_states, 0);
    vector<int> set2(max_states, 0);
    vector<int> charA(max_chars_alphabet, 0);
    vector<int> shift1(max_states, 1);
    vector<int> shift2(max_states, 1);

    // max and min length of searched patterns
    wmax = getWmax(pattern);
    wmin = getWMin(pattern);

    // reverse pattern
    const string pattern_rev = reversePatterns(pattern);

    search(pattern_rev, text, output, failure, go, state_depth, set2, charA, shift1, shift2);
}


// shift1 as defined by cw ver. B
int cwSearch::calcShift1(int cur_state, vector<int> &failure, vector<int> &state_depth){
    if(cur_state == 0){
        return 1;
    }
    else{
        int depth = state_depth[failure[cur_state]] - state_depth[cur_state];
        return min(wmin, depth);
    }
}


// shift2 as defined by cw ver. B
int cwSearch::calcShift2(int cur_state, vector<int> &set2, vector<int> &state_depth){
    if(cur_state == 0){
        return wmin;
    }
    else{
        int depth = state_depth[set2[cur_state]] - state_depth[cur_state];
        return min(0, depth);
    }
}


// char(a) as defined by cw ver. B
int cwSearch::charADepth(int ch, vector<vector<int>> &go){
    for(unsigned int i = 0; i < max_states-1; i++){
        if(go[i][ch] > 0){
            int depth = i+1;
            return min(depth, wmin+1);
        }
    }
    return 0;
}


void cwSearch::search(const string pattern, const string text, vector<int> output, vector<int> failure, vector<vector<int>> go, vector<int> state_depth, vector<int> set2, vector<int> charA, vector<int> shift1, vector<int> shift2){
    // preprocessing
    buildMachine(pattern, output, failure, go, state_depth, set2, charA, shift1, shift2);

    //unsigned int k = 1; //sizeof (patts) / sizeof (patts[0]);
    int N = text.size();
    int n = pattern.size();
    vector<int> found(N, 0); // found results

    unsigned int l = 0; //number of matches
    int cur_state = 0; // current state in the trie
    int i = wmin-1; // starting position in text
    int j = 0; // iterator over pattern
    int temp_char = 0; // next char in text
    int shift = 1; // initial shift value

    while(i <= N){
        temp_char = getCurChar(text[i-j]);
        while(findNextState(cur_state, temp_char, failure, go) > 0 && j < n){
            cur_state = findNextState(cur_state, temp_char, failure, go);
            j++;

            if(output[cur_state] != 0){
                found[l] = i - j + 1;
                l++;
            }

            temp_char = getCurChar(text[i-j]);
        }

        shift = min(shift2[cur_state], max(shift1[cur_state], charA[temp_char]-j-1));
        if(shift > 0){
            i += shift;
        }
        else{
            i += 1;
        }

        j = 0;
        cur_state = 0;
    }

    result = {found, l};
}


int cwSearch::getCurChar(const char ch){
    // map next char onto 0..39
    int res = 0;
    if((ch - 'a') < 26 && (ch - 'a') >= 0){ // a..z
        res = ch - 'a';
    }
    else if((ch - 'a') == -65){ // ''
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


int cwSearch::findNextState(int cur_state, int next_char, vector<int> &failure, vector<vector<int> > &go){
    int res = cur_state;

    while(go[res][next_char] == -1){
        res = failure[res];
    }

    return go[res][next_char];
}


int cwSearch::buildMachine(const string pattern, vector<int> &output, vector<int> &failure, vector<vector<int>> &go, vector<int> &state_depth, vector<int> &set2, vector<int> &charA, vector<int> &shift1, vector<int> &shift2){
    int states = 1; // there's only the root in the beginning
    unsigned int k = 1; //sizeof (patts) / sizeof (patts[0]);

    for(unsigned int i = 0; i < k; ++i){
        int cur_state = 0;

        for(unsigned int j = 0; j < pattern.size(); ++j){
            int ch = getCurChar(pattern[j]);

            // define goto function
            if(go[cur_state][ch] == -1){
                go[cur_state][ch] = states++;
            }

            // move forward in trie
            cur_state = go[cur_state][ch];
        }

        // define output function for current pattern
        output[cur_state] |= (1 << i);
    }

    queue<int> q;

    for(unsigned int i = 0; i < max_chars_alphabet; ++i){
        // goto root for chars that lead nowhere
        if(go[0][i] == -1){
            go[0][i] = 0;
        }

        // goto root for chars in final state
        if(go[max_states-1][i] == -1){
            go[max_states-1][i] = 0;
        }

        // failure of states of depth 1 is 0
        if(go[0][i] != 0){
            failure[go[0][i]] = 0;
            q.push(go[0][i]);
        }

        // calc charA(i) for cw
        charA[i] = charADepth(i, go);
    }

    // while there are remaining states in the queue
    while(q.size()){
        // get next state
        unsigned int state = q.front();
        q.pop();

        for(unsigned int i = 0; i < max_chars_alphabet; ++i){
            // termination
            if(state == (max_states-1)){
                // calculate depth for each state and set2
                for(unsigned int j = 0; j < max_states; j++){
                    state_depth[j] = getStateDepth(j, go);

                    if(failure[j] != 0 && output[j] != 0){
                        set2[j] = j;
                    }
                }

                // calculate shift1, shift2 for each state
                for(unsigned int j = 0; j < max_states; j++){
                    shift1[j] = calcShift1(j, failure, state_depth);
                    shift2[j] = calcShift2(j, set2, state_depth);
                }

                return states;
            }

            // if goto is defined for state and char i
            else if(go[state][i] != -1){
                // get failure value
                int fail = failure[state];

                // go through trie to find final failure value
                while(go[fail][i] == -1){
                    fail = failure[fail];
                }
                fail = go[fail][i];
                failure[go[state][i]] = fail;

                // define output for word that form a part of different word
                // output can be more than one word in certain states
                output[go[state][i]] |= output[fail];

                //move onto next state
                q.push(go[state][i]);
            }
        }
    }
}

#endif // CWSEARCH_H
