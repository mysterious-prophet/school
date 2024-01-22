#ifndef HUFFSTAT_H
#define HUFFSTAT_H

#include <string>
#include <vector>

using namespace std;


class huffStat
{
public:
    huffStat(const string text);

private:
    struct MinHeapNode {

        // One of the input characters
        char data;

        // Frequency of the character
        unsigned freq;

        // Left and right child
        MinHeapNode *left, *right;

        MinHeapNode(char data, unsigned freq)

        {

            left = right = nullptr;
            this->data = data;
            this->freq = freq;
        }
    };

    struct compare {

        bool operator()(MinHeapNode* l, MinHeapNode* r)

        {
            return (l->freq > r->freq);
        }
    };

    struct freqAnalysis{
        vector<char> symbols;
        vector<int> freq;
        int size;
    };


    void printCodes(struct MinHeapNode* root, string str);
    void huffmanCodes(vector<char> data, vector<int> freq, int size);
    freqAnalysis getFreqAnalysis(const string text);

};

#endif // HUFFSTAT_H
