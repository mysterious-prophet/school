from Search_base_class import Search
from Search_base_class import datetime

# BM algorithm class that extends the base class: 'Search'
class BMSearch(Search):

	def __init__(self):
		super().__init__("BM", "O(m)")

	# Overriding the dummy preprocess function
	def preprocess(self, pattern, m):
		start_t = datetime.now()

		# Number of characters in UCS2 Unicode
		NO_OF_CHARS = 65536

		# Initialize all occurrence as -1 
		bad_char = [-1]*NO_OF_CHARS

		# Fill the actual value of last occurrence for i in range(0, n):
		for i in range(0, m):
			bad_char[ord(pattern[i])] = i

		end_t = datetime.now()
		preprocess_t_ms = self.process_time_ms(start_t, end_t)
		return bad_char, preprocess_t_ms

	# Overriding the dummy function with the pure BM search algorithm
	def pure_search(self, n, m, text, pattern, bad_char, index_list, pattern_count):
		i = 0
		while i < n - m:
			skip = 0
			for j in range(m-1, -1, -1):
				if pattern[j] != text[i+j]:
					skip = max(1, j - bad_char[ord(text[i+j])])
					break
			if (skip == 0):
				index_list.append(i)
				pattern_count += 1
				skip += 1
			i += skip
		return index_list, pattern_count