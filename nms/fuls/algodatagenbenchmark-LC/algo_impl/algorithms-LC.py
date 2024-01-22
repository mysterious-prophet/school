from datetime import datetime
import csv
import csv_summary

#################### SETUP:

#  Default accuracy that time in ms will be rounded to. Taken from csv_summary.py
DEC_ACCURACY = csv_summary.DEC_ACCURACY

# The input file with be read by row (delimited by '\n'). By default, the file that is to be read by row is a csv in the '/input_data' dir
READ_FILE_BY_ROW = True

# Number of times that each format will be run
ITERATIONS = 3

# Print the indexes at which a match was found and how many times the pattern was found
PRINT_MATCH_INFO = [True, True]

#################### END OF SETUP


# Return time in ms between start_t and end_t
def process_time_ms(start_t, end_t):
	t = end_t - start_t
	t_ms = round(t.total_seconds()*1000, DEC_ACCURACY) # secs to ms rounded to DEC_ACCURACY decimal places
	return t_ms

# Print information about what pattern was found, how many times (pattern_count) and at what indexes (match_list)
def print_search_summary(pattern, pattern_count, match_list):
	if PRINT_MATCH_INFO[0] == True:
		if READ_FILE_BY_ROW == True:
			for i in range(len(match_list)):
				if len(match_list[i]) > 0:
					print("Found the pattern \"" + pattern + "\" in row " + str(i) + " beginning at index(es): " + str(match_list[i]))
		else:
			for i in match_list:
				print("Found the pattern \"" + pattern + "\" beginning at index " + str(i) + ".")
				
	if PRINT_MATCH_INFO[1] == True:
		if pattern_count > 0:
			print("\nThe pattern \"" + pattern + "\" was found " + str(pattern_count) + " times in the given text.")
		else:
			print("\nThe pattern \"" + pattern + "\" was not found in the given text.")

def init_search(pattern, text):
	match_list = []
	pattern_count = 0
	n = len(pattern)
	m = len(text)
	
	if READ_FILE_BY_ROW == True:
		for _ in range(0, m):
			match_list.append([])
	return n, m, match_list, pattern_count

class ElementarySearch():

	def __init__(self):
		self.preprocess_t_ms = []
		self.search_t_ms = []
		self.sorted_time_cols = []

	def get_name(self):
		return "Elementary"

	def get_complexity(self):
		return "O(mn)"

	def pure_search(self, m, n, pattern, text, index_list, pattern_count):
		for i in range(0, m-n+1):
			for j in range(0, n):
				if pattern[j] != text[i+j]:
					break
				elif j == n - 1:
					index_list.append(i)
					pattern_count += 1
		return index_list, pattern_count

	def search(self, pattern, text):
		print("===START ELEM")
		n, m, match_list, pattern_count = init_search(pattern, text)

		start_t = datetime.now()
		print("Search start: \t" + str(start_t))

		if READ_FILE_BY_ROW == False:
			match_list, pattern_count = self.pure_search(m, n, pattern, text, match_list, pattern_count)
		else:
			row_index = 0
			for row in text:
				m = len(row)
				match_list[row_index], pattern_count = self.pure_search(m, n, pattern, row, match_list[row_index], pattern_count)
				row_index += 1

		end_t = datetime.now()
		print("Search finish: \t" + str(end_t))

		print_search_summary(pattern, pattern_count, match_list)		

		search_t_ms = process_time_ms(start_t, end_t)
		print("Total runtime: " + str(search_t_ms) + "ms")
		preprocess_t_ms = 0.0
		print("===FINISH ELEM\n")
		return preprocess_t_ms, search_t_ms

class KMPSearch():

	def __init__(self):
		self.preprocess_t_ms = []
		self.search_t_ms = []
		self.sorted_time_cols = []

	def get_name(self):
		return "KMP"

	def get_complexity(self):
		return "O(m+n)"

	def preprocess(self, pattern, n):
		start_t = datetime.now()
		# Pre-allocate array of Longest Proper prefix Sizes with 0s of size n
		lps = [0]*n

		i = 1 # We don't need to check the 0th position, as the proper prefix of the 0th position will always be ""
		while i < n: # this loop sets the number of elems to be considered pro proper prefix and suffix
			# all elems from 0...i find longest proper prefix, that is also a suffix of elems 0...i
			for j in range(1, i+1): # go from 0 to i included (i+1 will never be considered)
				if pattern[0:j] == pattern[i-j+1:i+1]:
					lps[i] = len(pattern[0:j])
			i += 1
		
		end_t = datetime.now()

		preprocess_t_ms = process_time_ms(start_t, end_t)
		return lps, preprocess_t_ms

	def pure_search(self, m, n, pattern, text, lps, index_list, pattern_count):
		i = 0
		j = 0
		while i < m:
			if pattern[j] == text[i]:
				i += 1
				j += 1
				if j == n:
					index_list.append(i-n)
					pattern_count += 1
					j = lps[j-1]
			elif j != 0:
				j = lps[j-1]
			else: # j == 0
				i += 1
		return index_list, pattern_count

	def search(self, pattern, text):
		print("===START KMP")
		n, m, match_list, pattern_count = init_search(pattern, text)

		lps, preprocess_t_ms = self.preprocess(pattern, n)

		start_t = datetime.now()
		print("Search start: \t" + str(start_t))

		if READ_FILE_BY_ROW == False:
			match_list, pattern_count = self.pure_search(m, n, pattern, text, lps, match_list, pattern_count)
		else:
			row_index = 0
			for row in text:
				m = len(row)
				match_list[row_index], pattern_count = self.pure_search(m, n, pattern, row, lps, match_list[row_index], pattern_count)
				row_index += 1
		
		end_t = datetime.now()
		print("Search finish: \t" + str(end_t))

		print_search_summary(pattern, pattern_count, match_list)

		search_t_ms = process_time_ms(start_t, end_t)
		print("Total runtime: " + str(search_t_ms) + "ms")
		print("===FINISH KMP\n")
		return preprocess_t_ms, search_t_ms

class BMSearch():

	def __init__(self):
		self.preprocess_t_ms = []
		self.search_t_ms = []
		self.sorted_time_cols = []

	def get_name(self):
		return "BM"

	def get_complexity(self):
		return "O(m)"

	def preprocess(self, pattern, n):
		start_t = datetime.now()

		# Number of characters in UCS2 Unicode
		NO_OF_CHARS = 65536

		# Initialize all occurrence as -1 
		bad_char = [-1]*NO_OF_CHARS

		# Fill the actual value of last occurrence for i in range(0, n):
		for i in range(0, n):
			bad_char[ord(pattern[i])] = i

		end_t = datetime.now()
		preprocess_t_ms = process_time_ms(start_t, end_t)
		return bad_char, preprocess_t_ms

	def pure_search(self, m, n, pattern, text, bad_char, index_list, pattern_count):
		i = 0
		while i < m - n:
			skip = 0
			for j in range(n-1, -1, -1):
				if pattern[j] != text[i+j]:
					skip = max(1, j - bad_char[ord(text[i+j])])
					break
			if (skip == 0):
				index_list.append(i)
				pattern_count += 1
				skip += 1
			i += skip
		return index_list, pattern_count

	def search(self, pattern, text):
		print("===START BM")
		n, m, match_list, pattern_count = init_search(pattern, text)

		bad_char, preprocess_t_ms = self.preprocess(pattern, n)

		start_t = datetime.now()
		print("Search start: \t" + str(start_t))
		
		if READ_FILE_BY_ROW == False:
			match_list, pattern_count = self.pure_search(m, n, pattern, text, bad_char, match_list, pattern_count)
		else:
			row_index = 0
			for row in text:
				m = len(row)
				match_list[row_index], pattern_count = self.pure_search(m, n, pattern, row, bad_char, match_list[row_index], pattern_count)
				row_index += 1

		end_t = datetime.now()
		print("Search finish: \t" + str(end_t)) 

		print_search_summary(pattern, pattern_count, match_list)

		search_t_ms = process_time_ms(start_t, end_t)
		print("Total runtime: " + str(search_t_ms) + "ms")
		print("===FINISH BM\n")
		return preprocess_t_ms, search_t_ms


def benchmark_algorithms(algorithms, pattern, text):
	for alg in algorithms:
		preprocess_t_ms, search_t_ms = alg.search(pattern, text)
		alg.preprocess_t_ms.append(preprocess_t_ms)
		alg.search_t_ms.append(search_t_ms)

def benchmark_algorithms_n_times(algorithms, n, pattern, text):
	# Run the benchmark n times
	for _ in range(0, n):
		benchmark_algorithms(algorithms, pattern, text)

def main():
	pattern = "16000"
	
	if READ_FILE_BY_ROW == True:
		with open('input_data/data_1_00-11-41-715014_50000_rows.csv', 'r') as csv_file:
			text = csv_file.readlines()
	else:
		with open('data/input-elem-algo.txt', 'r') as file:
			text = file.read()	
	
	algorithms = [ElementarySearch(), KMPSearch(), BMSearch()]

	benchmark_algorithms_n_times(algorithms, ITERATIONS, pattern, text)
	csv_summary.create_summary_csv("summary.csv", algorithms)

	print("Number of iterations: " + str(ITERATIONS))

if __name__== "__main__" :
	main()
