#ifndef NODE
#define NODE
    #include "../Abstract/Node.h"
#endif

#ifndef NOTHING
#define NOTHING -1
#endif

class DynNode final : public Node
{
    public:

        DynNode(unsigned short Byte = static_cast<unsigned short>(NO_INF_SIGN),
                const std::size_t& Freq = 0, int Left = NOTHING,
                int Right = NOTHING, int Prev = NOTHING);

        DynNode(const DynNode& dn);
        DynNode(DynNode&& dn);

        DynNode& operator = (const DynNode& dn);
        DynNode& operator = (DynNode&& dn);

        int get_left() const;
        int get_right() const;
        int get_prev() const;
        void reset_left(int Left);
        void reset_right(int Right);
        void reset_prev(int Prev);
        virtual bool is_leaf() const;

        virtual ~DynNode();

    protected:

        int  left;
        int  right;
        int  prev;
};
