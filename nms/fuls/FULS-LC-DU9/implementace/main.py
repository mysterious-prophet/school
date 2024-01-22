import sys # For the input file as an argument when launching the script
from pathlib import Path # For path operations
import yaml # For settings import
settings = yaml.safe_load(open("settings/settings.yml"))

# Custom local file imports
from algo_impl.RLE_compress_impl_class import RLECompress
from algo_impl.SHF_compress_impl_class import SHFCompress
from algo_impl.HUFF_compress_impl_class import HUFFCompress
from algo_impl.FGK_compress_impl_class import FGKCompress
from algo_impl.VTTR_compress_impl_class import VTTRCompress
from algo_impl.LZ77_compress_impl_class import LZ77Compress
from algo_impl.LZ78_compress_impl_class import LZ78Compress
from benchmark.DataCompressionBenchmark_impl_class import DataCompressionBenchmark



#################### SETUP:

# Path to the data file:
#DATA_PATH = Path('input_data/RLE_input.txt')
#DATA_PATH = Path('input_data/input-elem-algo-short.txt')
#DATA_PATH = Path('input_data/data100.csv')
#DATA_PATH = Path('input_data/data_1_23-10-11-763245_100_MB.csv')
DATA_PATH = Path('input_data/data_1_21-51-34-196664_10_MB.csv')
#DATA_PATH = Path('input_data/data_1_21-51-30-509624_1_MB.csv')
#DATA_PATH = Path('input_data/data_1_21-50-05-386745_0.0001_MB.csv')

# If there is an argument given when the script is launched, get the input
if len(sys.argv) == 2:
	DATA_PATH = Path(sys.argv[1])

#################### END OF SETUP
# TODO: Fix imports, so they don't show up as errors in VSCode (https://realpython.com/python-import/)



def print_program_configuration():
	"Print the program configuration"
	print("\n==================================================")
	print("Program Configuration:")
	print("==================================================")
	print("Data file path: {}".format(DATA_PATH))
	print("Print the original, encoded and decoded text: {}".format("Enabled" if settings["PRINT_INFO"] == True else "Disabled"))
	print("Print the compression ratio: {}".format("Enabled" if settings["DEBUG"] == True else "Disabled"))
	print("Number of iterations in benchmark: {}".format(settings["NUM_ITERATIONS"]))
	print("Degrees of accuracy when rouning ms or %: {}".format(settings["DEC_ACCURACY"]))
	print("Print/Save individual runs of the benchmark: {}".\
		  format("Enabled" if settings["SAVE_INDIVIDUAL_RUNS"] == True else "Disabled"))
	print("Save the results of the benchmark into a CSV: {}".format("Enabled" if settings["SAVE_RESULTS"] == True else "Disabled"))
	print("\n * Configuration can be changed in the settings/settings.yml file")


def main():
	algorithms = [RLECompress(), SHFCompress(), HUFFCompress(), FGKCompress(), VTTRCompress(), LZ77Compress(), LZ78Compress()]
	benchmark = DataCompressionBenchmark(DATA_PATH, algorithms)
	benchmark.run_benchmark()
	benchmark.print_nice_results()

	if settings["SAVE_RESULTS"]:
		benchmark.save_results()

	print_program_configuration()


# Launch the program using the following syntax (Python 3.9.0 compatible):
# -> The following will use the default data path ('input_data/RLE_input.txt'):
#		py main.py
# -> The following will use the input as a data path:
# 		py main.py 'input_data/RLE_input.txt'
if __name__== "__main__" :
	main()
