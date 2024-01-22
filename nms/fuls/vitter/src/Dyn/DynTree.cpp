#ifndef DYNTREE
#define DYNTREE
    #include "../../headers/Dyn/DynTree.h"
#endif
 
DynTree::DynTree() :
    Tree(), leafs(new int[256]), nyt_index(0),
    curr_node_pub(0), curr_node_prot(0), first_seen_byte(),
    tree(new DynNode [MAX_NUMBER_OF_NODES]) {
    
    // initialization
    for(int i = 0; i < 256; i++)
        leafs[i] = NOTHING;

    // set nyt node
    tree[0].reset_byte(static_cast<unsigned short>(NYT_NODE_SIGN));
    nyt_index = 0;
}

const DynNode& DynTree::get_curr() const {
    
    return tree[curr_node_pub];
}

unsigned int DynTree::get_curr_pos() const {

    return curr_node_pub;
}

bool DynTree::move_prev() {

    if(tree[curr_node_pub].get_prev() != NOTHING){

        curr_node_pub = tree[curr_node_pub].get_prev();
        return true;

    } else {

        return false;
    }
}

bool DynTree::move_to_byte(unsigned short b) {

    if((b < 256) && (leafs[b] != NOTHING)){
        curr_node_pub = leafs[b];
        return true;
    } else {
        curr_node_pub = nyt_index;
        return false;
    }
}

bool DynTree::move_left() {

    if(tree[curr_node_pub].get_left() != NOTHING){
        curr_node_pub = tree[curr_node_pub].get_left();
        return true;
    } else {
        return false;
    }
}

bool DynTree::move_right() {

    if(tree[curr_node_pub].get_right() != NOTHING){

        curr_node_pub = tree[curr_node_pub].get_right();
        return true;

    } else {

        return false;
    }
}

void DynTree::move_to_root() {

    curr_node_pub = 0;
}

unsigned short DynTree::get_curr_byte() const {

    return tree[curr_node_pub].get_byte();
}

std::size_t DynTree::get_curr_freq() const {

    return tree[curr_node_pub].get_freq();
}

std::vector<char> DynTree::decrypt(const std::vector<char>& bytes_to_decrypt) {

    // NOTE // // It is necessary firstly write decrypted byte
               // in deciphered vector and only then update tree
               // in order to obtain right decryption of information.
    
    // initialization of return vector with deciphered information
    std::vector<char> deciphered;

    for(unsigned int i = 0; i < bytes_to_decrypt.size(); i++){

        // cycle for passing the byte with encrypted information
        for(unsigned int j = 0; j < 8; j++){

            if(tree[curr_node_prot].is_leaf()){
                // if some leaf of the tree is reached
                
                unsigned short ush_byte = tree[curr_node_prot].get_byte();

                if(ush_byte == static_cast<unsigned short>(NYT_NODE_SIGN)){

                    // if leaf with nyt sign is reached
                    // it means that the next block of information that we will
                    // read should consist of 8 bits and should be decrypted
                    // like simple char byte
                    // Also it means that there is no information
                    // about next decrypted byte in tree yet
                    
                    // iterate in this block of information (byte)

                    // if the block of information does
                    // not consist of 8 bits yet
                    
                    // first  - describres the block of
                    //          infomation (byte) itself
                    // second - describes length of block
                    //          of information (byte)
                    unsigned char current_bit = bytes_to_decrypt[i] & (1 << (7 - j));

                    first_seen_byte.first |= 
                        ((current_bit >> (7 - j)) << (7 - first_seen_byte.second));

                    first_seen_byte.second++;

                    if(first_seen_byte.second == 8){

                        // if the block of information
                        // already contains 8 bits
                        
                        // write first seen byte in return vector
                        
                        deciphered.push_back(first_seen_byte.first);

                        unsigned char uch_f_byte = 
                                    static_cast<unsigned short>(first_seen_byte.first);

                        unsigned short ush_f_byte = static_cast<unsigned short>(
                                                                            uch_f_byte);
                        // update tree with new first seen byte
                        update_byte_tree(ush_f_byte);

                        // reset first seen byte
                        first_seen_byte.first = 0;
                        first_seen_byte.second = 0;

                        // reset protected current node
                        curr_node_prot = 0;
                    }

                } else {

                    // if any leaf with simple byte is reached
                    
                    // cast node's 'byte' with addtional service information
                    // from unsigned short to char (real byte)
                    char ch_byte = static_cast<char>(ush_byte);

                    // write reached and after casted byte in return vector
                    deciphered.push_back(ch_byte);

                    // update tree with already seen byte
                    update_byte_tree(ush_byte);

                    // reset protected current node
                    curr_node_prot = 0;

                    if(bytes_to_decrypt[i] & (1 << (7 - j))){

                        // protected current node in case next
                        // bit is 1 and then next node is right child
                        curr_node_prot = tree[curr_node_prot].get_right();

                    } else {

                        // protected current node in case next
                        // bit is 0 and then next node is left child
                        curr_node_prot = tree[curr_node_prot].get_left();
                    }
                }

            } else {

                if(bytes_to_decrypt[i] & (1 << (7 - j))){

                    // protected current node in case next
                    // bit is 1 and then next node is right child
                    curr_node_prot = tree[curr_node_prot].get_right();

                } else {

                    // protected current node in case next
                    // bit is 0 and then next node is left child
                    curr_node_prot = tree[curr_node_prot].get_left();
                }
            }
        }
    }

    return deciphered;
}

std::vector<char> DynTree::decrypt_bits(const std::pair<char, unsigned int>& bits) {

    // NOTE // // It is necessary firstly write decrypted byte
               // in deciphered vector and only then update tree
               // in order to obtain right decryption of information.

    // initialization of return vector with deciphered information
    std::vector<char> deciphered;

    // cycle for passing the byte with encrypted information
    for(unsigned int i = 0; i < bits.second; i++){

        if(tree[curr_node_prot].is_leaf()){

            // if some leaf of the tree is reached

            unsigned short ush_byte = tree[curr_node_prot].get_byte();

            if(ush_byte == static_cast<unsigned short>(NYT_NODE_SIGN)){

                // if leaf with nyt sign is reached
                // it means that the block of information that we will
                // read should consist of 8 bits and should be decrypted
                // like simple char byte
                // Also it means that there is no information
                // about next decrypted byte in tree yet

                // if the block of information does
                // not consist of 8 bits yet

                // first  - describres the block of
                //          infomation (byte) itself
                // second - describes length of block
                //          of information (byte)
                
                unsigned char current_bit = bits.first & (1 << (7 - i));

                first_seen_byte.first |= 
                    ((current_bit >> (7 - i)) << (7 - first_seen_byte.second));

                first_seen_byte.second++;

                if(first_seen_byte.second == 8){

                    // if the block of information
                    // already contains 8 bits
                    
                    // write first seen byte in return vector
                    deciphered.push_back(first_seen_byte.first);

                    unsigned char uch_byte = 
                                static_cast<unsigned short>(first_seen_byte.first);

                    unsigned short ush_byte = static_cast<unsigned short>(uch_byte);

                    // update tree with new first seen byte
                    update_byte_tree(ush_byte);

                    // reset first seen byte
                    first_seen_byte.first = 0;
                    first_seen_byte.second = 0;

                    // reset protected current node
                    curr_node_prot = 0;
                }

            } else {

                // if any leaf with simple byte is reached

                // cast node's 'byte' with possible addtional service
                // information from unsigned short to char (real byte)
                char ch_byte = static_cast<char>(ush_byte);

                // write reached and after casted byte in return vector
                deciphered.push_back(ch_byte);
                    
                // update tree with already seen byte
                update_byte_tree(ush_byte);
                    
                // reset protected current node
                curr_node_prot = 0;

                if(bits.first & (1 << (7 - i))){

                    // protected current node in case next
                    // bit is 1 and then next node is right child
                    curr_node_prot = tree[curr_node_prot].get_right();

                } else {

                    // protected current node in case next
                    // bit is 0 and then next node is left child
                    curr_node_prot = tree[curr_node_prot].get_left();
                }
            }

        } else {

            if(bits.first & (1 << (7 - i))){

                // protected current node in case next
                // bit is 1 and then next node is right child
                curr_node_prot = tree[curr_node_prot].get_right();

            } else {

                // protected current node in case next
                // bit is 0 and then next node is left child
                curr_node_prot = tree[curr_node_prot].get_left();
            }
        }
    }

    if(tree[curr_node_prot].is_leaf()){

        // if any leaf with simple byte is reached at the end of decryption
        
        unsigned short ush_byte = tree[curr_node_prot].get_byte();

        // cast node's 'byte' with possible addtional service
        // information from unsigned short to char (real byte)
        char ch_byte = static_cast<char>(ush_byte);

        // write reached and after casted byte in return vector
        deciphered.push_back(ch_byte);
            
        // update tree with already seen byte
        update_byte_tree(ush_byte);
            
        // reset protected current node
        curr_node_prot = 0;
    }

    return deciphered;
}

DynTree::DynTree(const DynTree& dtr) :
    Tree(dtr), leafs(new int [256]), nyt_index(dtr.nyt_index),
    first_seen_byte(dtr.first_seen_byte),
    curr_node_prot(dtr.curr_node_prot), curr_node_pub(dtr.curr_node_pub),
    tree(new DynNode [MAX_NUMBER_OF_NODES]) {
    
    do_copy(dtr);
}

DynTree::DynTree(DynTree&& dtr) :
    Tree(std::move(dtr)), leafs(std::move(dtr.leafs)), nyt_index(dtr.nyt_index),
    curr_node_prot(dtr.curr_node_prot),
    curr_node_pub(dtr.curr_node_pub), tree(std::move(dtr.tree)),
    first_seen_byte(std::move(dtr.first_seen_byte)) {

    dtr.nyt_index = 0;
    dtr.curr_node_prot = 0;
    dtr.curr_node_pub = 0;
}

DynTree& DynTree::operator = (const DynTree& dtr) {
    
    if(this == &dtr){

        return * this;

    } else {

        nyt_index = dtr.nyt_index;
        first_seen_byte = dtr.first_seen_byte;
        curr_node_prot = dtr.curr_node_prot;
        curr_node_pub= dtr.curr_node_pub;
        do_copy(dtr);
        return * this;
    }
}
    
DynTree& DynTree::operator = (DynTree&& dtr) {

    if(this == &dtr){

        return * this;

    } else {

        do_move(std::move(dtr));
        return * this;
    }
}

void DynTree::update_byte_tree(unsigned short b) {
    
    // initialization
    int leaf_to_increment = NOTHING;
    
    int p = leafs[static_cast<unsigned int>(b)];

    if(p == NOTHING){
        // in case b is new byte
        
        // reset DynNode of nyt_index + 2 in new NYT node
        tree[nyt_index + 2].reset_byte(static_cast<unsigned short>(NYT_NODE_SIGN));
        tree[nyt_index + 2].reset_prev(nyt_index);

        // reset old NYT node in internal node
        tree[nyt_index].reset_byte(static_cast<unsigned short>(INTERNAL_NODE_SIGN));
        tree[nyt_index].reset_left(nyt_index + 2);
        tree[nyt_index].reset_right(nyt_index + 1);

        // reset DynNode of nyt_index + 1 in new byte leaf node
        tree[nyt_index + 1].reset_byte(b);
        tree[nyt_index + 1].reset_prev(nyt_index);

        leafs[static_cast<unsigned int>(b)] = nyt_index + 1;
        
        // first node to function slide_and_increment
        p = nyt_index;

        // pointing index of new NYT node
        nyt_index += 2;

        // last node to fuction slide_and_increment
        leaf_to_increment = tree[p].get_right();

    } else {
        // in case b is an already existing byte in tree
        
        // swap with the leader of it's block
        p = swap_with_leader(p);

        // if p is the sibling of NYT node
        if(tree[tree[tree[p].get_prev()].get_left()].get_byte() == NYT_NODE_SIGN){
            leaf_to_increment = p;
            p = tree[p].get_prev();
        }
    }
    
    // slide and increment of required nodes
    while(p != NOTHING) p = slide_and_increment(p);

    // if there is special leaf which must be last updated
    if(leaf_to_increment != NOTHING){
        slide_and_increment(leaf_to_increment);
    }
}

void DynTree::do_copy(const DynTree& dtr) {

    // copying dtr's leafs in new copy-object
    for(int i = 0; i < 256; i++)
        leafs[i] = dtr.leafs[i];

    // copying dtr's tree with all nodes in new copy-object
    for(int i = 0; i < MAX_NUMBER_OF_NODES; i++){
        tree[i].reset_byte(dtr.tree[i].get_byte());
        tree[i].reset_freq(dtr.tree[i].get_freq());
        tree[i].reset_prev(dtr.tree[i].get_prev());
        tree[i].reset_left(dtr.tree[i].get_left());
        tree[i].reset_right(dtr.tree[i].get_right());
    }
}

void DynTree::do_move(DynTree&& dtr) {

    tree = std::move(dtr.tree);
    leafs = std::move(dtr.leafs);
    first_seen_byte = std::move(dtr.first_seen_byte);
}

unsigned int DynTree::slide_and_increment(unsigned int dnode) {

    // return value (to next slide_and_increment)
    int ret_p = tree[dnode].get_prev();

    int w = tree[dnode].get_freq();

    // create temp copy of sliding node 
    DynNode temp(tree[dnode]);
    temp.reset_left(tree[dnode].get_left());
    temp.reset_right(tree[dnode].get_right());
    temp.reset_prev(tree[dnode].get_prev());

    int i = dnode - 1;

    if (tree[dnode].is_leaf()) {
        // if dnode is leaf node
        
        // slide leaf higher than nodes with frequency == temp.get_freq()
        while ((i >= 0) && (tree[i].get_freq() == w)) {

            // remember prev dyn node
            int prev_dn = tree[i + 1].get_prev();

            // assign prev element in slide to i'th element
            tree[i + 1] = tree[i]; // set children and prev to NOTHING

            // reset children and prev of node 
            tree[i + 1].reset_left(tree[i].get_left());
            tree[i + 1].reset_right(tree[i].get_right());
            tree[i + 1].reset_prev(prev_dn);

            // if moving node has children
            if (!tree[i + 1].is_leaf()) {

                // reset children's prev to new pos of this node
                tree[tree[i + 1].get_right()].reset_prev(i + 1);
                tree[tree[i + 1].get_left()].reset_prev(i + 1);
            }

            // if moving node is leaf
            if (tree[i + 1].is_leaf()) {

                // change it's position in leafs
                leafs[tree[i + 1].get_byte()] = i + 1;
            }

            // now children of i refer only to i + 1 and don't refer to i
            // while i and i + 1 refer to same children

            // move to next node
            i--;
        }

        if ((i + 1) != dnode){

            // set dnode to selected index
            
            // remember prev of selected place
            int prev_dn = tree[i + 1].get_prev();
            
            tree[i + 1] = temp; // set children and prev to NOTHING
            // doesn't change children because temp is leaf (has no children)
            
            // reset prev of node
            tree[i + 1].reset_prev(prev_dn);

            // change return value (next node for slide_and_increment)
            // cause actually the sum of children's frequencies has
            // changed for new parrent of node in argument of function
            ret_p = tree[i + 1].get_prev();

            // reset index of leaf in leafs array
            leafs[tree[i + 1].get_byte()] = i + 1;
        }

    } else {

        // if dnode is internal node

        while ((i >= 0) && tree[i].is_leaf() &&
              (tree[i].get_freq() <= (w + 1))){

            // remember prev dyn node
            int prev_dn = tree[i + 1].get_prev();

            // assign prev element in slide i'th element
            tree[i + 1] = tree[i]; // set children and prev to NOTHING


            // reset children and prev of node
            tree[i + 1].reset_left(tree[i].get_left());
            tree[i + 1].reset_right(tree[i].get_right());
            tree[i + 1].reset_prev(prev_dn);

            // update information about position of leaf in leafs
            leafs[tree[i + 1].get_byte()] = i + 1;

            // move to next node
            i--;
        }
        
        if ((i + 1) != dnode){

            // set dnode to selected index
            
            // rememer pvev of selected place
            int prev_dn = tree[i + 1].get_prev();
            
            tree[i + 1] = temp; // set children and prev to NOTHING

            // chage children of temp so that they refer to i + 1
            tree[temp.get_left()].reset_prev(i + 1);
            tree[temp.get_right()].reset_prev(i + 1);

            // reset prev to remembered prev
            tree[i + 1].reset_prev(prev_dn);

            // change children of temp so that they are
            // (i + 1)'s left and right
            tree[i + 1].reset_left(temp.get_left());
            tree[i + 1].reset_right(temp.get_right());
            
            // doesn't change return value (next node for slide_and_increment)
            // cause actually the sum of children's frequencies has
            // changed for old parrent of node in argument of function
        }
    }

    // increment current node
    tree[i + 1].reset_freq(tree[i + 1].get_freq() + 1);

    return ret_p;
}

unsigned int DynTree::swap_with_leader(unsigned int dnode) {

    int i = dnode;

    while((i >= 1) && (tree[i - 1].is_leaf() == tree[dnode].is_leaf()) &&
          (tree[i - 1].get_freq() == tree[dnode].get_freq())){

        i--;
    }

    if(i != dnode){

        // swap positions in tree
        unsigned int temp_trpos = leafs[tree[i].get_byte()];
        leafs[tree[i].get_byte()] = leafs[tree[dnode].get_byte()];
        leafs[tree[dnode].get_byte()] = temp_trpos;

        // swap bytes
        unsigned short temp_byte = tree[i].get_byte();
        tree[i].reset_byte(tree[dnode].get_byte());
        tree[dnode].reset_byte(temp_byte);
    }

    return i;
}

DynTree::~DynTree() {}
