from pathlib import Path # For path operations - if input data is instance of string or a data paths

# Custom local file imports
from algo_impl.Compress_base_class import Compress, settings



class RLECompress(Compress):
	"RLE compression algorithm class that extends the base class: 'Compress'"

	def __init__(self):
		super().__init__("RLE", False)


	def encode_text(self, text):
		"Encodes the input text"
		# Get size of input text size
		self.num_chars = len(text)
		# Pre-allocate output text as array of strings for faster writing during computation
		encoded_text = [""] * (self.num_chars + 1)
		prev_char = ''
		count = 1

		if not text: return ''

		i = 0
		for char in text:
			# If the prev and current characters don't match
			#  then add the count of the previous character and the character to the encoded text
			if char != prev_char:
				if prev_char != '':
					# https://stackoverflow.com/a/38362140/7941877
					# f'{count}|{prev_char}|' is the equivalent of str(count) + "|{}|".format(prev_char) 
					encoded_text[i] = f'{count}|{prev_char}|'
				# Reset the counter for the current character
				count = 1
				# Set the previous character to be the current character
				prev_char = char
			# Else: if the characters match
			else:
				# Increment the character counter
				count += 1
			i += 1
		# If there are no more characters in the text (i.e. if char is not a character)
		else:
			# Finish off the encoding
			encoded_text[i] = f'{count}|{prev_char}|'
			return ''.join(encoded_text)


	def encode(self, data):
		if isinstance(data, Path):
			return -1
			# TODO: Implement reading file by chunks if needed
			# 		return self.encode_file_by_chunks(data)
		if isinstance(data, str):
			return self.encode_string(data)

	
	def encode_string(self, text):
		return self.encode_text(text)
		

	def decode(self, encoded_text):
		"Decodes the input text encoded by RLE"
		# Pre-allocate output text as array of strings for faster writing during computation
		decoded_text = [""] * self.num_chars
		count = ''
		is_count = True

		i = 0
		for char in encoded_text:
			# If char is the separator, then flip the bool
			if char == "|":
				is_count = not is_count
				continue
			
			# * is_count == True => load count of symbol, until the next "|" is encountered
			# * is_count == False => write the char "count" times and then the next "|" is encountered and bool is flipped
			if is_count == True:
				count += char
			else:
				decoded_text[i] = char * int(count)
				count = ''
				i += 1
			
		return ''.join(decoded_text)