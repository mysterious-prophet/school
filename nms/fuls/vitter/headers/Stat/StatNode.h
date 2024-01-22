#ifndef NODE
#define NODE
    #include "../Abstract/Node.h"
#endif

#ifndef MEMORY
#define MEMORY
    #include <memory>
#endif

#ifndef INTERNAL_NODE_SIGN
#define INTERNAL_NODE_SIGN 0x100
#endif

class StatNode final : public Node
{
    public:

        class ptr_compare
        {
            public:
                
                bool operator () (const std::shared_ptr<const StatNode>& n1,
                                  const std::shared_ptr<const StatNode>& n2) const; 
        };

        // constructors
        
        StatNode(unsigned short Byte = static_cast<unsigned short>(NO_INF_SIGN),
                 const std::size_t& Freq = 0,
                 const std::shared_ptr<StatNode>& Left = nullptr,
                 const std::shared_ptr<StatNode>& Right = nullptr);

        StatNode(std::shared_ptr<StatNode>&& Left,
                 std::shared_ptr<StatNode>&& Right, 
                 unsigned short Byte = static_cast<unsigned short>(NO_INF_SIGN),
                 const std::size_t& Freq = 0);

        StatNode(const StatNode& stn);
        StatNode(StatNode&& stn);

        // get children
        std::shared_ptr<const StatNode> get_left() const;
        std::shared_ptr<const StatNode> get_right() const;

        // reset children
        void reset_left(const std::shared_ptr<StatNode>& Left);
        void reset_left(std::shared_ptr<StatNode>&& Left);
        void reset_right(const std::shared_ptr<StatNode>& Right);
        void reset_right(std::shared_ptr<StatNode>&& Right);

        // operators of assignment
        StatNode& operator = (const StatNode& stn);
        StatNode& operator = (StatNode&& stn);

        virtual bool is_leaf() const;

        virtual ~StatNode();

    protected:

        std::shared_ptr<StatNode> left;
        std::shared_ptr<StatNode> right;
};
