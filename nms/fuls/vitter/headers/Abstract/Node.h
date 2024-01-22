#ifndef STRING
#define STRING
    #include <string>
#endif

#ifndef NO_INF_SIGN
    #define NO_INF_SIGN 0x300
#endif

class Node 
{
    public:

        unsigned short get_byte() const;
        const std::size_t&  get_freq() const;
        void reset_byte(unsigned short b);
        void reset_freq(std::size_t fq);
        virtual bool is_leaf() const = 0;

        bool operator >  (const Node& n) const;
        bool operator <  (const Node& n) const;
        bool operator <= (const Node& n) const;
        bool operator >= (const Node& n) const;
        bool operator == (const Node& n) const;
        virtual ~Node();

    protected:

        Node(unsigned short Byte = static_cast<unsigned short>(NO_INF_SIGN),
             const std::size_t& Freq = 0);

        Node(const Node& n);
        Node(Node&& n);
        Node& operator = (const Node& n) = delete;
        Node& operator = (Node&& n) = delete;
        unsigned short byte;
        std::size_t freq;
};
