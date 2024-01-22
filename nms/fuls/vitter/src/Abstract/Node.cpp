#ifndef NODE
#define NODE
    #include "../../headers/Abstract/Node.h" 
#endif

unsigned short Node::get_byte() const {

    return byte;
}

const std::size_t& Node::get_freq() const {

    return freq;
}

void Node::reset_byte(unsigned short b) {

    byte = b;
}

void Node::reset_freq(std::size_t fq) {

    freq = fq;
}

bool Node::operator > (const Node& n) const {

    return freq > n.freq;
}

bool Node::operator < (const Node& n) const {

    return freq < n.freq;
}

bool Node::operator <= (const Node& n) const {

    return freq <= n.freq;
}

bool Node::operator >= (const Node& n) const {

    return freq >= n.freq;
}

bool Node::operator == (const Node& n) const {

    return ((freq == n.freq) && (byte == n.byte));
}

Node::Node(unsigned short Byte, const std::size_t& Freq) :
freq(Freq) {

    if ((Byte <= 0x0FF) || ((Byte == 0x100) ||
        (Byte == 0x200) || (Byte == 0x300))) {

        byte = Byte;

    } else {
        
        byte = NO_INF_SIGN;
        freq = 0;
    }
}

Node::Node(const Node& n) : byte(n.byte), freq(n.freq) {}

Node::Node(Node&& n) : byte(n.byte), freq(std::move(n.freq)) {

    n.byte = static_cast<unsigned short>(NO_INF_SIGN);
}

Node::~Node() {}
