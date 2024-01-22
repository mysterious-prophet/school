#ifndef STATNODE
#define STATNODE
    #include "../../headers/Stat/StatNode.h"
#endif
 
bool StatNode::ptr_compare::operator () (const std::shared_ptr<const StatNode>& n1,
                                         const std::shared_ptr<const StatNode>& n2)
                                         const {

    return n1->get_freq() > n2->get_freq();
}

StatNode::StatNode(unsigned short Byte, const std::size_t& Freq,
                   const std::shared_ptr<StatNode>& Left,
                   const std::shared_ptr<StatNode>& Right) :

    Node(Byte, Freq), left(Left), right(Right) {}

StatNode::StatNode(std::shared_ptr<StatNode>&& Left,
                   std::shared_ptr<StatNode>&& Right,
                   unsigned short Byte, const std::size_t& Freq) :

    Node(Byte, Freq), left(std::move(Left)), right(std::move(Right)) {}

std::shared_ptr<const StatNode> StatNode::get_left() const {

    return left;
}

std::shared_ptr<const StatNode> StatNode::get_right() const {

    return right;
}

void StatNode::reset_left(const std::shared_ptr<StatNode>& Left) {

    left = Left;
}

void StatNode::reset_left(std::shared_ptr<StatNode>&& Left) {

    left = std::move(Left);
}

void StatNode::reset_right(const std::shared_ptr<StatNode>& Right) {

    right = Right;
}

void StatNode::reset_right(std::shared_ptr<StatNode>&& Right) {

    right = std::move(Right);
}

bool StatNode::is_leaf() const {
    
    return ((left == nullptr) || (right == nullptr));
}

StatNode::~StatNode() {}

StatNode::StatNode(const StatNode& stn) : Node(stn), left(nullptr), right(nullptr) {}

StatNode::StatNode(StatNode&& stn) :
    Node(std::move(stn)), left(std::move(stn.left)), right(std::move(stn.right)) {}

StatNode& StatNode::operator = (const StatNode& stn) {

    if(this == &stn){

        return * this;

    } else {

        byte = stn.byte;
        freq = stn.freq;
        left.reset();
        right.reset();
        return * this;
    }
}

StatNode& StatNode::operator = (StatNode&& stn) {
    
    if(this == &stn){

        return * this;

    } else {

        byte = stn.byte;
        stn.byte = static_cast<unsigned short>(NO_INF_SIGN);
        freq = std::move(stn.freq);
        left = std::move(stn.left);
        right = std::move(stn.right);
        return * this;
    }
}
