#ifndef STRING
#define STRING
    #include <string>
#endif

#ifndef VECTOR
#define VECTOR
    #include <vector>
#endif

class Tree
{
    public:

        const std::string& get_interacting_nf() const;
        virtual std::vector<char> decrypt(const std::vector<char>& bytes_to_decrypt) = 0;

        virtual std::vector<char> decrypt_bits(const std::pair<char,
                                                               unsigned int>& bits) = 0;

        virtual bool move_left() = 0;
        virtual bool move_right() = 0;
        virtual void move_to_root() = 0;
        virtual unsigned short get_curr_byte() const = 0;
        virtual std::size_t get_curr_freq() const = 0;

        virtual ~Tree();

    protected:

        Tree();
        Tree(const Tree& tr);
        Tree(Tree&& tr);
        Tree& operator = (const Tree& tr) = delete;
        Tree& operator = (Tree&& tr) = delete;
};
