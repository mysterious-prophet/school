import sys # For the input file as an argument when launching the script
from datetime import datetime # For measuring preprocessing and search times

# Custom local file imports
from algo_settings import READ_FILE_BY_ROW, DEC_ACCURACY, PRINT_MATCH_INFO

# Base class for all search algorithms
class Search():
	def __init__(self, name, complexity):
		self.name = name
		self.complexity = complexity
		self.preprocess_t_ms = [] # Preprocessing time in ms
		self.search_t_ms = [] # Search time in ms
		self.sorted_time_cols = [] # Sorted columns of times of individual runs and total run times

	def get_name(self):
		return self.name
	
	def get_complexity(self):
		return self.complexity

	# Return time in ms between start_t and end_t
	def process_time_ms(self, start_t, end_t):
		t = end_t - start_t
		t_ms = round(t.total_seconds()*1000, DEC_ACCURACY) # secs to ms rounded to DEC_ACCURACY decimal places
		return t_ms

	# Print information about what pattern was found, how many times (pattern_count) and at what indexes (match_list)
	def print_search_summary(self, pattern, pattern_count, match_list):
		if PRINT_MATCH_INFO["Matches found"] == True:
			if READ_FILE_BY_ROW == True:
				for i in range(len(match_list)):
					if len(match_list[i]) > 0:
						print("Found the pattern \"" + pattern + "\" in row " + str(i) + \
							" beginning at index(es): " + str(match_list[i]))
			else:
				for i in match_list:
					print("Found the pattern \"" + pattern + "\" beginning at index " + str(i) + ".")
					
		if PRINT_MATCH_INFO["Pattern count"] == True:
			if pattern_count > 0:
				print("\nThe pattern \"" + pattern + "\" was found " + str(pattern_count) + " times in the given text.")
			else:
				print("\nThe pattern \"" + pattern + "\" was not found in the given text.")

	# Initializing variables for search algorithms
	def init_search(self, text, pattern):
		match_list = []
		pattern_count = 0
		n = len(text)
		m = len(pattern)
		
		if READ_FILE_BY_ROW == True:
			for _ in range(0, n):
				match_list.append([])
		print(len(match_list))
		return n, m, match_list, pattern_count

	# Dummy function - placeholder for preprocess function that each extended search algorithm class will override
	def preprocess(self, pattern, m):
		return [], 0.0

	# Dummy function - placeholder for the pure search algorithm function that each extended search algorithm class will override
	def pure_search(self, n, m, text, pattern, place_holder_arr, index_list, pattern_count):
		return [], 0

	# Basic search function that assumes a given extended search algorithm class has a preprocess function.
	# -> If it doesn't, then the extended class must override this function
	# -> This was done because the majority of extended search algorithm classes have a preprocess function.
	# => Returns: preprocess and search times for recording benchmark results
	def search(self, text, pattern):
		# Print the start of a given algorithm output in the console
		print("===START " + self.get_name())

		# Initialize starting variables
		n, m, match_list, pattern_count = self.init_search(text, pattern)

		# Preprocess the pattern
		pre_processed_pattern, preprocess_t_ms = self.preprocess(pattern, m)

		start_t = datetime.now()
		print("Search start: \t" + str(start_t))

		# Reading the input as and entire string or row by row.
		# This allows the output to show in which row and on which index of that row was a match found
		if READ_FILE_BY_ROW == False:
			match_list, pattern_count = self.pure_search(n, m, text, pattern, pre_processed_pattern,\
														 match_list, pattern_count)
		else:
			row_index = 0
			for row in text:
				n = len(row)
				match_list[row_index], pattern_count = self.pure_search(n, m, row, pattern, pre_processed_pattern,\
																	    match_list[row_index], pattern_count)
				row_index += 1
		
		end_t = datetime.now()
		print("Search finish: \t" + str(end_t))

		# print summarizing information about the matches of the pattern
		self.print_search_summary(pattern, pattern_count, match_list)

		search_t_ms = self.process_time_ms(start_t, end_t)
		print("\nTotal runtime: " + str(search_t_ms) + "ms")
		print("===FINISH " + self.get_name() + "\n")

		return preprocess_t_ms, search_t_ms