from datetime import datetime
import csv

DEC_ACCURACY = 3

def sort_times_into_cols(algorithms):
	for alg in algorithms:
		for i in range(0, len(alg.preprocess_t_ms)):
			# Alg's preprocess time for each run, unless Elementary, which will have "-"
			alg.sorted_time_cols.append(alg.preprocess_t_ms[i] if alg.get_name() != "Elementary" else "-")
			# Alg's search time for each run
			alg.sorted_time_cols.append(alg.search_t_ms[i])
			# Alg's total time for each run
			alg.sorted_time_cols.append(alg.preprocess_t_ms[i] + alg.search_t_ms[i])

		# Avg. preprocess time, round to 5 decimal places
		alg.sorted_time_cols.append( round(sum(alg.preprocess_t_ms)/len(alg.preprocess_t_ms), DEC_ACCURACY) if alg.get_name() != "Elementary" else "-")
		# Avg. search time
		alg.sorted_time_cols.append( round(sum(alg.search_t_ms)/len(alg.search_t_ms), DEC_ACCURACY) )
		# Avg. total time
		alg.sorted_time_cols.append( round((sum(alg.preprocess_t_ms)+sum(alg.search_t_ms))/len(alg.preprocess_t_ms), DEC_ACCURACY) )

def create_summary_csv(csv_name, algorithms):
	num_runs = len(algorithms[0].preprocess_t_ms)

	header = ["Algorithm", "Complexity"]
	for i in range(0, num_runs):
		header.append("Run " + str(i+1) + " preprocess time [ms]")
		header.append("Run " + str(i+1) + " search time [ms]")
		header.append("Run " + str(i+1) + " total time [ms]")
	header.append("Avg. preprocess time [ms]")
	header.append("Avg. search time [ms]")
	header.append("Avg. total time [ms]")

	sort_times_into_cols(algorithms)

	with open(csv_name, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=';')
		writer.writerow(header)
		for alg in algorithms:
			alg_row = [alg.get_name(), alg.get_complexity()]
			for i in alg.sorted_time_cols:
				alg_row.append(i)
			writer.writerow(alg_row)
