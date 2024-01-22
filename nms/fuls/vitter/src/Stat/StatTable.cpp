#ifndef STATTABLE
#define STATTABLE
    #include "../../headers/Stat/StatTable.h"
#endif
 
StatTable::StatTable(StatTree& str) : Table(), table(new Code [256]), bad_state(false) {

    // if tree is in bad state
    if (str.is_bad_state()) {

        // set bad state flag of table in true too 
        bad_state = true;

        // and return from constructor
        return;
    }

    // reset curr_node_pub to root
    str.move_to_root();

    // creating table with recursive traversal of the tree
    // get curr_node_pub
    rec_make_table(str.get_curr(), 0, 0);
}

std::vector<char> StatTable::encrypt(const std::vector<char>& bytes_to_encrypt) {

    // if table in bad state
    if (bad_state) {
        
        // return empty vector
        return std::vector<char>(0);
    }
    
    // initialization of return vector with encrypted information
    std::vector<char> encrypted;
    
    for(unsigned int i = 0; (i < bytes_to_encrypt.size()); i++){
        
        // cast current byte in bytes_to_encrypt to unsigned char
        // from char in order to avoid errors with casting farther 
        unsigned char casted_to_uch = static_cast<unsigned char>(bytes_to_encrypt[i]);

        // second cast of current byte in order to use
        // it for finding needed code for encrypting
        unsigned int required_byte = static_cast<unsigned int>(casted_to_uch);

        // find needed code of required byte
        Code found_byte = table[required_byte];
        
        // write code in return vector wirh encrypted informarion
        write_code(found_byte, encrypted);
    }

    return encrypted;
}

StatTable::StatTable(const StatTable& stb) :
    Table(stb), table(new Code [256]), bad_state(stb.bad_state) {
    
    for(int i = 0; i < 256; i++)
        table[i] = stb.table[i];
}

StatTable::StatTable(StatTable&& stb) :
    Table(std::move(stb)), table(std::move(stb.table)), bad_state(stb.bad_state) {}

StatTable& StatTable::operator = (const StatTable& stb) {
    
    if(this == &stb){

        return * this;

    } else {

        bad_state = stb.bad_state;

        for(int i = 0; i < 256; i++)
            table[i] = stb.table[i];

        return * this;
    }
}

StatTable& StatTable::operator = (StatTable&& stb) {

    if(this == &stb){

        return * this;

    } else {

        bad_state = stb.bad_state;

        table = std::move(stb.table);
        return * this;
    }
}

const Code& StatTable::operator [] (unsigned int i) const {

    if(i > 255){

        throw std::out_of_range("index out of range StatTable");
    }
    
    return table[i];
}

void StatTable::rec_make_table(const std::shared_ptr<const StatNode>& stn,
                               std::size_t code, unsigned int length) {

    if(stn->is_leaf()){
        // adding information about leaf in StatTable
        unsigned int current_byte = static_cast<unsigned int>(stn->get_byte());
        table[current_byte].reset_byte(stn->get_byte());
        table[current_byte].reset_code(code);
        table[current_byte].reset_length(length);
    } else {
        rec_make_table(stn->get_left(), code << 1, length + 1);
        rec_make_table(stn->get_right(), (code << 1) | 1, length + 1);
    }
}

StatTable::~StatTable() {}
