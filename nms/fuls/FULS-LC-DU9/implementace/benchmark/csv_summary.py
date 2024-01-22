import csv  # For writing into CSV files
import os # For file operations
import yaml # For settings import
settings = yaml.safe_load(open("settings/settings.yml"))



def make_data_dir(data_dir):
	"Make a data directory according the the working directory, if it doesn't already exist"
	# Check if the directory, where the script will create the csv files, exists:
		# If it doesn't -> create it
		# If it does -> say it does
	# https://stackabuse.com/creating-and-deleting-directories-with-python/
	# https://tecadmin.net/python-check-file-directory-exists/
	if not os.path.exists(data_dir):
		os.mkdir(data_dir)
		print(f' [ SUCCESS ] DIR created.')
	else:
		print(f' [ SUCCESS ] DIR exists.')
	print(f"\t{data_dir}\n")


def get_header(num_runs, save_individual_runs, time_in_seconds, file_size_units):
	"Create header of the CSV as an array"
	time_units = "[s]" if time_in_seconds == True else "[ms]"
	size_units = "[{}]".format(file_size_units)

	header = ["Algorithm"]
	if save_individual_runs == True:
		for i in range(0, num_runs):
			header.append("Run {} compression ratio {}".format(str(i+1), "[%]"))
			header.append("Run {} compression time {}".format(str(i+1), time_units))
	header.append("Avg. compression ratio {}".format("[%]"))
	header.append("Avg. compression time {}".format(time_units))
	header.append("Input file size {}".format(size_units))
	header.append("Encoded file size {}".format(size_units))
	return header


def get_list_mean(lst, accuracy = settings["DEC_ACCURACY"]):
	"Get the mean of a list of numbers with a given accuracy"
	return round(sum(lst)/len(lst), accuracy)


def get_avg_time(times_ms):
	"Compute avg time when given an array of times in ms"
	return get_list_mean(times_ms)


def get_avg_compression_ratio(c_rates):
	"Compute avg compression ratios when given an array of compression ratios in %"
	return get_list_mean(c_rates)


def flatten_data_into_cols(alg_data, print_individual_runs, time_in_seconds, file_size_units, accuracy = settings["DEC_ACCURACY"]):
	"Flatten the benchmark results into a list of values for a given algorithm's benchmark data container"
	flat_data = []
	flat_data.append(alg_data.name)

	if time_in_seconds == True:
		alg_data.compression_times = [round(time/1000, accuracy) for time in alg_data.compression_times]
	if file_size_units == "MB":
		alg_data.orig_text_size_bytes = round(alg_data.orig_text_size_bytes / (1024.0*1024.0), accuracy)
		alg_data.encoded_text_size_bytes = round(alg_data.encoded_text_size_bytes / (1024.0*1024.0), accuracy)

	if print_individual_runs == True:
		for i in range(0, len(alg_data.compression_ratios)):
			flat_data.append(alg_data.compression_ratios[i])
			flat_data.append(alg_data.compression_times[i])

	flat_data.append(get_avg_compression_ratio(alg_data.compression_ratios))
	flat_data.append(get_avg_time(alg_data.compression_times))
	flat_data.append(alg_data.orig_text_size_bytes)
	flat_data.append(alg_data.encoded_text_size_bytes)
	return flat_data


def create_summary_csv(csv_name, algo_data_list, time_in_seconds, file_size_units, save_individual_runs = settings["SAVE_INDIVIDUAL_RUNS"]):
	"Create a csv of benchmark results of input algorithms' benchmark data containers"
	# Get number of runs by getting the length of the array of preprocessing times of an input algorithm
	num_runs = len(algo_data_list[0].compression_ratios)

	header = get_header(num_runs, save_individual_runs, time_in_seconds, file_size_units)

	# Change dir to write results into benchmark_results
	make_data_dir(os.getcwd() + "/benchmark_results")

	csv_name = "benchmark_results/" + csv_name

	with open(csv_name, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=';')
		writer.writerow(header)

		# For every algorithm create a new row that consists of:
		# 	Algorithm name; Algorithm compression ratios, run times: {run i preprocess time; run i search time; run i total time}; avg. times: {avg. preprocess time; avg. search time; avg. total time}
		# 	-> All times are in ms
		for alg_data in algo_data_list:
			row = flatten_data_into_cols(alg_data, save_individual_runs, time_in_seconds, file_size_units)
			writer.writerow(row)
