# Default accuracy that time in ms will be rounded to. Taken from csv_summary.py
DEC_ACCURACY = 3

# The input file with be read by row (delimited by '\n'). By default, the file that is to be read by row is a csv in the '/input_data' dir
READ_FILE_BY_ROW = True

# Number of times that each format will be run
ITERATIONS = 1

# Print the indexes at which a match was found and how many times the pattern was found
PRINT_MATCH_INFO = {"Matches found": False, "Pattern count" : True}

# Export individual run times into the output csv
EXPORT_INDIVIDUAL_RUNS = False

# Export times into table in seconds in the output csv
TIME_IN_SECONDS = True
