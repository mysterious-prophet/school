#ifndef TREE
#define TREE
    #include "../Abstract/Tree.h" 
#endif

#ifndef STATNODE
#define STATNODE
    #include "StatNode.h"
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

#ifndef QUEUE
#define QUEUE
    #include <queue>
#endif

#ifndef FSTREAM
#define FSTREAM
    #include <fstream>
#endif

class StatTree final : public Tree
{
    public:
        
        enum Mode {Encrypt, Decrypt};

        // constructors

        // if you need to encrypt file
        StatTree(const std::string& Name_of_File, const StatTree::Mode& md);

        // if you need to encrypt vector of bytes
        explicit StatTree(const std::vector<char>& bytes);
        
        // if you need to decrypt information
        StatTree(const std::vector<char>& tree_in_vec, unsigned int Num_diff_bytes,
                 unsigned int Freq_length);

        StatTree(const StatTree& str);
        StatTree(StatTree&& str);

        // get properties
        const std::string& get_interacting_nf() const;
        const StatTree::Mode& get_mode() const;
        std::vector<char> get_tree_in_vec() const;
        const std::shared_ptr<const StatNode>& get_curr() const;
        unsigned int get_num_diff_bytes() const;
        unsigned int get_freq_length() const;

        // move in tree and view
        virtual bool move_left();
        virtual bool move_right();
        virtual void move_to_root();
        virtual unsigned short get_curr_byte() const;
        virtual std::size_t get_curr_freq() const;

        // state flags of object
        bool is_bad_state() const;
        bool is_success_file_open() const;
        bool is_bad_tree() const;

        // operators of assignment
        StatTree& operator = (const StatTree& str);
        StatTree& operator = (StatTree&& str);

        virtual std::vector<char> decrypt(const std::vector<char>& bytes_to_decrypt);

        virtual std::vector<char> decrypt_bits(const std::pair<char,
                                                               unsigned int>& bits);

        virtual ~StatTree();

    protected:

        void do_copy(const StatTree& str);
        void do_move(StatTree&& str);

        void copy_curr_node(const std::pair<std::size_t, unsigned int>& route,
                            std::shared_ptr<const StatNode>& curr_node);

        // read tree from file
        void read_tree_file(std::priority_queue<std::shared_ptr<StatNode>,
                                                std::vector<std::shared_ptr<StatNode>>,
                                                StatNode::ptr_compare>& StatNodes);
        // read tree from vector
        void read_tree_vec(const std::vector<char>& tree,
                           std::priority_queue<std::shared_ptr<StatNode>,
                                               std::vector<std::shared_ptr<StatNode>>,
                                               StatNode::ptr_compare>& StatNodes);

        // make tree from nodes with Hafman algorithm
        void make_tree(std::priority_queue<std::shared_ptr<StatNode>,
                                           std::vector<std::shared_ptr<StatNode>>,
                                           StatNode::ptr_compare>& StatNodes);

        // properties
        static const unsigned int sz_byte_fq_tab = 256;
        std::shared_ptr<std::size_t[]> Byte_Freq;
        std::shared_ptr<StatNode> root;
        unsigned int freq_length;
        unsigned int num_diff_bytes;
        std::shared_ptr<const StatNode> curr_node_prot;
        std::shared_ptr<const StatNode> curr_node_pub;
        std::pair<std::size_t, unsigned int> route_curr_prot;
        std::pair<std::size_t, unsigned int> route_curr_pub;
        std::string interacting_nf;
        StatTree::Mode mode;
        bool bad_state;
        bool success_file_open;
        bool bad_tree;
};
