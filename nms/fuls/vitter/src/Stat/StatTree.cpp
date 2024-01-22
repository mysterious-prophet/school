#ifndef STATTREE
#define STATTREE
    #include "../../headers/Stat/StatTree.h"
#endif
 
StatTree::StatTree(const std::string& Name_of_File, const StatTree::Mode& md) :
    interacting_nf(Name_of_File), Tree(), root(), freq_length(0), route_curr_pub(),
    mode(md), curr_node_prot(nullptr), curr_node_pub(nullptr), route_curr_prot(),
    num_diff_bytes(0), Byte_Freq(new std::size_t[sz_byte_fq_tab]), bad_state(false),
    success_file_open(false), bad_tree(false) {

    // initialize priority queue in order to save nodes
    std::priority_queue<std::shared_ptr<StatNode>,
                        std::vector<std::shared_ptr<StatNode>>,
                        StatNode::ptr_compare> StatNodes;

    // if we are encrypting file
    if(mode == StatTree::Mode::Encrypt){ 

        // init freq table in zeros
        for(unsigned int i = 0; i < sz_byte_fq_tab; i++){
            Byte_Freq[i] = 0;
        }
        
        // init max freq of byte in zero
        std::size_t max_freq = 0;

        // collecting information about file
        
        // open file
        std::ifstream interact_file(interacting_nf, std::ios::binary);

        // check if file is open
        if(!interact_file.is_open()){

            // if not set bad state
            bad_state = true;

            // and return
            return;

        } else {

            // else set file is open
            success_file_open = true;
        }

        interact_file.seekg(0, std::ios::end);

        // set read block size
        std::size_t block_size = 100;

        // collect information about file
        std::size_t file_size = static_cast<std::size_t>(interact_file.tellg());

        // num of iterations needed in order to chek file
        std::size_t num_iters = file_size / block_size;

        // find size of the rest of file
        std::size_t rest_file = file_size % block_size;

        // if there is rest increase num of iters
        if(rest_file){

            num_iters++;
        }

        // move to begining of file
        interact_file.seekg(0, std::ios::beg);

        // init buffer
        std::vector<char> Read(block_size);

        // collect information about frequence of bytes in file
        for(unsigned int i = 0; i < num_iters; i++){

            // resize to size of rest file
            if((i == num_iters - 1) && rest_file){
                Read.resize(rest_file);
                block_size = rest_file;
            }

            // read block of information
            interact_file.read(&Read[0], Read.size());

            for(unsigned int j = 0; j < Read.size(); j++){

                // casts of byte
                unsigned char uch_byte = static_cast<unsigned char>(Read[j]);
                unsigned int uint_byte = static_cast<unsigned int>(uch_byte);

                // count num of different bytes
                if(!Byte_Freq[uint_byte]){

                    num_diff_bytes++;
                }

                // increment freq of current byte
                Byte_Freq[uint_byte]++;

                // find byte with max freq
                if(Byte_Freq[uint_byte] > max_freq){

                    max_freq = Byte_Freq[uint_byte];
                }
            }
        }

        // close file
        interact_file.close();

        // make nodes with bytes and frequences
        for(unsigned int i = 0; i < sz_byte_fq_tab; i++){

            if(Byte_Freq[i]){

                StatNodes.emplace(new StatNode(static_cast<unsigned short>(i),
                                               Byte_Freq[i]));
            }
        }

        // defining the length of max_freq in bytes
        // (in order to choose number of bytes that
        // is necessary for saving frequenses)
        
        unsigned char mask = 255;
        for(unsigned int i = 0; i < 8; i++){
            if((max_freq >> (8 * i)) & mask){
                freq_length = i + 1;
            }
        }

        // make tree from nodes with Hafman algorithm
        make_tree(StatNodes);

    }

    // if we are derypting file
    else {

        // read leafs from file in priority queue
        read_tree_file(StatNodes);

        // if tree is in bad state after reading
        // tree return from constructor
        if(bad_state) {

            return;
        }

        // make tree from nodes with Hafman algorithm
        make_tree(StatNodes);
    }

    // set current nodes to begin of the tree
    curr_node_prot = curr_node_pub = root;
}

StatTree::StatTree(const std::vector<char>& bytes) :
    Tree(), Byte_Freq(new std::size_t[sz_byte_fq_tab]), root(nullptr),
    route_curr_prot(), route_curr_pub(), freq_length(0), mode(StatTree::Mode::Encrypt),
    num_diff_bytes(0), curr_node_pub(nullptr), curr_node_prot(nullptr), bad_state(false),
    success_file_open(false), bad_tree(false) {

    // initialize priority queue in order to save nodes
    std::priority_queue<std::shared_ptr<StatNode>,
                        std::vector<std::shared_ptr<StatNode>>,
                        StatNode::ptr_compare> StatNodes;

    // init freq table in zeros
    for(unsigned int i = 0; i < sz_byte_fq_tab; i++){
        Byte_Freq[i] = 0;
    }

    std::size_t max_freq = 0;

    for(unsigned int i = 0; i < bytes.size(); i++){

        // casts of byte
        unsigned char uch_byte = static_cast<unsigned char>(bytes[i]);
        unsigned int uint_byte = static_cast<unsigned int>(uch_byte);

        // count num of different bytes
        if(!Byte_Freq[uint_byte]){

            num_diff_bytes++;
        }

        // increment freq of current byte
        Byte_Freq[uint_byte]++;

        // find byte with max freq
        if(Byte_Freq[uint_byte] > max_freq){

            max_freq = Byte_Freq[uint_byte];
        }
    }

    // make nodes with bytes and frequences
    for(unsigned int i = 0; i < sz_byte_fq_tab; i++){

        if(Byte_Freq[i]){

            StatNodes.emplace(new StatNode(static_cast<unsigned short>(i),
                                           Byte_Freq[i]));
        }
    }

    // defining the length of max_freq in bytes
    // (in order to choose number of bytes that
    // is necessary for saving frequenses)
    
    unsigned char mask = 255;
    for(unsigned int i = 0; i < 8; i++)
        if(max_freq & (mask << (8 * i)))
            freq_length = i + 1;

    // make tree from nodes with Haffman algorithm
    make_tree(StatNodes);
}

StatTree::StatTree(const std::vector<char>& tree_in_vec, unsigned int Num_diff_bytes,
                   unsigned int Freq_length) :

    Tree(), Byte_Freq(new std::size_t[sz_byte_fq_tab]), root(nullptr), route_curr_prot(),
    route_curr_pub(), curr_node_pub(nullptr), curr_node_prot(nullptr), bad_tree(false),
    freq_length(Freq_length), num_diff_bytes(Num_diff_bytes), bad_state(false),
    success_file_open(false), mode(StatTree::Mode::Decrypt) {

    // initialize priority queue in order to save nodes
    std::priority_queue<std::shared_ptr<StatNode>,
                        std::vector<std::shared_ptr<StatNode>>,
                        StatNode::ptr_compare> StatNodes;

    // read tree from vector with bytes
    read_tree_vec(tree_in_vec, StatNodes);

    // if tree is in bad state after reading
    // tree return from constructor
    if(bad_state) {

        return;
    }

    // make tree from nodes with Hafman algorithm
    make_tree(StatNodes);
}

bool StatTree::is_bad_state() const {

    return bad_state;
}

bool StatTree::is_success_file_open() const {

    return success_file_open;
}

bool StatTree::is_bad_tree() const {

    return bad_state;
}

const std::string& StatTree::get_interacting_nf() const {

    return interacting_nf;
}

const StatTree::Mode& StatTree::get_mode() const {

    return mode;
}

std::vector<char> StatTree::get_tree_in_vec() const {

    // if tree is in bad state return
    // empty vector
    if(bad_state) {

        return std::vector<char>(0);
    }

    // initialize size of block of inf which refers
    // to specific byte
    // one more byte for recording the byte itself
    unsigned int length_of_block = freq_length + 1;

    // init return vector with required size
    std::vector<char> ret(num_diff_bytes * length_of_block);
    unsigned char mask = 255;

    // write blocks with bytes and freqs in vector
    for(unsigned int i = 0, p = 0; i < 256; i++){
        
        // p iterates in buffer of chars
        // i iterates in bytes
        if(Byte_Freq[i]){

            ret[p] = static_cast<char>(i);
            p++;

            for(int j = freq_length - 1; j >= 0; j--){

                // j - number of byte in current freq
                
                ret[p] = static_cast<char>( (Byte_Freq[i] >> (j * 8)) & mask ); 
                p++;
            }
        }
    }

    return ret;
}

StatTree::StatTree(const StatTree& str) : // copy semantics
    Tree(str), root(nullptr), curr_node_prot(nullptr), bad_tree(str.bad_tree), 
    curr_node_pub(nullptr), freq_length(str.freq_length), bad_state(str.bad_state),
    route_curr_prot(str.route_curr_prot), route_curr_pub(str.route_curr_pub),
    success_file_open(str.success_file_open) {
    
    do_copy(str);
}

StatTree::StatTree(StatTree&& str) : // move semantics
    Tree(std::move(str)), root(std::move(str.root)),
    freq_length(str.freq_length), bad_state(str.bad_state),
    curr_node_prot(std::move(str.curr_node_prot)),
    curr_node_pub(std::move(str.curr_node_pub)),
    route_curr_prot(std::move(str.route_curr_prot)),
    route_curr_pub(std::move(str.route_curr_pub)),
    Byte_Freq(std::move(str.Byte_Freq)),
    success_file_open(str.success_file_open),
    bad_tree(str.bad_tree) {

    str.freq_length = 0;
    str.bad_tree = false;
    str.bad_state = false;
    str.success_file_open = false;
}

const std::shared_ptr<const StatNode>& StatTree::get_curr() const {

    return curr_node_pub;
}

unsigned int StatTree::get_num_diff_bytes() const {

    return num_diff_bytes;
}

unsigned int StatTree::get_freq_length() const {

    return freq_length;
}

bool StatTree::move_left() {

    if (bad_state) {

        return false;
    }

    if(curr_node_pub->get_left()){

        route_curr_pub.second++;
        curr_node_pub = std::move(curr_node_pub->get_left());
        return true;

    } else {

        return false;
    }
}

bool StatTree::move_right() {

    if (bad_state) {

        return false;
    }

    if(curr_node_pub->get_right()){

        route_curr_pub.first |= 1 << route_curr_pub.second;
        route_curr_pub.second++;
        curr_node_pub = std::move(curr_node_pub->get_right());
        return true;

    } else {

        return false;
    }
}

void StatTree::move_to_root() {

    route_curr_pub.first = route_curr_pub.second = 0;
    curr_node_pub = root;
}

unsigned short StatTree::get_curr_byte() const {

    if (bad_state) {

        return NO_INF_SIGN;
    }

    return curr_node_pub->get_byte();
}

std::size_t StatTree::get_curr_freq() const {
    
    if (bad_state) {

        return 0;
    }

    return curr_node_pub->get_freq();
}

std::vector<char> StatTree::decrypt(const std::vector<char>& bytes_to_decrypt) {

    // if bad state return empty vector
    if (bad_state) {
        
        return std::vector<char>(0);
    }
    
    // initialization of return vector with deciphered information
    std::vector<char> deciphered;

    for(unsigned int i = 0; (i < bytes_to_decrypt.size()); i++){

        // cycle for passing the byte with encrypted information
        for(unsigned int j = 0; j < 8; j++){

            // at begining of every iteration
            // we are not in leaf

            // allocating space for recordinng
            // information about protected route
            route_curr_prot.first <<= 1;

            // update length of route
            route_curr_prot.second++;

            if(bytes_to_decrypt[i] & (1 << (7 - j))){

                // updating current node and route
                // in case next bit is 1 and then
                // next node is right child
                curr_node_prot = std::move(curr_node_prot->get_right());
                route_curr_prot.first |= 1;

            } else {

                // updating route and current node
                // in case next bit is 0 and then
                // next node is left child
                curr_node_prot = std::move(curr_node_prot->get_left());
            }

            if(curr_node_prot->is_leaf()){

                // if some leaf of the tree is reached
                
                // cast node's 'byte' with addtional service information
                // from unsigned short to char (real byte)
                char byte = static_cast<char>(curr_node_prot->get_byte());

                // write byte of leaf in return vector
                deciphered.push_back(byte);

                // reset protected current node
                curr_node_prot = root;

                // reset proteted route
                // first  - describes the protected route itself
                // second - describes protected route's length
                route_curr_prot.first = 0;
                route_curr_prot.second = 0;
            }
        }
    }
    
    return deciphered;
}

std::vector<char> StatTree::decrypt_bits(const std::pair<char, unsigned int>& bits) {
    
    // if bad state return empty vector
    if (bad_state) {
        
        return std::vector<char>(0);
    }

    // initialization of return vector with deciphered information
    std::vector<char> deciphered;

    for(unsigned int i = 0; i < bits.second; i++){
        
        // at the begining of every iteration
        // we are not in leaf

        // allocating space for recordinng
        // information about protected route
        route_curr_prot.first <<= 1;

        // update length of route
        route_curr_prot.second++;

        if(bits.first & (1 << (7 - i))){

            // updating current node and route
            // in case next bit is 1 and then
            // next node is right child
            curr_node_prot = std::move(curr_node_prot->get_right());
            route_curr_prot.first |= 1;

        } else {

            // updating route and current node
            // in case next bit is 0 and then
            // next node is left child
            curr_node_prot = std::move(curr_node_prot->get_left());
        }

        if(curr_node_prot->is_leaf()){

            // if some leaf of the tree is reached
            
            // cast node's 'byte' with addtional service information
            // from unsigned short to char (real byte)
            char byte = static_cast<char>(curr_node_prot->get_byte());

            // write byte of leaf in return vector
            deciphered.push_back(byte);
            
            // reset protected current node
            curr_node_prot = root;

            // reset proteted route
            // first  - describes the protected route itself
            // second - describes protected route's length
            route_curr_prot.first = 0;
            route_curr_prot.second = 0;
        }
    }

    return deciphered;
}

StatTree::~StatTree() {}

void StatTree::do_copy(const StatTree& str) {
    
    // initialize priority queue in order to save copied nodes
    std::priority_queue<std::shared_ptr<StatNode>,
                        std::vector<std::shared_ptr<StatNode>>,
                        StatNode::ptr_compare> StatNodes;

    // iterate in original table with bytes
    // and freqs, make copy of it and make
    // copy of nodes
    for(unsigned int i = 0; i < sz_byte_fq_tab; i++){
        Byte_Freq[i] = str.Byte_Freq[i];

        // if there is such byte in tree
        if(Byte_Freq[i]){

            // make node with this byte and it's frequency
            StatNodes.emplace(new StatNode(static_cast<unsigned short>(i),
                                           Byte_Freq[i]));
        }
    }

    if (!bad_state) {

        // making full coding tree for new copy-object
        make_tree(StatNodes);
    }
    
    // copying protected current node for decoding
    copy_curr_node(str.route_curr_prot, curr_node_prot);
    route_curr_prot = str.route_curr_prot;

    // copying public current node for moving in tree
    copy_curr_node(str.route_curr_pub, curr_node_pub);
    route_curr_pub = str.route_curr_pub;

}

void StatTree::copy_curr_node(const std::pair<std::size_t, unsigned int>& route,
                              std::shared_ptr<const StatNode>& curr_node) {

    if(route.second){
        // in case route isn't empty
        
        // move curr node in copied tree in same direction with original 
        for(unsigned int i = route.second; i > 0; i--){
            if((1 << (i - 1)) & route.first){

                // if bit of route is ' 1 ' move right
                curr_node = std::move(curr_node->get_right());

            } else {

                // if bit of route is ' 0 ' move left
                curr_node = std::move(curr_node->get_left());
            }
        } 

    } else {
        // in case route is empty
        curr_node = root;
    }
}

void StatTree::read_tree_file(std::priority_queue<std::shared_ptr<StatNode>,
                                                std::vector<std::shared_ptr<StatNode>>,
                                                StatNode::ptr_compare>& StatNodes) {

    // open file with tree
    std::ifstream interact_file(interacting_nf, std::ios::binary);

    // check if file is open
    if(!interact_file.is_open()){

        // if not set bad state
        bad_state = true;

        // and return
        return;

    } else {

        // else set file is open
        success_file_open = true;
    }

    // buffer variable
    char temp = 0;
    
    //            SPECIAL BYTES IN ENCRYPTED FILE
    //          (TWO FIRST BYTES IN ENCRYPTED FILE)
    //               ___________________
    //              |___first__|_second_|
    //              |000|0000|0 00000000|
    //                |     \        \___________
    //                |      \                   |
    //  ______________V____  _V______________  __V________________
    //  describes number of  describes length  describes number of
    //  significant bits in  of max frequency  different  bytes in
    //  rest byte with enc-      in bytes              tree
    //  rypted information

    // read special bytes with information about tree
    interact_file >> temp;
    unsigned char first_spec_byte = static_cast<unsigned char>(temp);

    interact_file >> temp;
    unsigned char second_spec_byte = static_cast<unsigned char>(temp);

    unsigned char mask = 15; // 00001111
    freq_length = (first_spec_byte >> 1) & mask;

    if(first_spec_byte & 1){

        // there is 256 different if there is
        // 1 at last right bit of first spec byte 
        num_diff_bytes = 256;

    } else {

        // else cast second byte to uint
        // in order to get inf about num
        // of diff bytes
        num_diff_bytes = static_cast<unsigned int>(second_spec_byte);
    }

    // set length of block with information
    // about byte and it's frequency
    unsigned int length_of_block = freq_length + 1;

    // initialize buffer for reading tree from file
    std::vector<char> tree(num_diff_bytes * length_of_block);

    // read vector with tree from file
    interact_file.read(&tree[0], tree.size());

    // close file
    interact_file.close();

    // read tree from vector
    read_tree_vec(tree, StatNodes);
}

void StatTree::read_tree_vec(const std::vector<char>& tree,
                             std::priority_queue<std::shared_ptr<StatNode>,
                                                std::vector<std::shared_ptr<StatNode>>,
                                                StatNode::ptr_compare>& StatNodes) {


    // set length of block with information
    // about byte and it's frequency
    unsigned int length_of_block = freq_length + 1;

    // check if size of tree vec is ok
    if (tree.size() != (length_of_block * num_diff_bytes)){

        // if not - return and set flags
        bad_tree = true;
        bad_state = true;

        return;
    }

    for(unsigned int i = 0; i < num_diff_bytes; i++){

        // i iterates to number of diff bytes in tree
        // and in number of block of information
        
        // buffer variable for recording byte
        unsigned short ush_byte = 0;

        // buffer variable for recording freq of byte
        std::size_t freq = 0;

        for(unsigned int j = 0; j < length_of_block; j++){

            // now we are reading i-th block

            // j iterates in current block number i

            // buffer variable for recording
            // next byte in encrypted tree
            unsigned char uch_byte = static_cast<unsigned char>(
                                                tree[i * length_of_block + j]);

            if(j == 0){

                // if it's zeros byte of block
                // thent it contains coding byte (character)
                ush_byte = static_cast<unsigned short>(uch_byte); 

            } else {

                // else it contains information about frequency
                
                // cast unsigned char with inf about frreq to size_t
                std::size_t szt_byte = static_cast<std::size_t>(uch_byte);

                // write this byte in freq
                freq |= (szt_byte << (8 * (freq_length - j)));
            }
        }
        
        // at the end of cycle we have read i-th block
        // we also have information about byte and ir's frequency

        // write freq of byte in table
        Byte_Freq[ush_byte] = freq;
        
        // make node of this byte with information about freq
        StatNodes.emplace(new StatNode(ush_byte, freq));
    }
}

void StatTree::make_tree(std::priority_queue<std::shared_ptr<StatNode>,
                                             std::vector<std::shared_ptr<StatNode>>,
                                             StatNode::ptr_compare>& StatNodes) {

    // this function makes tree by taking
    // next two elements of queue with increasing
    // order, uniting them and emplacing back to queue
    // while there is not only root node in queue

    while(StatNodes.size() > 1){

        // pop uniting two children under one parrent
        std::shared_ptr<StatNode> left_child(StatNodes.top());
        StatNodes.pop();
        std::shared_ptr<StatNode> right_child(StatNodes.top());
        StatNodes.pop();
        
        // emplace new parrent node with left_child and right_child
        StatNodes.emplace(new StatNode(std::move(left_child), std::move(right_child),
                                       static_cast<unsigned short>(INTERNAL_NODE_SIGN),
                                       left_child->get_freq() + right_child->get_freq()
                                      ));
    }
    
    // set root of tree
    root = StatNodes.top();

    // remove root from queue
    StatNodes.pop();
}
