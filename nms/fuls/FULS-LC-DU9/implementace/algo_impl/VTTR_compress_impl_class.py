from bitstring import BitArray # For bitarray operations

# Custom local file imports
from algo_impl.FGK_compress_impl_class import Compress, SiblingPair



class VTTRCompress(Compress):
    "VTTR compression algorithm class that extends the base class: 'Compress'"

    def __init__(self):
        super().__init__("VTTR")


    def encode(self, text):
        "Encodes data using a Vitter Adaptive Huffman Algorithm"

        alphabet_pointers = dict([(chr(a), (-1, -1)) for a in range(128)])
        alphabet_pointers["NULL"] = (0, 0)

        # keep null pointer on all zeros
        init_pair = SiblingPair()
        init_pair.fp = (-1, -1)
        init_pair.bp = [("NULL", True), (text[0], True)]
        init_pair.count = [0.0, 1.0]
        alphabet_pointers[text[0]] = (0, 1)  # may be a 1 bit so check decoding
        sib_list = [init_pair]

        # Now we have generated the starting tree we can begin to order the list
        init_code = [int(a) for a in bin(ord(text[0]))[2:]]
        init_code = [0]*(7-len(init_code)) + init_code  # extend to make full 7 bits
        encoded_text = init_code
        #for i in tqdm(range(1, len(text))):
        for i in range(1, len(text)):
            code = []
            try:
                # non ASCII characters not set up to be decoded but this exception
                # handler will add it to the alphabet for benchmarking purposes
                a = alphabet_pointers[text[i]][0]
            except KeyError:
                print("Warning non ASCII character encoded, decoder will not recognise\n")
                alphabet_pointers[text[i]] = (-1, -1)

            if alphabet_pointers[text[i]][0] == -1:  # not yet in tree
                # create a new pair
                new_pair = SiblingPair()
                new_pair.count = [0.0, 0.0]
                new_pair.fp = (alphabet_pointers["NULL"][0], 0)
                new_pair.bp = [("NULL", True), (text[i], True)]
                sib_list.append(new_pair)
                sib_list[alphabet_pointers["NULL"][0]].bp[0] = (len(sib_list)-1, False)
                sib_list[alphabet_pointers["NULL"][0]].count[0] = 0.0

                pnt, bit = alphabet_pointers["NULL"]
                alphabet_pointers["NULL"] = (len(sib_list)-1, 0)
                alphabet_pointers[text[i]] = (len(sib_list)-1, 1)

                # generate the codeword
                while pnt != -1:  # note root node will not be added
                    code.append(bit)
                    pnt, bit = sib_list[pnt].fp
                code = code[::-1]  # as we are traversing leaves to root so codeword is reversed
                sym_code = [int(a) for a in bin(ord(text[i]))[2:]]
                code = code + [0]*(7-len(sym_code)) + sym_code

            else:
                # generate the codeword
                pnt, bit = alphabet_pointers[text[i]]
                while pnt != -1:  # note root node will not be added
                    code.append(bit)
                    pnt, bit = sib_list[pnt].fp

                code = code[::-1]  # as we are traversing leaves to root so codeword is reversed

            encoded_text += code
            sib_list, alphabet_pointers = self.modify_tree(sib_list, alphabet_pointers, char=text[i])

        return encoded_text


    def decode(self, encoded_text):
        "Decodes data using a Vitter Adaptive Huffman Algorithm"
        # first symbol will be uncompressed and 7 bits ascii
        decoded_text = []
        init_sym = encoded_text[:7]
        init_sym = chr(BitArray(init_sym).uint)

        decoded_text.append(init_sym)
        # initialise alphabet pointers with null
        alphabet_pointers = dict([(chr(a), (-1, -1)) for a in range(128)])
        alphabet_pointers["NULL"] = (0, 0)

        # keep null pointer on all zeros
        init_pair = SiblingPair()
        init_pair.fp = (-1, -1)
        init_pair.bp = [("NULL", True), (decoded_text[0], True)]
        init_pair.count = [0.0, 1.0]
        alphabet_pointers[decoded_text[0]] = (0, 1)  # may be a 1 bit so check decoding
        sib_list = [init_pair]

        pair = sib_list[0]  # initialise root which is at start of the list
        current_pnt = 0
        i = 7
        while i < len(encoded_text):

            bit = encoded_text[i]

            if pair.bp[bit][1]:  # reached leaf
                if pair.bp[bit][0] == "NULL":  # if new symbol
                    code = encoded_text[i+1:i+8] # gathers block code
                    i += 7  # additional incremented add at the end of the loop
                    symb = chr(BitArray(code).uint)
                    if alphabet_pointers[symb][0] != -1:
                        print("ERROR CURRENT TREE:")
                        print("ALPHABET POINTERS:")
                        for j, k in alphabet_pointers.items():
                            print("{}: {}".format(j, k))
                        print(decoded_text)
                        raise RuntimeError("Null root for existing items: {}".format(symb))
                    decoded_text.append(symb)

                    # create a new pair
                    new_pair = SiblingPair()
                    new_pair.count = [0.0, 0.0]
                    new_pair.fp = (alphabet_pointers["NULL"][0], 0)
                    new_pair.bp = [("NULL", True), (decoded_text[-1], True)]
                    sib_list.append(new_pair)
                    sib_list[alphabet_pointers["NULL"][0]].bp[0] = (len(sib_list)-1, False)
                    alphabet_pointers["NULL"] = (len(sib_list)-1, 0)
                    alphabet_pointers[decoded_text[-1]] = (len(sib_list)-1, 1)

                else:
                    decoded_text.append(pair.bp[bit][0])

                sib_list, alphabet_pointers = self.modify_tree(sib_list, alphabet_pointers, decoded_text[-1])

                current_pnt = 0
            else:
                current_pnt = pair.bp[bit][0]
            pair = sib_list[current_pnt]
            i += 1

        return decoded_text


    def modify_tree(self, sib_list, alphabet_pointers, char):
        "Modifies and exitsting sibling list for Adaptive Huffman algorithms based on a traversal list from an encoding or decoding process"
        # sib_list: list of SiblingPair() - List of sibling pair trees based on the ASCII character set
        #  -> This list will be modified to take into account the observed data
        # alphabet_pointers: dict - Dictionary of pointers to leaves of sib_list labelled with ascii characters
        #  -> This dict will be modified to take into account the observed data
        # char: character - Symbol that has been encoded on the tree
        # NOTE: Tree should be maintained such that all bp < fp and all
        # counts higher up the list <= than those below it

        get_out = False
        # check alphabet_pointers
        pnt, bit = alphabet_pointers[char]
        while pnt != -1:  # could skip first iteration if new char as will be in max place?
            for index in range(pnt+1):  # could do check that once greater than swap to that position to limit iterations
                for i in range(2):
                    if sib_list[index].count[1-i] == sib_list[pnt].count[bit]:  # 1-i to make sure it is left as possible
                        if (index, 1-i) == (pnt, bit) or (index, 1-i) == sib_list[pnt].fp:
                            # if already at highest order
                            # also don't swap with parent node
                            pass
                        else:
                            # swap fps and bps
                            bckpnt1 = sib_list[pnt].bp[bit]
                            if bckpnt1[1]:
                                alphabet_pointers[bckpnt1[0]] = (index, 1-i)
                            else:
                                sib_list[bckpnt1[0]].fp = (index, 1-i)

                            bckpnt2 = sib_list[index].bp[1-i]
                            if bckpnt2[1]:
                                alphabet_pointers[bckpnt2[0]] = (pnt, bit)
                            else:
                                sib_list[bckpnt2[0]].fp = (pnt, bit)

                            # swap bps
                            sib_list[pnt].bp[bit] = bckpnt2
                            sib_list[index].bp[1-i] = bckpnt1
                            pnt, bit = index, 1-i
                        get_out = True
                        break

                if get_out:
                    get_out = False
                    break

            sib_list[pnt].count[bit] += 1

            pnt, bit = sib_list[pnt].fp


        return sib_list, alphabet_pointers