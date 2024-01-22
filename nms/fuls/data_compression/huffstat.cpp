// C++ program for Huffman Coding with STL
#include <bits/stdc++.h>
#include "huffstat.h"

using namespace std;

huffStat::huffStat(const string text)
{
    freqAnalysis freqAn = getFreqAnalysis(text);
    huffmanCodes(freqAn.symbols, freqAn.freq, freqAn.size);
}

huffStat::freqAnalysis huffStat::getFreqAnalysis(const string text){
    freqAnalysis freqAn;
    vector<int> freqTemp(26, 0);
    vector<char> symbolsTemp(26, ' ');
    freqAn.freq = freqTemp;
    freqAn.symbols = symbolsTemp;


    for(unsigned int i = 0; i < text.length(); i++){
        freqAn.freq[int(text[i])-97]++;
    }


    int k = 0;
    for(unsigned int i = 0; i < freqAn.freq.size(); i++){
        if(freqAn.freq[i] != 0){
            freqAn.symbols[k] = char(i+97);
            k++;
        }
    }

    for(unsigned int i = 0; i < freqAn.freq.size(); i++){
        if(freqAn.freq[i] == 0){
            for(unsigned int j = i; j < freqAn.freq.size(); j++){
                if(freqAn.freq[j] != 0){
                    freqAn.freq[i] = freqAn.freq[j];
                    freqAn.freq[j] = 0;
                    break;
                }
            }
        }
    }

    remove(freqAn.freq.begin(), freqAn.freq.end(), 0);
    remove(freqAn.symbols.begin(), freqAn.symbols.end(), ' ');

    freqAn.size = k;
    return freqAn;
}


void huffStat::printCodes(struct MinHeapNode* root, string str){
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}


void huffStat::huffmanCodes(vector<char> data, vector<int> freq, int size){
    struct MinHeapNode *left, *right, *top;

    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1) {

        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}
