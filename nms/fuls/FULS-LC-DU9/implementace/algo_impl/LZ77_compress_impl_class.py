import struct # For storing encoded data as structs of bytes
import math   # For calculatin the max lookahead

# Custom local file imports
from algo_impl.Compress_base_class import Compress



class LZ77Compress(Compress):
    "LZ77 compression algorithm class that extends the base class: 'Compress'"

    def __init__(self):
        super().__init__("LZ77", encoded_text_in_bits = False)
        # Contants x, MAX_SEARCH determine the size of the look-ahead ahead
        self.x = 16
        self.MAX_SEARCH = int(1024)


    def search(self, search, look_ahead):
        "Search for the longest word in the search window that is also a prefix of the look-ahead window"
        # Get the sizes of windows
        len_search = len(search)
        len_look_ahead = len(look_ahead)

        # If the search window is not looking at anything (it has no elements)
        if len_search == 0:
            # Return 0 steps back to the 1st index of the potentially repeating string,
            #  0 length of the potentially repeating string, and the first character of the look-ahead window
            #  as that is the following character that doesn't match
            return (0, 0, look_ahead[0])
        
        # If the look-ahead window is empty (end of input), then return -1 and an emapty string
        if len_look_ahead == 0:
            return (-1, -1, "")

        # Determine the best length and offset and show the entire window
        best_length = 0
        best_offset = 0
        buffer = search + look_ahead

        # Initialize the search pointer as the end of the search window
        search_pointer = len_search

        # Go through the elements of the search window
        #  -> 'i' will serve as the starting indexes for the word in the search window
        for i in range(0, len_search):
            length = 0
            # While the word beginning at index 'i' with len 'length' in the search window 
            #  (buffer[0:len_search] is search[]) matches with a prefix of the same length in the look-ahead window
            # i.e. while the char at i+length matches the char at search_pointer+length
            while buffer[i + length] == buffer[search_pointer + length]:
                # Try making the searched word longer (length matched, so try length + 1)
                length += 1
                # If the prefix in the look-ahead window would reach the end of the buffer (out of array index)
                if search_pointer + length == len(buffer):
                    # Change back the length and break
                    length -= 1
                    break
                # If the length of the word in the search window would reach into the look-ahead window
                #  the matching needs to be stopped
                if i + length >= search_pointer:
                    break
            # If the length of the word that was just found is better than the best length
            if length > best_length:
                # There is a new best length 
                best_offset = i
                best_length = length
        # Return the offset and length of the longest matching word in the search window, that is 
        #  also a prefix in the look-ahead window, and the character that follows the longest matched 
        #   word in the look-ahead window
        return (best_offset, best_length, buffer[search_pointer + best_length])


    def encode_text(self, text):
        "Encode the input string using the lZ77 algorithm into a byte string"
        # Get the size of the maximum look-ahead
        MAXLH =  int(math.pow(2, (self.x - (math.log(self.MAX_SEARCH, 2)))))

        # Initialize vars
        searchiterator = 0
        lhiterator = 0
        encoded_text = []

        # Go through the input text
        while lhiterator < len(text):
            # Create the search window (iterators mark the first index of each window)
            search = text[searchiterator:lhiterator]
            # Create the look-ahead window
            look_ahead = text[lhiterator:lhiterator + MAXLH]
            # Get the longest word in the search window, that is also a prefix of the look-ahead window
            #  (how many positions back in the text is it found what is its length),
            #  along with the character that follows it (the first character that doesn't match) 
            (offset, length, char) = self.search(search, look_ahead)
            
            # Bitwwise shifting to hide two numbers into one (simpler into bytes)
            # Example of how this is used here can be found in the decode function 
            shifted_offset = offset << 6
            offset_and_length = shifted_offset + length

            # https://docs.python.org/3/library/struct.html
            # Pack the offset and length along with the character into a struct as bytes:
            # > := A big-endian system stores the most significant byte of a word at the smallest 
            #      memory address and the least significant byte at the largest.
            # H := Unsigned short 2 bytes (used for the offset_and_length)
            #      -> The size of the full window (search + look-ahead window) is the max offset
            #      -> We have 
            # c := char (bytes of length 1) (used for the char) 
            ol_bytes = struct.pack(">Hc", offset_and_length, char.encode('utf-8'))
            # Append it to the array of structs of bytes
            encoded_text.append(ol_bytes)

            # Increment the look-ahead iterator index by the length of the repeated word and the length of the char (+1)
            #  Because we encoded the repeated word and the character, so we move onto the next part of the input text
            lhiterator += length + 1

            # Increment the search iterator index according to the lhiterator index,
            #  and take away the max size of the search window => beginning index of the search window
            searchiterator = lhiterator - self.MAX_SEARCH

            # If the max search window size goes too far, reset the search iterator 
            if searchiterator < 0:
                searchiterator = 0

        # Return the array of structs of bytes as a byte string
        return b''.join(encoded_text)


    def encode(self, data):
        "Encode the input text"
        return (self.encode_text(data) if isinstance(data, str) else None) 


    def decode(self, enoded_text):
        "Decode the encoded input byte string" 
        byte_char_array = []

        # Go through the encoded input string by increment of 3:
        #   (2 bytes (size of unsigned short) + 1 byte (size of char))
        #  -> encoded input contains packed structs of 2 + 1 bytes:
        #     -> unsigned short for offset and length
        #     -> char for the character
        for i in range(0, len(enoded_text), 3):
            # unpack, every 3 bytes (offset_and_length, byte_char)
            offset_and_length, byte_char = struct.unpack(">Hc", enoded_text[i:i+3])

            # bitwise shifting
            # -> example:
            #    offset = 10; length = 3
            #    in encode: 10 = 1010 << 6 -> 1010000000 = 640; 640 + 3 = 643
            #    here: 643 = 1010000011 >> 6 -> 1010 = 10; 643 - (1010 << 6) = 643 - 640 = 3
            # shift right, get offset (length dissapears)
            offset = offset_and_length >> 6

            # substract by offset, gives length value
            length = offset_and_length - (offset << 6)

            # case is (0, 0, c)
            if (offset == 0) and (length == 0):
                # Append to the byte character array
                byte_char_array.append(byte_char)

            # case is (x, y, c)	
            else:
                # Set the max "going back" distance for repeated words
                iterator = len(byte_char_array) - self.MAX_SEARCH
                # If we have gone back too far
                if iterator < 0:
                    iterator = offset
                else:
                    iterator += offset
                # Add characters in the repeated word according to pointers in the byte char array
                for pointer in range(0, length):
                    byte_char_array.append(byte_char_array[iterator + pointer])
                # Finally, add the character itself
                byte_char_array.append(byte_char)
        # Create a byte string from the byte char array and decode the byte string into regular chars
        return b''.join(byte_char_array).decode("utf-8")