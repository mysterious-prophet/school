#ifndef VECTOR
#define VECTOR
    #include <vector>
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

#ifndef TREE
#define TREE
    #include "../Abstract/Tree.h"
#endif

#ifndef DYNNODE
#define DYNNODE
    #include "../../headers/Dyn/DynNode.h"
#endif

#ifndef MAX_NUMBER_OF_NODES
#define MAX_NUMBER_OF_NODES 256 * 2 + 1
#endif

#ifndef INTERNAL_NODE_SIGN
#define INTERNAL_NODE_SIGN 0x100
#endif

#ifndef NYT_NODE_SIGN
#define NYT_NODE_SIGN 0x200
#endif

#ifndef NO_INF_SIGN
#define NO_INF_SIGN 0x300
#endif

#ifndef NOTHING
#define NOTHING -1
#endif
 
class DynTree final : public Tree
{
    public:

        DynTree();
        DynTree(const DynTree& dtr);
        DynTree(DynTree&& dtr);

        DynTree& operator = (const DynTree& dtr);
        DynTree& operator = (DynTree&& dtr);

        const DynNode& get_curr() const;
        unsigned int get_curr_pos() const;
        bool move_prev();
        bool move_to_byte(unsigned short b);
        virtual bool move_left();
        virtual bool move_right();
        virtual void move_to_root();
        virtual unsigned short get_curr_byte() const;
        virtual std::size_t get_curr_freq() const;

        virtual std::vector<char> decrypt(const std::vector<char>& bytes_to_decrypt);
        virtual std::vector<char> decrypt_bits(const std::pair<char, unsigned int>& bits);
        virtual ~DynTree();

    protected:

        void do_copy(const DynTree& dtr);
        void do_move(DynTree&& dtr);
        void update_byte_tree(unsigned short b);
        unsigned int slide_and_increment(unsigned int dnode);
        unsigned int swap_with_leader(unsigned int dnode);

        friend class DynTable;
        
        std::shared_ptr<DynNode[]> tree;
        std::shared_ptr<int[]> leafs;
        std::pair<char, unsigned int> first_seen_byte;
        unsigned int curr_node_prot;
        unsigned int curr_node_pub;
        unsigned int nyt_index;
};
