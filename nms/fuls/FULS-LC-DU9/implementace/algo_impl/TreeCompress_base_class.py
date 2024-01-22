# Custom local file imports
from algo_impl.Compress_base_class import Compress # When launched from main, this import works



class TreeCompress(Compress):
	"Base class for certain Compression algorithms that use trees"

	def preprocess(self, text):
		self.codes = {}
	

	def sort_by_value(self, dictionary):
		"Returns the keys of a dictionary sorted by their values (ascending)"
		# Get the items of the probability dictionary as tuples
		items = list(dictionary.items())
		# Transform the tuples into arrays, but swap the order to be: (code, char)
		backitems = [ [v[1], v[0]] for v in items ]
		# Sort the array according the 1st element of each arr and reverse the sorted list, so that it is in ascending order
		backitems.sort(reverse=True)
		# Retun the chars sorted according to their values
		return [ backitems[i][1] for i in range(0, len(backitems)) ]


	def codes_to_str(self):
		"Dummy function that will be overriden in impl classes that inherit from this class"
		return None


	def print_preprocessing_results(self):
		"Quick method to print preprocessing results"
		print(self.codes_to_str())


	def get_nice_encoded_text(self, encoded_text, separator = "|"):
		"Prints out the encoded text with separators between each encoded word"
		output = ""
		n = len(encoded_text)
		i = 0
		while i < n:
			j = i + 1
			while j <= n:
				if encoded_text[i:j] in self.codes.values():
					output += encoded_text[i:j] + separator
					i += len(encoded_text[i:j]) - 1 # Has to have -1, cause otherwise for loop will increment it too far
					break
				else:
					j += 1
			i += 1
		return output