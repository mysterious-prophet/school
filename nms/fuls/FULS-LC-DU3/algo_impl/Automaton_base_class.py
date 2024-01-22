from Search_base_class import Search
from Search_base_class import datetime
from Search_base_class import READ_FILE_BY_ROW, PRINT_MATCH_INFO

class AutomatonSearch(Search):
	def __init__(self, name, complexity):
		super().__init__(name, complexity)

	def print_search_summary(self, keywords, match_list):
		if PRINT_MATCH_INFO["Matches found"] == True:
			if READ_FILE_BY_ROW == True:
				# For every row
				for row_id in range(0, len(match_list)):
					# If the row has some matches
					if len(match_list[row_id]) > 0:
						pattern_list = [idx[1] for idx in match_list[row_id]]
						for keyword in set(pattern_list):
							match_indexes = []
							# Find indexes of each matched keyword in pattern_list and save the indexes their matches in separate arrays.
							for idx, word in enumerate(pattern_list):
								if word == keyword:
									match_indexes.append(match_list[row_id][idx][0])
							print("Found the keyword \"" + keyword + "\" in row " + str(row_id) + \
									" beginning at index(es): " + str(match_indexes))
			else:
				pattern_list = [match[1] for match in match_list]
				for keyword in set(pattern_list):
					match_indexes = []
					for idx, word in enumerate(pattern_list):
						if word == keyword:
							match_indexes.append(match_list[idx][0])
					print("Found the keyword \"" + keyword + "\" beginning at index(es): " + str(match_indexes) + ".")		
		
		if PRINT_MATCH_INFO["Pattern count"] == True:
			if len(match_list) > 0:
				matches = []
				if READ_FILE_BY_ROW == True:
					# Re-format the match_list into a flat match list
					match_list = [item for sublist in match_list for item in sublist]
				# Format of match_list: (start_index,keyword,value)
				# -> keyword is at index 1
				for match in match_list:
					matches.append(match[1])
				pattern_count = [[x, matches.count(x)] for x in set(matches)]
				print("\nThe following keyword(s) was(were) found in the text [keyword, #matches]: " + str(pattern_count))

				not_matched = []
				for keyword in keywords:
					if keyword not in set(matches):
						not_matched.append(keyword)
				if not_matched:
					print("The following keyword(s) was(were) not found in the text: \"" + str(not_matched) + "\"")
			else:
				print("\nThe patterns \"" + str(keywords) + "\" were not found in the given text.")

	# Initializing variables for search algorithms
	def init_search(self, text, pattern):
		match_list = []
		n = len(text)
		
		if READ_FILE_BY_ROW == True:
			for _ in range(0, n):
				match_list.append([])
		print(len(match_list))
		return n, match_list

	# Redefine dummy preprocess, as AC and CW algos need different parameters (they don't need a preprocessed array) - compared to KMP/BM
	def preprocess(self, keywords):
		return [], 0.0

	# Redefine dummy pure_search, as AC and CW algos need different parameters (they don't need a preprocessed array) - compared to KMP/BM
	def pure_search(self, n, text, index_list):
		return []

	def search(self, text, keywords):
		"""Uses Aho-Corasick or Commentz-Walter algorithm to find all matches
		@param text: files to be checked for keywords
		@param keywords: list of keywords to search for
		@return: preprocesse time, search time elapsed to match all keywords against the file
		"""
		# Print the start of a given algorithm output in the console
		print("===START " + self.get_name())

		# Initialize starting variables
		n, match_list = self.init_search(text, keywords)

		# Preprocess the pattern
		keywords, preprocess_t_ms = self.preprocess(keywords)

		start_t = datetime.now()
		print("Search start: \t" + str(start_t))

		# Reading the input as and entire string or row by row.
		# This allows the output to show in which row and on which index of that row was a match found
		if READ_FILE_BY_ROW == False:
			match_list = self.pure_search(n, text, match_list)
		else:
			row_index = 0
			for row in text:
				n = len(row)
				match_list[row_index] = self.pure_search(n, row, match_list[row_index])
				row_index += 1
		
		end_t = datetime.now()
		print("Search finish: \t" + str(end_t))

		# print summarizing information about the matches of the pattern
		self.print_search_summary(keywords, match_list)

		search_t_ms = self.process_time_ms(start_t, end_t)
		print("\nTotal runtime: " + str(search_t_ms) + "ms")
		print("===FINISH " + self.get_name() + "\n")

		return preprocess_t_ms, search_t_ms