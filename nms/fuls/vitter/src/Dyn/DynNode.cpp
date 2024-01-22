#ifndef DYNNODE
#define DYNNODE
    #include "../../headers/Dyn/DynNode.h"
#endif
 
DynNode::DynNode(unsigned short Byte, const std::size_t& Freq,
                 int Left, int Right, int Prev) :

    Node(Byte, Freq), left(Left), right(Right), prev(Prev) {}

int DynNode::get_left() const {

    return left;
}

int DynNode::get_right() const {

    return right;
}

int DynNode::get_prev() const {

    return prev;
}

void DynNode::reset_left(int Left) {

    left = Left;
}

void DynNode::reset_right(int Right) {

    right = Right;
}

void DynNode::reset_prev(int Prev) {

    prev = Prev;
}

bool DynNode::is_leaf() const {

    return ((left == NOTHING) && (right == NOTHING) && (byte != NO_INF_SIGN));
}

DynNode::~DynNode() {}

DynNode::DynNode(const DynNode& dn) :

Node(dn), left(NOTHING), right(NOTHING),
prev(NOTHING) {}

DynNode::DynNode(DynNode&& dn) :

Node(std::move(dn)), left(dn.left),
right(dn.right), prev(dn.prev) {

    dn.left = NOTHING;
    dn.right = NOTHING;
    dn.prev = NOTHING;
}

DynNode& DynNode::operator = (const DynNode& dn) {

    if(this == &dn){
        return * this;
    } else {
        byte = dn.byte;
        freq = dn.freq;
        left = right = prev = NOTHING;
        return * this;
    }
}

DynNode& DynNode::operator = (DynNode&& dn) {

    if(this == &dn){
        return * this;
    } else {
        byte = dn.byte;
        dn.byte = static_cast<unsigned short>(NO_INF_SIGN);
        freq = dn.freq;
        dn.freq = 0;
        left = dn.left;
        right = dn.right;
        prev = dn.prev;
        dn.left = dn.right = dn.prev = NOTHING;
        return * this;
    }
}
