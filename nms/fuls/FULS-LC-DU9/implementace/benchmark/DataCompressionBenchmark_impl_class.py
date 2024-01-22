from datetime import datetime # For measuring preprocessing and search times
import os # For path operations
import yaml # For settings import
settings = yaml.safe_load(open("settings/settings.yml"))

# Custom local file imports
from benchmark.Benchmark_base_class import Benchmark
from data_generator.utils import get_byte_size
from benchmark.csv_summary import create_summary_csv



class AlgorithmData:
	def __init__(self, algo_name, is_output_in_bits):
		"Initialize data container for a given algorithm"
		self.name = algo_name
		self.compression_ratios = []
		self.compression_times = []
		self.is_output_in_bits = is_output_in_bits
		self.orig_text_size_bytes = None
		self.encoded_text_size_bytes = None

	
	def print(self):
		print([self.name, self.compression_ratios, self.compression_times, \
			   self.is_output_in_bits, self.orig_text_size_bytes, self.encoded_text_size_bytes])
		

	def print_nice(self):
		print("{{Algorithm: {},\t Compression ratio(s) [%]: {},\t Compression time(s) [ms]: {},\t Output in bits: {},\t Input text size [B]: {},\t Encoded text size [B]: {}}}".\
			   format(self.name, self.compression_ratios, self.compression_times, \
			          self.is_output_in_bits, self.orig_text_size_bytes, self.encoded_text_size_bytes))



class DataCompressionBenchmark(Benchmark):
	def __init__(self, input_file_path, algorithms):
		"Initialize the benchmark instance"
		super().__init__("Data Compression Benchmark")
		self.input_file_name = input_file_path.name
		self.text = self.load_file(input_file_path)
		self.input_file_size = os.path.getsize(input_file_path)
		self.algorithms = algorithms
		self.create_algo_dict()
		

	def load_file(self, data_path):
		"Load the text from a given file"
		if not data_path.is_file():
			print("The supplied data file does not exist.\nExiting...")
			exit()

		with open(data_path, 'r') as file:
			text = file.read()
		return text
	

	def create_algo_dict(self):
		"Create a dictionary of benchmark records for each algorithm"
		self.algorithms_data = {}
		for alg in self.algorithms:
			self.algorithms_data[alg.get_name()] = AlgorithmData(alg.get_name(), alg.encoded_text_in_bits)


	def parse_arguments(self, algorithms, text):
		"Dummy function that sets members of this class as deafult arguments"
		if algorithms is None:
			algorithms = self.algorithms
		if text is None:
			text = self.text
		return algorithms, text


	def record_encoding_results(self, alg, encoded_text, time_ms):
		"Record run results"
		alg_data = self.algorithms_data[alg.get_name()]
		alg_data.compression_ratios.append(alg.get_compression_ratio(self.text, encoded_text))
		alg_data.compression_times.append(time_ms)
		alg_data.orig_text_size_bytes = self.input_file_size
		if alg_data.is_output_in_bits == False:
			encoded_text_size = get_byte_size(encoded_text)
		else:
			encoded_text_size = len(encoded_text) / 8.0
		alg_data.encoded_text_size_bytes = encoded_text_size


	def run_algorithms(self, algorithms = None, text = None, iteration = 1):
		"Run the given compression algorithms on a given text"
		algorithms, text = self.parse_arguments(algorithms, text)
		
		for alg in algorithms:
			print("\n{} compression:".format(alg.get_name()))

			start_t = datetime.now()
			encoded_text = alg.encode(text)
			end_t = datetime.now()

			
			start_t_decode = datetime.now()
			decoded_text = alg.decode(encoded_text)
			end_t_decode = datetime.now()

			if settings["PRINT_INFO"]:
				print("Original text: \"{}\"".format(text))
				print("Encoded text: \"{}\"".format(encoded_text))
				print("Decoded text: \"{}\"".format(decoded_text))
			if text == ''.join(decoded_text):
				self.record_encoding_results(alg, encoded_text, self.process_time_ms(start_t, end_t))
				print("SUCCESS! Original file and decoded file match!")
				print("Encode time [ms]: {}".format(self.process_time_ms(start_t, end_t)))
				print("Decode time [ms]: {}".format(self.process_time_ms(start_t_decode, end_t_decode)))
				if settings["DEBUG"]:
					print("Compression ratio (% of original file size [in bits]) = {:03.2f}".format(alg.get_compression_ratio(text, encoded_text)))
		

	def run_benchmark(self, iterations = settings["NUM_ITERATIONS"]):
		"Run the benchmark a given number of times"
		print("\n=== RUNNING BENCHMARK ===")
		for i in range(0, iterations):
			print(f"\n== Iteration {i} ==")
			self.run_algorithms(iteration = i)


	def print_results(self):
		"Print results of the benchmark"
		print("\n=== BENCHMARK RESULTS SUMMARY ===")
		for algo_data in self.algorithms_data.values():
			algo_data.print()
	
	def print_nice_results(self):
		"Print nicely formatted results of the benchmark"
		print("\n=== BENCHMARK RESULTS SUMMARY ===")
		for algo_data in self.algorithms_data.values():
			algo_data.print_nice()


	def save_results(self):
		"Save the results of the benchmark to a CSV file"
		print("\n=== SAVING RESULTS ===")
		file_name = "benchmark_summary_table-{}-{}.csv".format(str(datetime.now().time().strftime('%H-%M-%S-%f')), \
															   str(self.input_file_name).split(".", 1)[0])
		create_summary_csv(file_name, list(self.algorithms_data.values()), time_in_seconds = True, file_size_units = "MB")
	

	def get_algo_data(self):
		"Return the algorithm data dictionary as a list of lists"
		return list(self.algorithms_data.values())