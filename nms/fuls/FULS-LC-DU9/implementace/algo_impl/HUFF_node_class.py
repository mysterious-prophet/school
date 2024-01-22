class HuffNode:
    def __init__(self, char, freq):
        "Initialize the node of a Huffman tree with its left and right children and a given character and frequrency"
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None


    def __lt__(self, other):
        "Overload the lt (less than) operator for the node"
        if(other == None):
            return -1
        if(not isinstance(other, HuffNode)):
            return -1
        return self.freq < other.freq