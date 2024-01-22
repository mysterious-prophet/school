import struct # For storing encoded data as structs of bytes

# Custom local file imports
from algo_impl.Compress_base_class import Compress



class LZ78Compress(Compress):
    "LZ78 compression algorithm class that extends the base class: 'Compress'"

    def __init__(self):
        super().__init__("LZ78", False)
        # data type used to store the data type representing the position. Values:
        # -> H - Unsigned short     (2 bytes)
        # -> I - Unsigned int       (4 bytes)
        # -> Q - Unsigned long long (8 bytes)
        # - The final value will be set according to text size (see encode func).
        self.data_type = "H"
        # Number of bytes used to store one entry in encoded output (2/4/8 bytes for pos + 1 byte for buf)
        self.skip = 3


    def set_pos_store_data_type(self, text_len):
        "Set the data type for storing the char's position in the dictionary and set the skipping of reading the encoded bytes accordingly to this size"
        # The position parameter determines how far we need to look back to copy an entry in a dict.
        #  -> Worst case: look from end of the file to the beginning (same symbol at the beginning and end of a file).
        #  => The position will be the length of the input text
        # We need to decide what data type we need to used to store the position parameter (unsigned short/int/long long)
        #  -> Each has different number of bytes: 2/4/8
        #  -> The less bytes needed to represent the position, the better the compression ratio
        #  => We need to choose the best data type, the smaller in bytes the better
        # Also determine the skip accordinly
        #  -> When decoding, we will read byte-by-byte, we will need to skip by 2/4/8 + 1 = 3/5/9 bytes
        #     (2/4/8 bytes for pos, 1 byte for char)
        if 65535 < text_len <= 4294967295:
            self.data_type = "I"
            self.skip = 5
        elif text_len > 4294967295:
            self.data_type = "Q"
            self.skip = 9


    def get_buffer(self, buf, dictionary):
        # If the buffer is one char, then we're adding a new character => pos = 0
        if len(buf) == 1:
            pos = 0
        # If the buffer is more than one char (buf will never be empty, unless it is the end of 
        #  the file - covered in last step of for loop in encode_text)
        else:
            # Remove the last character from the buffer
            char = buf[:-1]
            # Get the position of the already known char (the string before the last character of buf)
            pos = dictionary[char]
            # Save the last char of the buffer
            buf = buf[-1]
        # Pack self.data_type (H/I/Q) for the position of the already known word and a character (c) that
        #  follows the known word
        ol_bytes = struct.pack(f'>{self.data_type}c', pos, buf.encode('utf-8'))
        return ol_bytes
        

    def encode_text(self, text):
        "Encode the input string using the lZ78 algorithm into a byte string"
        # set the max position and skipping of bytes cccording to the length of the text 
        self.set_pos_store_data_type(len(text))

        # Initialize variables
        encoded_text = []
        dictionary = {}
        buf = ""
        position = 1

        # For each character in the text
        for char in text:
            # Add the character to the buffer
            buf += char

            # If the current buffer is not in the dictionary
            if buf not in dictionary:
                # Add the position of the character in the dict as the value
                dictionary[buf] = position
                # Shift the position
                position += 1
                # Add the packed struct of byte consisting of the pos of the known word
                #  and the char that comes after the known word, to the encoded struct array
                encoded_text.append(self.get_buffer(buf, dictionary))
                buf = ""
        else:
            # If buf is empty and it is the end of the file, then struct will fail when packin an empty string
            if len(buf) > 0:
                # Add the packed struct of byte consisting of the pos of the known word
                #  and the char that comes after the known word, to the encoded struct array
                encoded_text.append(self.get_buffer(buf, dictionary))

        # Return a byte string created by joining elems of the packged structs of encoded entries in bytes
        return b''.join(encoded_text)

    
    def encode(self, data):
        "Encode the input text"
        return self.encode_text(data)


    def decode(self, encoded_text):
        "Decode the encoded input byte string"
        # Intialize the array for the characters encoded in bytes
        byte_char_array = []

        # Loop through the array by skipping along the bytes by the size of the struct
        for i in range(0, len(encoded_text), self.skip):
            # https://docs.python.org/3/library/struct.html
            # Unpack the struct of length self.skip -> the character in bytes and the index (position)
            #  of the prefix in the dictionary
            index, byte_char = struct.unpack(f'>{self.data_type}c', encoded_text[i:i+self.skip])

            # If the index of the item in the dictionary is 0, then there is nothing to add from the previous
            #  chars (no string to use from before) => append the byte of the char
            if index == 0:
                byte_char_array.append(byte_char)
            # If the index is greater than 0
            else:
                # Get the prefix from the already set bytes
                prefix = byte_char_array[index - 1]
                # Append the byte char of the prefix and the current byte_char
                byte_char_array.append(prefix + byte_char)
        
        # Return the byte string formed from joining elems of the byte char array and decode them 
        #  into normals characters
        return b''.join(byte_char_array).decode('utf-8')