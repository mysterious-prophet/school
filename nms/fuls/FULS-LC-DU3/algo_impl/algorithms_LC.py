import sys # For the input file as an argument when launching the script
from pathlib import Path # For path operations

# Custom local file imports
from algo_settings import READ_FILE_BY_ROW, DEC_ACCURACY, ITERATIONS, PRINT_MATCH_INFO, EXPORT_INDIVIDUAL_RUNS
import csv_summary
from Elem_algo_impl_class import ElementarySearch
from KMP_algo_impl_class import KMPSearch
from BM_algo_impl_class import BMSearch
from AC_algo_impl_class import ACSearch
from CW_algo_impl_class import CWSearch

#################### SETUP:

# Path to the data file:
DATA_PATH = Path('input_data/data_1_15-27-25-885789_50000_rows.csv')
#DATA_PATH = Path('input_data/orig_input_data/input-algos-short.csv')
# If there is an argument given when the script is launched, get the input
if len(sys.argv) == 2:
	DATA_PATH = Path(sys.argv[1])

#################### END OF SETUP

# Benchmark given search algorithms on a given pattern and text
# Save results to each class's respective time arrays
def benchmark_algorithms(algorithms, text, pattern):
	for alg in algorithms:
		preprocess_t_ms, search_t_ms = alg.search(text, pattern)
		alg.preprocess_t_ms.append(preprocess_t_ms)
		alg.search_t_ms.append(search_t_ms)

# Benchmark given search algorithms on a given pattern and text "iteration" times
def benchmark_algorithms_n_times(algorithms, iterations, text, pattern):
	print("==================================================")
	print("Benchmark:")
	print("==================================================")
	# Run the benchmark n times
	for _ in range(0, iterations):
		benchmark_algorithms(algorithms, text, pattern)

# Print the benchmark configuration
def print_benchmark_configuration():
	print("==================================================")
	print("Program Configuration:")
	print("==================================================")
	print("Data file path: " + str(DATA_PATH))
	print("Read file by row: " +  "Enabled" if READ_FILE_BY_ROW == True else "Disabled")
	print("Number of benchmark iterations: " + str(ITERATIONS))
	print("Accuracy of [ms] decimals: " + str(DEC_ACCURACY))
	print("Print debug info {Match indexes; Matches count}: {" + ("Enabled" \
		  if PRINT_MATCH_INFO["Matches found"] == True else "Disabled") + "; " + ("Enabled" \
		  if PRINT_MATCH_INFO["Pattern count"] == True else "Disabled") + "}")
	print("Export individual run times into the output csv: " + "Enabled" if EXPORT_INDIVIDUAL_RUNS == True else "Disabled")
	print("\n * Configuration can be changed in the algo_settings.py file")

def main():
	if not DATA_PATH.is_file():
		print("The supplied data file does not exist.\nExiting...")
		exit()
	
	file_size = round(DATA_PATH.stat().st_size/1000000, 2)

	# Search for this pattern
	pattern = "sit"
	
	# In the following file:
	# -> Reading files by row is by default set to csv files.
	if READ_FILE_BY_ROW == True:
		with open(DATA_PATH, 'r') as csv_file:
			text = csv_file.readlines()
	else:
		with open(DATA_PATH, 'r') as file:
			text = file.read()

	# Declare which algorithms are to be benchmarked
	algorithms = [ElementarySearch(), KMPSearch(), BMSearch(), ACSearch(), CWSearch()]

	# Benchmark the algorithms n times
	benchmark_algorithms_n_times(algorithms, ITERATIONS, text, pattern)

	# Create a summarizing csv of preprocess, search times, etc.
	csv_summary.create_summary_csv("benchmark_summary_table.csv", file_size, algorithms, EXPORT_INDIVIDUAL_RUNS)

	print_benchmark_configuration()

# Launch the program using the following syntax (Python 3.9.0 compatible):
# -> The following will use the default data path ('input_data/data_1_15-27-25-885789_50000_rows.csv'):
#		py algorithms_LC.py
# -> The following will use the input as a data path:
# 		py algorithms_LC.py 'input_data/data_1_15-27-25-885789_50000_rows.csv'
if __name__== "__main__" :
	main()
