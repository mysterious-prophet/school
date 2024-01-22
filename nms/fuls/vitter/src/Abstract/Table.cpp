#include "../../headers/Abstract/Table.h" 
#ifndef IOSTREAM
#define IOSTREAM
    #include <iostream>
#endif

Table::Table() : outp_byte() {}

Table::Table(const Table& tb) : outp_byte(tb.outp_byte) {}

Table::Table(Table&& tb) : outp_byte(std::move(tb.outp_byte)) {}

std::pair<char, unsigned int> Table::get_rest_of_encrypt() {

    std::pair<char, unsigned int> ret = outp_byte;
    return ret;
}

void Table::write_code(const Code& cd, std::vector<char>& encrypted) {
    
    // cycle for pasing the code of found_byte
    // and writing it in the outp_byte
    const std::size_t& code = cd.get_code();
    unsigned int length = cd.get_length();

    for(int p = length - 1; p >= 0; p--){ 
        // first  - describes the found code
        // second - describes the length of found code
            
        // writing (p + 1)'s bit of found_byte in outp_byte
        outp_byte.first |= ((((1 << p) & code) >> p) << (7 - outp_byte.second));
        
        // increment length of outp_byte
        outp_byte.second++;

        if(outp_byte.second == 8){
            // if the length of outp_byte == 8
            // write outp_byte in return vector

            encrypted.push_back(outp_byte.first);

            // reset outp_byte's code
            outp_byte.first = 0;

            //reset outp_byte's length
            outp_byte.second = 0;
        }
    }
}

Table::~Table() {}
