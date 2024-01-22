import sys # For the input file as an argument when launching the script
import os # For path operations
import csv # For csv file operations
import colorama # Color formatting of text output to console
from colorama import Fore
from colorama import Style
from datetime import datetime # For file naming based on current time
import lorem # For Lorem Ipsum generation
import random
from random import uniform # For random latitude and longitude


#################### SETUP:

# Default number of CSV files to be generated
NUM_CSV_FILES = 1

# Number of rows per CSV files to be generated
NUM_ROWS = 50000

# Number of characters in Lorem Ipsum column
NUM_LOREM_CHARS = 256

# Random number of characters in Lorem Ipsum column allowed
RAND_LOREM_SIZE = False

#################### END OF SETUP


# If there is an argument given when the script is launched, get the input
if len(sys.argv) == 2:
	NUM_CSV_FILES = int(sys.argv[ 1 ])

# Directory into which the files will be generated
data_dir = os.getcwd() + "/../algo_impl/input_data" # cwd := current working direcrtory

# Initialize colors for console output
# https://www.devdungeon.com/content/colorize-terminal-output-python
colorama.init()

def make_data_dir():
	# Check if the directory, where the script will create the csv files, exists:
		# If it doesn't -> create it
		# If it does -> say it does
	# https://stackabuse.com/creating-and-deleting-directories-with-python/
	# https://tecadmin.net/python-check-file-directory-exists/
	if not os.path.exists(data_dir):
		os.mkdir(data_dir)
		print(f' {Fore.GREEN}[ SUCCESS ]{Style.RESET_ALL} DIR created.')
		print("\t" + data_dir + "\n")
	else:
		print(f' {Fore.GREEN}[ SUCCESS ]{Style.RESET_ALL} DIR exists.')
		print("\t" + data_dir + "\n")

def generate_csv_files(num_csv_files, num_rows):
	for id in range(num_csv_files):

		file_name = "data_" + str(id + 1) + "_" + str(datetime.now().time().strftime('%H-%M-%S-%f') + "_") + str(NUM_ROWS) + "_rows" + ".csv"
		file_dir = data_dir + "/" + file_name

		with open(file_dir, 'w', newline='') as csv_file:
			writer = csv.writer(csv_file, delimiter=';')
			writer.writerow(get_header(csv_file))
			for i in range(1, num_rows+1):
				writer.writerow(get_rand_row(i, NUM_LOREM_CHARS))

		print(f' {Fore.GREEN}[ CREATED ]{Style.RESET_ALL} ' + data_dir + "/" + file_name)

def get_header(file):
	header = ["id", "label", "lat", "lon"]
	return header

def get_rand_lorem_ipsum(num_chars):
	if RAND_LOREM_SIZE == True:
		num_chars = random.randint(1, num_chars)
	lorips = lorem.paragraph()[0:num_chars]
	return lorips

def get_rand_coords():
	# https://wiki.openstreetmap.org/wiki/Czech_Republic: (12.09,48.55,18.87,51.06)
	return uniform(48.55, 51.06), uniform(12.09, 18.87)

def get_rand_row(row_id, num_lorem_chars):
	return [row_id, get_rand_lorem_ipsum(num_lorem_chars), get_rand_coords()[0], get_rand_coords()[1]]

def main():
	make_data_dir()

	generate_csv_files(NUM_CSV_FILES, NUM_ROWS)

	print(f'\n {Fore.GREEN}[ SUCCESS ]{Style.RESET_ALL} All files created in: ' + data_dir)

if __name__== "__main__" :
	main()