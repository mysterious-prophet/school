from math import log # For the print out of probabilities

# Custom local file imports
from algo_impl.TreeCompress_base_class import TreeCompress # When launched from main, this import works



class SHFCompress(TreeCompress):
	"SHF compression algorithm class that extends the base class: 'Compress'"

	def __init__(self):
		super().__init__("SHF")


	def split_list(self, prob_dict):
		"Splits the dictionary (list) using shannon-fano encoding"
		sorted_values = self.sort_by_value(prob_dict)

		# Find the middle value
		half = 0
		for v in list(prob_dict.values()):
			half += v
		half = half/2

		suml = 0
		l = []
		r = []
		i = len(sorted_values) - 1
		while i >= 0:
			char = sorted_values[i]
			# Add the char if its value added to the total sum of the 1st half will not cross the halfway value
			if suml < half:
				if abs(half - suml - prob_dict[char]) < abs(half - suml):
					l.append(char)
					suml += prob_dict[char]
				else:
					break	
			else:
				break
			i -= 1
		# "i" will stop iterating halfway through
		# Add the remaining values to the 2nd list
		while i >= 0:
			r.append(sorted_values[i])
			i -= 1
		
		# Return the two lists
		return (l, r)


	def get_tree(self, prob_dict):
		"Transforms a probability dictionary into an encoding decision tree using the shannon-fano split algorithm"
		tree = (None, None)
		# If there is only 1 character in the probability dictionary
		#  then return the only char as a list
		if len(prob_dict) == 1:
			return list(prob_dict.keys())[0]
		# If there are more characters => split
		else:
			# Split the list (probability dictionary) into 2
			x = self.split_list(prob_dict)
			left, right = x
			left_dict = dict()
			right_dict = dict()

			# Split the original dictionary according to the split list (list of chars)
			for x in left:
				left_dict[x] = prob_dict[x]
			for x in right:
				right_dict[x] = prob_dict[x]
			
			# Tree will be a tuple of the left and right dictionaries (recursion)
			tree = (self.get_tree(left_dict), self.get_tree(right_dict))
			return tree


	def get_prob_dict(self, text):
		"Calculates a probability dictionary for the input text"
		prob_dict = dict()
		unit = 1.0 / len(text)

		# Traverse the input text
		for char in text:
			# If the character is already in the dictionary, add 1/total_num_chars
			# -> That way, at the end there will the probability of occurence of this character
			if char in prob_dict:
				prob_dict[char] += unit
			# If the character is not found in the dictionary, add the default probability of 1/total_num_chars
			else:
				prob_dict[char] = unit
		return prob_dict
		

	def gen_codes(self, tree):
		"Turns the encoding decision tree into a dictionary with input chars and code words"
		# If the tree has more than 1 element and is a tuple
		if len(tree) == 2 and isinstance(tree, tuple):
			# Get code words for each subtree
			left, right = tree
			code_left = self.gen_codes(left)
			code_right = self.gen_codes(right)
			
			cout = dict()

			# Add a 0 for the left code values
			for key, val in code_left.items():
				cout[key] = f'0{val}'

			# Add a 1 for the right code values
			for key, val in code_right.items():
				cout[key] = f'1{val}'
			return cout
		# If the tree has 1 element
		else:
			return {tree: '0'}
	

	def preprocess(self, text):
		"Preprocesses the input text and returns its probability dictionary and code words"
		self.text = text
		# Get size of input text size
		self.num_chars = len(text)
		# Generate the probability dictionary
		self.prob_dict = self.get_prob_dict(self.text)

		# Generate codes for each character
		self.codes = self.gen_codes(self.get_tree(self.prob_dict))


	def encode_text(self, text):
		"Encodes the input text"
		# Get the code words for the input text
		self.preprocess(text)
		
		# Pre-allocate encoded text as array of strings for faster writing during computation
		encoded_text = [""] * self.num_chars

		# Get the code for each character in the text and append it to the resulting encoded text
		for i in range(self.num_chars):
			encoded_text[i] = self.codes[text[i]]
		return ''.join(encoded_text)


	def encode(self, text):
		return self.encode_text(text)
	

	def reverse_code(self, codes):
		"Reverses the code words"
		# https://stackoverflow.com/questions/1031851/how-do-i-exchange-keys-with-values-in-a-dictionary
		return {value: key for key, value in codes.items()}


	def decode(self, encoded_text):
		"Decodes the input text encoded by SHF"
		# Get the code words for the input text
		# - Could have passed the code words alone, but this allows for the decode function to be called from multiple algos
		#	-> For example, RLE algo doesn't have a code_word variable to pass to its decode function
		
		# Reverse the code
		reverse_mapping = self.reverse_code(self.codes)

		decoded_text = [""] * self.num_chars
		
		char_code = ""

		# For every bit (character) in the input encoded_text
		i = 0
		for bit in encoded_text:
			# Add the bit to the current code
			char_code += bit
			# If the current code is in the code
			if(char_code in reverse_mapping):
				# Get the character whose code corresponds to the current code
				#  and append the character to the decoded_text
				decoded_text[i] = reverse_mapping[char_code]
				# Reset the current code
				char_code = ""
				i += 1

		# If the char code was not reset, then the length of the encoded text was not correct (for this implementation). 
		if len(char_code) > 0:
			raise ValueError("problem found while decoding, '{}' is not a valid codeword".format((char_code)))
		return ''.join(decoded_text)


	def codes_to_str(self):
		"Outputs the probabilities and encoding of the input text"
		s = "\n"
		hx = 0.0
		length = 0.0
		sorted_chars = self.sort_by_value(self.prob_dict)
		for char in sorted_chars:
			codeword = self.codes[char]
			prob = self.prob_dict[char]
			hx += prob*log(prob,2)
			length += prob*len(self.codes[char])
			s += "'{}' --->>>   {:6} (p(x)={:01.4f}  H(x)={:01.4f} len={:01.4f}) ".format(char, codeword, prob, prob*log(prob,2), len(self.codes[char])*prob)
			s += "\n"
		return s[0:-1] + "\n H(x) = {:04.4f}  len(x) = {:04.4f}".format(-hx, length)