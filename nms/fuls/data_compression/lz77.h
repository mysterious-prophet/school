#ifndef LZ77_H
#define LZ77_H

/*#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "windows.h"

using namespace std;


class LZ77
{
public:
    LZ77();
    string driver(string input, int option);
};*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;
#define SEARCHBUFFER_SIZE 4095
#define LOCK_A_HEAD_SIZE 15
class LZ77
{

private:
    static char *GET_CODE(uint16_t JUMP, uint8_t LENGTH, char BYTE);
    static char *GET_CODE(char BYTE);
    static pair<int, int> GET_JUMP_LENGTH(char *CODE);

public:
    static void LZ77_ENC(string String_TOENC, ofstream &ENCODED_FILE);
    static void LZ77_DEC(string ENCODED_FILE, ofstream &FINAL_OUTPUT);
};


#endif // LZ77_H
