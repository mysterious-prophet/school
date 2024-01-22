import heapq # For managing the heap

# Custom local file imports
from algo_impl.TreeCompress_base_class import TreeCompress # When launched from main, this import works
from algo_impl.HUFF_node_class import HuffNode # When launched from main, this import works



class HUFFCompress(TreeCompress):
    "HUFF compression algorithm class that extends the base class: 'Compress'"
    
    def __init__(self):
        super().__init__("HUFF")


    def make_frequency_dict(self, text):
        "Calculates a frequency dictionary for the input text"
        frequency = {}

        for character in text:
            # If the character is not found in the dictionary, then initialize it with 0 occurence
            if not character in frequency:
                frequency[character] = 0

            # Increment the count of the current character
            frequency[character] += 1
        return frequency


    def make_heap(self, frequency):
        "Creates the heap of Huffman nodes"
        # For every item in the frequency dictionary take the character and frequency
        for key, freq in frequency.items():
            # Create a Huffman node with the key (character) and occurence frequency of that character in the input text
            node = HuffNode(key, freq)
            # Add the node to the heap
            heapq.heappush(self.heap, node)


    def merge_nodes(self):
        "Transforms the Heap into a tree structure using HuffNode and its 'left' and 'right' (chars with larger frequencies are on the right)"
        # While the heap of Huffman nodes (each node: char and its frequency) still has more Huffman nodes than just the root
        while(len(self.heap) > 1):

            # Pop the two smallest nodes from the heap (that's why we need the overloading of the "less than" operator in the HuffNode class)
            node1 = heapq.heappop(self.heap)
            node2 = heapq.heappop(self.heap)

            # Merge the nodes into a new node that has no character, but it has the sum of the nodes' frequencies
            merged = HuffNode(None, node1.freq + node2.freq)
            # Set the left and right child of this node to be the two popped nodes (left -> smaller freq, right -> larger freq)
            merged.left = node1
            merged.right = node2

            # Add the merged node to the heap
            heapq.heappush(self.heap, merged)


    def make_codes_helper(self, root, current_code):
        "Helper function to create the code recursively"

        # If the root doesn't exist, return
        if(root == None):
            return

        # If the input node has a character (i.e. it is a leaf node)
        if(root.char != None):
            # Set the code for the character to the current code
            self.codes[root.char] = current_code
            # Set the character code to the current code (inverse function for decoding)
            self.reverse_mapping[current_code] = root.char
            # Leaf node has no children, return
            return

        # The current node (root) has children, as it isn't a leaf node
        # Recursively make the code for the left and right children
        # -> append 0 to the current code for the left subtree
        # -> append 1 to the current code for the right subtree
        # f'{current_code}0' is equivalent to: current_code + '0'
        self.make_codes_helper(root.left, f'{current_code}0')
        self.make_codes_helper(root.right, f'{current_code}1')


    def make_codes(self):
        "Turns the Huffman tree into a dictionary with input chars and code words"
        # Huffman tree (heap contains only the root, which has left and right children)
        root = heapq.heappop(self.heap)
        current_code = ""
        self.make_codes_helper(root, current_code)


    def encode_text(self, text):
        "Helper function to encode the input text using the generated code"
        self.preprocess(text)
        # Get size of input text size
        self.num_chars = len(text)
        # Pre-allocate output text as array of strings for faster writing during computation
        encoded_text = [""] * self.num_chars

        # For each character in the text, append its code to the end of the encoded_text string
        for i in range(self.num_chars):
            encoded_text[i] = self.codes[text[i]]

        return ''.join(encoded_text)
        

    def preprocess(self, text):
        "Initializes the class variables and compute the code for the input text"
        self.text = text
        self.heap = []
        self.codes = {}
        self.reverse_mapping = {}

        self.frequency_dict = self.make_frequency_dict(text)
        self.make_heap(self.frequency_dict)
        self.merge_nodes()
        self.make_codes()


    def encode(self, text):
        "Encodes the input text"
        return self.encode_text(text)


    def decode_text(self, encoded_text):
        "Helper function to decode the input text using the generated reverse code"
        # reverse code (reverse_mapping) := dictionary of codes with characters as values

        current_code = ""
        decoded_text = [""] * self.num_chars

        # For every bit (character) in the input encoded_text
        i = 0
        for bit in encoded_text:
            # Add the bit to the current code
            current_code += bit
            # If the current code is in the code
            if(current_code in self.reverse_mapping):
                # Get the character whose code corresponds to the current code
                #  and append the character to the decoded_text
                decoded_text[i] = self.reverse_mapping[current_code]
                # Reset the current code
                current_code = ""
                i += 1
            
        return ''.join(decoded_text)


    def decode(self, text):
        "Decodes the input text"
        return self.decode_text(text)


    def codes_to_str(self):
        "Outputs the frequencies and encoding of the input text"
        s = "\n"
        length = 0.0
        sorted_chars = self.sort_by_value(self.frequency_dict)
        for char in sorted_chars:
            codeword = self.codes[char]
            freq = self.frequency_dict[char]
            length += freq*len(self.codes[char])
            s += "'{}' --->>>   {:6} (freq(x)={:01.4f}  len={:01.4f}) ".\
                format(char, codeword, freq, len(self.codes[char])*freq)
            s += "\n"
        # len(x) := Length of encoded text in bits (0s and 1s obtained from codes)
        return s[0:-1] + "\n len(x) = {:04.4f}".format(length)