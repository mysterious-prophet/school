#ifndef DYNTABLE
#define DYNTABLE
    #include "../../headers/Dyn/DynTable.h"
#endif
 
DynTable::DynTable(DynTree& dtr) : Table(), dyn_tree(&dtr), ret_Code(new Code) {}

std::vector<char> DynTable::encrypt(const std::vector<char>& bytes_to_encrypt) {

    // initialization of return vector with encrypted information
    std::vector<char> encrypted;
    
    for(unsigned int i = 0; i < bytes_to_encrypt.size(); i++){
        
        // cast current byte in bytes_to_encrypt to unsigned char
        // in order to avoid errors with casting farther 
        unsigned char casted_to_uch = static_cast<unsigned char>(bytes_to_encrypt[i]);

        // cast of current byte to unsigned int in order to use
        // it for finding needed code for encrypting
        unsigned int required_byte = static_cast<unsigned int>(casted_to_uch);

        // find needed code of required byte
        const Code found_byte = operator [] (required_byte); 

        char byte = static_cast<char>(found_byte.get_byte());

        // write code in return vector wirh encrypted informarion
        write_code(found_byte, encrypted);

        // cast of current byte to unsignde short
        // in order to use it for updating tree
        unsigned short casted_to_ush = static_cast<unsigned short>(casted_to_uch);

        if(found_byte.get_byte() == static_cast<unsigned short>(NYT_NODE_SIGN)){
            // in case there is no current byte in the
            // tree and found_byte is nyt node sign
            // in this case we should write current
            // byte in encrypted vector after nyt sign
            
            // cast of current byte to std::size_t in order
            // to use it for writing in Code object
            std::size_t casted_to_size_t = static_cast<std::size_t>(casted_to_uch);
            
            // connstruct a new Code object in order
            // to write in order to write current byte
            // with natural coding in encoding vector
            const Code byte(casted_to_ush, casted_to_size_t, 8);

            char ch_byte = static_cast<char>(byte.get_byte());

            write_code(byte, encrypted);
        }
        // updating tree with current byte
        dyn_tree->update_byte_tree(casted_to_ush);

    }

    return encrypted;
} 

DynTable::DynTable(const DynTable& dtb) :
    dyn_tree(dtb.dyn_tree), ret_Code(new Code(* dtb.ret_Code)) {}

DynTable::DynTable(DynTable&& dtb) :
    dyn_tree(dtb.dyn_tree), ret_Code(std::move(dtb.ret_Code)) {

    dtb.dyn_tree = nullptr;
}

DynTable& DynTable::operator = (const DynTable& dtb) {

    if(this == &dtb){

        return * this;

    } else {

        dyn_tree = dtb.dyn_tree;
        ret_Code.reset(new Code(* dtb.ret_Code));
        return * this;
    }
}

DynTable& DynTable::operator = (DynTable&& dtb) {
    
    if(this == &dtb){

        return * this;

    } else {
        
        dyn_tree = dtb.dyn_tree;
        dtb.dyn_tree = nullptr;
        ret_Code = std::move(dtb.ret_Code);
        return * this;
    }
}

const Code& DynTable::operator [] (unsigned int i) const {

    if(i > 255){

        throw std::out_of_range("index out of range DynTable");
    }

    // init return byte in casted argument
    unsigned short ret_byte = static_cast<unsigned short>(i);

    // get position of byte in tree
    int curr_pos = dyn_tree->leafs[i];

    // if there is no such byte in tree yet
    if(curr_pos == NOTHING){

        curr_pos = dyn_tree->nyt_index;
        ret_byte = NYT_NODE_SIGN;
    }

    // get position of previous node of
    // this byte's node in tree
    int prev_node = dyn_tree->tree[curr_pos].get_prev();

    std::size_t code = 0;
    unsigned int length = 0;

    // generate code for byte i
    while(prev_node != -1){ //dyn_tree->move_prev()){

        // if curr node is the right child
        if(dyn_tree->tree[prev_node].get_right() == curr_pos){
            code |= (1 << length);
        }
        // if it is left child - just nothing to do
        length++;
        curr_pos = prev_node;
        prev_node = dyn_tree->tree[curr_pos].get_prev();
    }

    ret_Code->reset_byte(static_cast<unsigned short>(ret_byte));
    ret_Code->reset_code(code);
    ret_Code->reset_length(length);

    return * ret_Code;
}

DynTable::~DynTable() {}
