#ifndef STATARCHIVER
#define STATARCHIVER
    #include "../../headers/Stat/StatArchiver.h"
#endif
 
StatArchiver::StatArchiver() : Archiver() {}

std::string StatArchiver::arch(const std::string& nf_to_arch) const {

    // open original file
    std::ifstream original(nf_to_arch, std::ios::binary);

    // check is it open
    if (!original.is_open()) {

        // if not throw exception
        throw Archiver::cant_open_file_error(nf_to_arch);
    }

    // get necessary information about original file 
    
    // get size of file
    original.seekg(0, std::ios::end);
    std::size_t file_size = static_cast<std::size_t>(original.tellg());
    original.seekg(0, std::ios::beg);

    // set read block size
    std::size_t block_size = 100;

    // calculate number of iterations
    std::size_t num_iters = file_size / block_size;

    // calculate the rest that doesn't
    // fill block_size completely
    std::size_t sz_rest = file_size % block_size;

    if(sz_rest){
        // if there is rest of file that
        // doesn't fill block size completely
        
        num_iters++;
    }

    // initialize the coding
    // tree for a specific file
    StatTree tree(nf_to_arch, StatTree::Mode::Encrypt);

    // initialize coding table using
    // information from coding tree
    StatTable table(tree);

    // defining name of file with archiving information
    std::string res_nf = nf_to_arch + ".sarch";
    
    // check if file with name res_nf already exist
    std::ifstream arch_in(res_nf, std::ios::binary);

    if (arch_in.is_open()) {

        // if exist close file and throw exception
        arch_in.close();
        throw Archiver::write_in_exist_file_error(res_nf);
    }

    // open new archiving file
    std::ofstream archived(res_nf, std::ios::binary | std::ios::app);

    // initialization of special bytes
    char first_spec_byte = 0;
    char second_spec_byte = 0;
    
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
    // write information about length
    // of each frequency in bytes
    
    first_spec_byte |= tree.get_freq_length() << 1;

    // write information about number
    // of different butes used in tree
    if(tree.get_num_diff_bytes() == 256){

        // if there are all bytes used in the tree
        first_spec_byte |= 1;

    } else {

        // if not all bytes are used
        second_spec_byte |= tree.get_num_diff_bytes();
    }

    // output special bytes in archived file
    archived << first_spec_byte << second_spec_byte;

    // write tree in archived file
    std::vector<char> vec_tree = tree.get_tree_in_vec();
    archived.write(&vec_tree[0], vec_tree.size());

    // create read buffer
    std::vector<char> Read(block_size);

    // the process of archiving
    for(unsigned int i = 0; i < num_iters; i++){
        if((i == num_iters - 1) && sz_rest){
            // if it is the last iteration and there is the
            // rest that doesn't fill the block size completely
            
            // resize read buffer
            Read.resize(sz_rest);

            // reset block size to size of rest
            block_size = sz_rest;
        }

        // read block of information from original file
        original.read(&Read[0], Read.size());

        // encrypt this block
        std::vector<char> Encrypted(table.encrypt(Read));

        // write encrypted information in archived file
        archived.write(&Encrypted[0], Encrypted.size());
    }

    // close both original and archived files
    original.close();
    archived.close();

    // get rest of encryption
    // rest.first  - describes the rest bits itself
    // rest.second - describes the number of 
    //               significant bits

    std::pair<char, unsigned int> rest = table.get_rest_of_encrypt();

    if(rest.second){
        // if there is a rest of encryption

        // open archived file again with another flags
        archived.open(res_nf, std::ios::binary | std::ios::in
                | std::ios::out | std::ios::ate);

        // move the begin of file position
        archived.seekp(0, std::ios::beg);

        // process of renewing first spesial byte with
        // new information about length of rest encription
        // byte and writing the rest encription byte

        // initialize the mask to choose correct bits
        // in rest.second (number of rest bits can't be
        // more than 7)
        unsigned char mask = 7;

        // choose correct bits and move
        // it in necessary position
        first_spec_byte |= (rest.second & mask) << 5;

        // rewrite updated first_spec_byte
        archived.seekp(0, std::ios::beg);
        archived << first_spec_byte;

        // write the rest encription byte
        archived.seekp(0, std::ios::end);
        archived << rest.first;

        // close archived file
        archived.close();
    }

    return res_nf;
}

std::string StatArchiver::unarch(const std::string& nf_to_unarch, const std::string& Res_nf) const {

    // open file with archived information
    std::ifstream archived(nf_to_unarch, std::ios::binary);

    // check is it open
    if (!archived.is_open()) {

        // if not throw exception
        throw Archiver::cant_open_file_error(nf_to_unarch);
    }

    // find begining of substr with archived file extention
    std::size_t point = nf_to_unarch.rfind(".sarch");

    // if there is no such substr
    if (point == std::string::npos) {
        
        // throw exception
        throw Archiver::file_is_not_archive(nf_to_unarch);
    }
    
    // initialize the coding
    // tree for a specific file
    // there we have already read tree
    StatTree tree(nf_to_unarch, StatTree::Mode::Decrypt);

    std::string res_nf = "";

    if (Res_nf.size() != 0) {

        res_nf = Res_nf;

    } else {

        // define unarchived file name as
        // substr without archive extention
        res_nf =  nf_to_unarch.substr(0, point);
    }
    
    // initialize temp for reading first_spec_byte
    char temp = 0;
    archived >> temp;

    // initialize first_spec_byte 
    unsigned char first_spec_byte = static_cast<unsigned char>(temp);

    // initialize mask in order to take correct
    // information about length of last encrypted byte
    unsigned char mask = 7;
    unsigned int len_rest_encr = static_cast<unsigned int>(
                                                    (first_spec_byte >> 5) & mask);

    // get number of different bytes in tree
    unsigned int num_diff_bytes = tree.get_num_diff_bytes();

    // get length of each frequency in bytes in tree
    unsigned int freq_length = tree.get_freq_length();

    // initialize the start position of decription
    std::size_t start_decr = 2 + (freq_length + 1) * num_diff_bytes;

    // get necessary information about archived file 

    // get size of file
    archived.seekg(0, std::ios::end);
    std::size_t file_size = archived.tellg();
    archived.seekg(start_decr, std::ios::beg);

    // initialize the read block size
    std::size_t block_size = 100;

    // calculate size of part of information that
    // need to be decrypted (encrypted size)
    std::size_t sz_encrypted = file_size - start_decr; 

    // calculate number of iterations
    std::size_t num_iters = sz_encrypted / block_size;

    // calculate the rest that doesn't
    // fill block_size completely
    std::size_t sz_rest = sz_encrypted % block_size;

    // create read buffer
    std::vector<char> Read(block_size);

    // check if file with name res_nf already exist
    std::ifstream unarch_in(res_nf, std::ios::binary);

    if (unarch_in.is_open()) {

        // if exist close file and throw exception
        unarch_in.close();
        throw Archiver::write_in_exist_file_error(res_nf);
    }

    // open new file with unarchived information
    std::ofstream unarchived(res_nf, std::ios::binary | std::ios::app);

    if(len_rest_encr){
        // if there is a rest of encrypting
        // with less than 8 significant bits
        // do special case of decrypting

        if(!sz_rest){
            // if there is no rest that doesn't
            // fill block size completely
            // we need to have rest in order
            // to work with last byte correctly
            
            // reduce number of iterations with
            // simple decryption and make one more
            // special decription instead
            num_iters--;

            // change size of rest to size of read block
            sz_rest = block_size;
        }

        // simple decryption
        for(unsigned int i = 0; i < num_iters; i++){

            // read block of information from archived file
            archived.read(&Read[0], Read.size());

            // decrypt this block
            std::vector<char> Decrypted(tree.decrypt(Read));

            // write decrypted information in unarchived file
            unarchived.write(&Decrypted[0], Decrypted.size());
        }

        // special case of decryption
        if(sz_rest > 1){
            // if rest block doesn't consist
            // of only one rest byte
            
            // resize read buffer to sz_rest - 1
            // because the last byte will be
            // processed separately
            Read.resize(sz_rest - 1);

            // read block of information from archived file
            archived.read(&Read[0], Read.size());

            // decrypt this block
            std::vector<char> Decrypted(tree.decrypt(Read));

            // write decrypted information in unarchived file
            unarchived.write(&Decrypted[0], Decrypted.size());
        }
        
        // decription of the last byte
        
        // read last byte from archived file
        char byte_last_encr = 0;
        archived >> byte_last_encr;

        // initialization of last encrypted bits
        std::pair<char, unsigned int> last_encr(byte_last_encr, len_rest_encr);

        // decrypt last bits from archived file
        std::vector<char> Decrypted(tree.decrypt_bits(last_encr));

        // write decrypted last bits in unarchived file
        unarchived.write(&Decrypted[0], Decrypted.size());

    } else {
        // if there is no rest of encryption

        if(sz_rest){
            // if there is rest that doesn't
            // fill block size completely
            
            num_iters++;
        }

        for(unsigned int i = 0; i < num_iters; i++){
            if((i == num_iters - 1) && sz_rest){
                // if it is the last iteration and there is the
                // rest that doesn't fill the block size completely

                // resize read buffer
                Read.resize(sz_rest);

                // reset block size to size of rest
                block_size = sz_rest;
            }

            // read block of information from archived file
            archived.read(&Read[0], Read.size());

            // decrypt this block
            std::vector<char> Decrypted(tree.decrypt(Read));

            // write decrypted information in unarchived file
            unarchived.write(&Decrypted[0], Decrypted.size());
        }
    }

    // close both archived and unarchived files
    archived.close();
    unarchived.close();

    return res_nf;
}

StatArchiver::~StatArchiver() {}
