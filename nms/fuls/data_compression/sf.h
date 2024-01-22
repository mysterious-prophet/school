#ifndef SF_H
#define SF_H
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

class sf
{
public:
    sf();

    const string encode(const string text);
    const string decode(const string text);

private:
    struct node {

        // for storing symbol
        string sym;
        string code;

        // for storing probability or frequency
        float pro;
        int arr[39];
        int top;
    } p[39];

    int num_symbols;

    void sortByProbability(int n, node p[]);
    void calcCodes(int l, int h, node p[]);
    string getCode(char ch);
    void freqAnalysis(vector<float>& x, const string& text, float &total, int num_symbols);
    int getNumberSymbols(string& text);
};

#endif // SF_H
