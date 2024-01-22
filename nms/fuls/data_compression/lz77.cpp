#include "lz77.h"

void LZ77::LZ77_ENC(string String_TOENC, ofstream &ENCODED_FILE){
    char chars = String_TOENC[0];
    char *singleCharCode = GET_CODE(chars), *matchCode;
    ENCODED_FILE.write(singleCharCode, 2);
    int SEARCHBUFFER_REVERSE = 0, LOOK_A_HEAD_F = 1, LOOK_A_HEAD_M = 1, SEARCHBUFFER_FORWORD;
    int JUMP_COUNT = 0, LENGTH_COUNT = 0, CURRENT_LENGTH_COUNTER = 0, CURRENT_JUMP_COUNTER = 0, JUMPLENGTH;
    while (LOOK_A_HEAD_F < String_TOENC.size())
    {
        JUMP_COUNT = 0;
        LENGTH_COUNT = 0;
        SEARCHBUFFER_REVERSE = LOOK_A_HEAD_F;
        CURRENT_JUMP_COUNTER = 0;
        while (SEARCHBUFFER_REVERSE > 0 && CURRENT_JUMP_COUNTER < SEARCHBUFFER_SIZE)
        {
            SEARCHBUFFER_REVERSE--;
            CURRENT_JUMP_COUNTER++;
            if (String_TOENC[SEARCHBUFFER_REVERSE] == String_TOENC[LOOK_A_HEAD_F])
            {
                CURRENT_LENGTH_COUNTER = 1;
                SEARCHBUFFER_FORWORD = SEARCHBUFFER_REVERSE + 1;
                LOOK_A_HEAD_M = LOOK_A_HEAD_F + 1;
                while (CURRENT_LENGTH_COUNTER < LOCK_A_HEAD_SIZE)
                {
                    if (String_TOENC[SEARCHBUFFER_FORWORD] != String_TOENC[LOOK_A_HEAD_M])
                    {
                        break;
                    }
                    CURRENT_LENGTH_COUNTER++;
                    SEARCHBUFFER_FORWORD++;
                    LOOK_A_HEAD_M++;
                }
                if (LENGTH_COUNT < CURRENT_LENGTH_COUNTER)
                {
                    LENGTH_COUNT = CURRENT_LENGTH_COUNTER;
                    JUMP_COUNT = CURRENT_JUMP_COUNTER;
                }
            }
        }
        if (LENGTH_COUNT < 2)
        {
            singleCharCode = GET_CODE(String_TOENC[LOOK_A_HEAD_F]);
            ENCODED_FILE.write(singleCharCode, 2);
            LOOK_A_HEAD_F++;
        }
        else
        {
            LOOK_A_HEAD_F += LENGTH_COUNT;
            matchCode = GET_CODE(JUMP_COUNT, LENGTH_COUNT, String_TOENC[LOOK_A_HEAD_F]);
            ENCODED_FILE.write(matchCode, 3);
            LOOK_A_HEAD_F++;
        }
    }
}

void LZ77::LZ77_DEC(string ENCODED_FILE, ofstream &FINAL_OUTPUT){
    char TEMP_CODE[2];
    char CURRENT_BYTE[1];
    int MASTER = 0, AUX, IN_FILE_PTR = 0;
    vector<char> OUT_STRING;
    pair<int, int> J_L;
    while (IN_FILE_PTR < ENCODED_FILE.size())
    {
        CURRENT_BYTE[0] = ENCODED_FILE[IN_FILE_PTR++] & 0xff;
        if (CURRENT_BYTE[0] == 0x00)
        {
            CURRENT_BYTE[0] = ENCODED_FILE[IN_FILE_PTR++];
            OUT_STRING.push_back(CURRENT_BYTE[0]);
        }
        else
        {
            TEMP_CODE[0] = CURRENT_BYTE[0];
            CURRENT_BYTE[0] = ENCODED_FILE[IN_FILE_PTR++];
            TEMP_CODE[1] = CURRENT_BYTE[0];
            J_L = GET_JUMP_LENGTH(TEMP_CODE);
            AUX = OUT_STRING.size() - J_L.first;
            for (int i = 0; i < J_L.second; i++)
            {
                OUT_STRING.push_back(OUT_STRING[AUX++]);
            }
            CURRENT_BYTE[0] = ENCODED_FILE[IN_FILE_PTR++];
            OUT_STRING.push_back(CURRENT_BYTE[0]);
        }
    }
    char a[1];
    for (auto c : OUT_STRING)
    {
        a[0] = c;
        FINAL_OUTPUT.write(a, 1);
    }
}

char *LZ77::GET_CODE(uint16_t JUMP, uint8_t LENGTH, char BYTE)
{
    char *ARR = new char[3];
    uint16_t CODE = 0x0000;
    JUMP = (JUMP << 4) & 0xffff;
    CODE = CODE | JUMP;
    CODE = CODE | LENGTH;
    ARR[0] = CODE & 0xff; // Lower byte first
    ARR[1] = ((CODE >> 8) & 0xff);
    ARR[2] = BYTE & 0xff;
    return ARR;
}

char *LZ77::GET_CODE(char BYTE)
{
    char *ARR = new char[2];
    ARR[0] = 0x00;
    ARR[1] = BYTE;
    return ARR;
}

pair<int, int> LZ77::GET_JUMP_LENGTH(char *CODE)
{
    uint8_t LENGTH = CODE[0] & 0x0f;
    uint16_t JUMP = CODE[1] & 0x00ff;
    JUMP = JUMP << 4;
    uint8_t TEMP = (CODE[0] >> 4) & 0x0f;
    JUMP |= TEMP;
    return make_pair(JUMP, LENGTH);
}


