#ifndef RLE_H
#define RLE_H

#include<string>

using namespace std;

class rle
{
public:
    rle();

    const string encode(string text);
    const string decode(string text);

private:

};

#endif // RLE_H
