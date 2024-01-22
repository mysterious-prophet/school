import csv
from operator import add
from datetime import datetime

from algo_settings import DEC_ACCURACY

# Generate a header with variable number of columns based on number of runs of benchmark
def get_header(num_runs, print_individual_runs):
	header = ["File size [MB]", "Algorithm", "Complexity"]
	if print_individual_runs == True:
		for i in range(0, num_runs):
			header.append("Run " + str(i+1) + " preprocess time [ms]")
			header.append("Run " + str(i+1) + " search time [ms]")
			header.append("Run " + str(i+1) + " total time [ms]")
	header.append("Avg. preprocess time [ms]")
	header.append("Avg. search time [ms]")
	header.append("Avg. total time [ms]")
	return header

# Compute avg time when given an array of times in ms
def get_avg_time(time_ms):
	return round(sum(time_ms)/len(time_ms), DEC_ACCURACY)

def sort_times_into_cols(algorithms, print_individual_runs):
	for alg in algorithms:
		if print_individual_runs == True:
			for i in range(0, len(alg.preprocess_t_ms)):
				# Alg's preprocess time for each run, unless Elementary, which will have "-"
				alg.sorted_time_cols.append(alg.preprocess_t_ms[i] if alg.get_name() != "Elementary" else "-")
				# Alg's search time for each run
				alg.sorted_time_cols.append(alg.search_t_ms[i])
				# Alg's total time for each run
				alg.sorted_time_cols.append(alg.preprocess_t_ms[i] + alg.search_t_ms[i])

		# Avg. preprocess time, round to 5 decimal places
		alg.sorted_time_cols.append( get_avg_time(alg.preprocess_t_ms) if alg.get_name() != "Elementary" else "-")
		# Avg. search time
		alg.sorted_time_cols.append( get_avg_time(alg.search_t_ms) )
		# Avg. total time
		alg.sorted_time_cols.append( get_avg_time(list( map(add, alg.preprocess_t_ms, alg.search_t_ms) )))

# Create a csv summarising the benchmark of input algorithms
def create_summary_csv(csv_name, file_size, algorithms, print_individual_runs):
	# Get number of runs by getting the length of the array of preprocessing times of an input algorithm
	num_runs = len(algorithms[0].preprocess_t_ms)

	header = get_header(num_runs, print_individual_runs)

	sort_times_into_cols(algorithms, print_individual_runs)

	with open(csv_name, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=';')
		writer.writerow(header)

		# For every algorithm create a new row that consists of:
		# 	Algorithm name; Algorithm complexity, run times: {run i preprocess time; run i search time; run i total time}; avg. times: {avg. preprocess time; avg. search time; avg. total time}
		# 	-> All times are in ms
		for alg in algorithms:
			alg_row = [file_size, alg.get_name(), alg.get_complexity()]
			for i in alg.sorted_time_cols:
				alg_row.append(i)
			writer.writerow(alg_row)
