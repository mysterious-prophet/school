#ifndef DYNARCHIVER
#define DYNARCHIVER
    #include "../../headers/Dyn/DynArchiver.h" 
#endif

DynArchiver::DynArchiver() : Archiver() {}

std::string DynArchiver::arch(const std::string& nf_to_arch) const {

    // open original file
    std::ifstream original(nf_to_arch, std::ios::binary);

    // check is it open
    if (!original.is_open()) {

        // if not throw exception
        throw Archiver::cant_open_file_error(nf_to_arch);
    }

    // get necessary information about file
    
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
    std::size_t rest_file = file_size % block_size;

    if(rest_file){
        // if there is rest of file that
        // doesn't fill block size completely
        
        num_iters++;
    }

    // initialize coding tree
    DynTree tree;

    // initialize coding table for encrypting
    // with help of information from tree
    DynTable table(tree);

    // defining name of archived file
    std::string res_nf = nf_to_arch + ".darch";

    // check if file with name res_nf already exist
    std::ifstream arch_in(res_nf, std::ios::binary);

    if (arch_in.is_open()) {

        // if exist close file and throw exception
        arch_in.close();
        throw Archiver::write_in_exist_file_error(res_nf);
    }

    // open new archived file
    std::ofstream archived(res_nf, std::ios::binary | std::ios::app);

    // output the byte with information about length
    // of rest byte (in bits)
    // now it has zero value, it will change farther
    char length_of_last = 0;
    archived << length_of_last;

    // create read buffer
    std::vector<char> Read(block_size);

    // the process of archiving
    for(unsigned int i = 0; i < num_iters; i++){
        if((i == num_iters - 1) && rest_file){
            // if it is the last iteration and there is the
            // rest that doesn't fill the block size completely
            
            // resize read buffer
            Read.resize(rest_file);

            // reset block size to size of rest
            block_size = rest_file;
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
    std::pair<char, unsigned int> rest = table.get_rest_of_encrypt();

    if(rest.second){
        // if there is a rest of encryption

        // open archived file again with another flags
        archived.open(res_nf, std::ios::binary | std::ios::in
                | std::ios::out | std::ios::ate);

        // move to the begining of file
        archived.seekp(0, std::ios::beg);

        // renew the byte wirh information about
        // rest of encryption byte length (in bits)
        archived << static_cast<char>(rest.second);

        // move to the end of file
        archived.seekp(0, std::ios::end);

        // write the rest of encryption byte
        archived << rest.first;

        // close achived file
        archived.close();
    }

    return res_nf;
}

std::string DynArchiver::unarch(const std::string& nf_to_unarch, const std::string& Res_nf) const {

    // open file with archived information
    std::ifstream archived(nf_to_unarch, std::ios::binary);

    // check is it open
    if (!archived.is_open()) {

        // if not throw exception
        throw Archiver::cant_open_file_error(nf_to_unarch);
    }

    // find begining of substr with archived file extention
    std::size_t point = nf_to_unarch.rfind(".darch");

    // if there is no such substr
    if (point == std::string::npos) {
        
        // throw exception
        throw Archiver::file_is_not_archive(nf_to_unarch);
    }

    // initializing coding tree
    DynTree tree;

    std::string res_nf = "";

    if (Res_nf.size() != 0) {
        
        res_nf = Res_nf;

    } else {

        // define unarchived file name as
        // substr without archive extention
        res_nf =  nf_to_unarch.substr(0, point);
    }

    // get length of encryption rest
    char len_rest_encr = 0; 
    archived >> len_rest_encr;

    // cast it to unsigned int
    unsigned char uch_len_rest_encr = static_cast<unsigned char>(len_rest_encr);
    unsigned int ui_len_rest_encr = static_cast<unsigned int>(uch_len_rest_encr);

    // it's impossible for archive have len of last more that 7
    if (ui_len_rest_encr > 7) {
        
        // in this case throw exception
        // it's not archive
        throw Archiver::file_is_not_archive(nf_to_unarch);
    }

    // initialize start of decryption position
    // in 1 becouse fist byte is already read
    // and encrypted information is placed
    // after it
    std::size_t start_decr = 1;

    // get necessary information about file

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

        if(!sz_rest){
            // if there is no rest that doesn't
            // fill block size completely
            
            // reduce number of iterations with
            // simple decryption make one more
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

        // call function to decrypt last byte even if
        // there is no such byte in order to write
        // last seen but not written byte

        // initialization of last encrypted bits
        std::pair<char, unsigned int> last_encr(0, 0);

        // decrypt last bits from archived file
        std::vector<char> Decrypted(tree.decrypt_bits(last_encr));

        // write decrypted last bits in unarchived file
        unarchived.write(&Decrypted[0], Decrypted.size());
    }

    // close both archived and unarchived files
    archived.close();
    unarchived.close();

    return res_nf;
}

DynArchiver::~DynArchiver() {}
