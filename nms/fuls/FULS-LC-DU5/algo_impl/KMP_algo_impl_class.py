from Search_base_class import Search
from Search_base_class import datetime


# KMP algorithm class that extends the base class: 'Search'
class KMPSearch(Search):

	def __init__(self):
		super().__init__("KMP", "O(m+n)")


	# Overriding the dummy preprocess function
	def preprocess(self, pattern, m):
		start_t = datetime.now()
		# Pre-allocate array of Longest Proper prefix Sizes with 0s of size n
		lps = [0]*m

		i = 1 # We don't need to check the 0th position, as the proper prefix of the 0th position will always be ""
		while i < m: # this loop sets the number of elems to be considered pro proper prefix and suffix
			# all elems from 0...i find longest proper prefix, that is also a suffix of elems 0...i
			for j in range(1, i+1): # go from 0 to i included (i+1 will never be considered)
				if pattern[0:j] == pattern[i-j+1:i+1]:
					lps[i] = len(pattern[0:j])
			i += 1
		
		end_t = datetime.now()

		preprocess_t_ms = self.process_time_ms(start_t, end_t)
		return lps, preprocess_t_ms


	# Overriding the dummy function with the pure KMP search algorithm
	def pure_search(self, n, m, text, pattern, lps, index_list, pattern_count):
		i = 0
		j = 0
		while i < n:
			if pattern[j] == text[i]:
				i += 1
				j += 1
				if j == m:
					index_list.append(i-m)
					pattern_count += 1
					j = lps[j-1]
			elif j != 0:
				j = lps[j-1]
			else: # j == 0
				i += 1
		return index_list, pattern_count