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

# Custom local file imports
from utils import list_to_str, get_byte_size



#################### SETUP:

# Default number of CSV files to be generated
NUM_CSV_FILES = 1

# File size in MB
FILE_SIZE_MB = 100
# File size in B
FILE_SIZE_B = FILE_SIZE_MB * 1024.0 * 1024.0

# Number of characters in Lorem Ipsum column
NUM_LOREM_CHARS = 256

# Random number of characters in Lorem Ipsum column allowed
RAND_LOREM_SIZE = False

#################### END OF SETUP



# If there is an argument given when the script is launched, get the input
if len(sys.argv) == 2:
	NUM_CSV_FILES = int(sys.argv[ 1 ])

# Directory into which the files will be generated
data_dir = os.getcwd() + "/../input_data" # cwd := current working direcrtory

# Initialize colors for console output
# https://www.devdungeon.com/content/colorize-terminal-output-python
colorama.init()



def make_data_dir(data_dir):
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


def shorten_row(row, desired_size_bytes):
	if isinstance(row, list):
		str_row = list_to_str(row)

	for i in range(len(str_row) - 1, 0, -1):
		str_size = get_byte_size(str_row)
		if str_size <= desired_size_bytes:
			break
		if str_row[i] == ";":
			continue
		str_row = str_row[:i] + str_row[i+1:]
	
	return str_row.split(';')


# Generate num_csv_files of csv files, each with num_rows rows
def generate_csv_files(num_csv_files):
	for id in range(num_csv_files):

		# File name for csv file 23, generated as date & time 'dt' and 50000 rows will be 'data_23_dt_50000_row.csv'
		file_name = "data_" + str(id + 1) + "_" + str(datetime.now().time().strftime('%H-%M-%S-%f') + "_") + str(FILE_SIZE_MB) + "_MB" + ".csv"
		file_dir = data_dir + "/" + file_name

		with open(file_dir, 'w', newline='', encoding='utf-8') as csv_file:
			writer = csv.writer(csv_file, delimiter=';')
			writer.writerow(get_header())
			curr_file_size_b = os.path.getsize(file_dir)
			# Row id counter
			i = 1
			while(curr_file_size_b < FILE_SIZE_B):
				rand_row = get_rand_row(i)
				# Get how many more bytes to write to file
				size_diff_bytes = FILE_SIZE_B - curr_file_size_b
				# If the current row (in bytes) is longer than the bytes required to get to FILE_SIZE_B
				if get_byte_size(list_to_str(rand_row)) > size_diff_bytes:
					# Shorten the row to size_diff_bytes bytes (counting the ';' in the resulting file)
					rand_row = shorten_row(rand_row, size_diff_bytes)
				# Write the row
				writer.writerow(rand_row)
				curr_file_size_b = os.path.getsize(file_dir)
				i += 1

		print(f' {Fore.GREEN}[ CREATED ]{Style.RESET_ALL} ' + data_dir + "/" + file_name)


def get_header():
	header = ["id", "label", "lat", "lon"]
	return header


# Generate a paragraph of lorem ipsum, but cut it at length num_chars (can be random if RAND_LOREM_SIZE is set to 'True')
def get_rand_lorem_ipsum(num_chars):
	if RAND_LOREM_SIZE == True:
		num_chars = random.randint(1, num_chars)
	lorips = lorem.paragraph()[0:num_chars]
	return lorips


def get_rand_coords():
	# Bounding box of CZE:
	#  https://wiki.openstreetmap.org/wiki/Czech_Republic
	#  (12.09,48.55,18.87,51.06)
	#  (min_lat, min_long, max_lat, max_long)
	return uniform(48.55, 51.06), uniform(12.09, 18.87)


# Generate a random row: id of row; random lorem ipsum string of num_lorem_chars chars; random longitutde; random latitude
def get_rand_row(row_id):
	return [row_id, get_rand_lorem_ipsum(NUM_LOREM_CHARS), get_rand_coords()[0], get_rand_coords()[1]]


def main():
	
	make_data_dir(data_dir)

	generate_csv_files(NUM_CSV_FILES)

	print(f'\n {Fore.GREEN}[ SUCCESS ]{Style.RESET_ALL} All files created in: ' + data_dir)


if __name__== "__main__" :
	main()