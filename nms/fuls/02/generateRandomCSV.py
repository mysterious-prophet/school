import sys
import os
import csv
import lorem
import random
from random import uniform
from datetime import datetime

num_files = 1
max_num_chars = 256
rand_num_chars = True

if len(sys.argv) > 1:
    num_files = int(sys.argv[1])

data_dir = os.getcwd() + "/../data"

def makeDataDir():
    if not os.path.exists(data_dir):
        os.mkdir(data_dir)
        print('DIR created.')
        print("\t" + data_dir + "\n")
    else:
        print('DIR exists.')
        print("\t" + data_dir + "\n")

def getHeader(file):
    header = ["id", "label", "lat", "lon"]
    return header

def genRandLoremIpsum(num_chars):
    if rand_num_chars == True:
        num_chars = random.randint(1, num_chars)
    lorem_ipsum = lorem.paragraph()[0:num_chars]
    return lorem_ipsum

def genRandCoords():
    return round(uniform(48.74, 51.00), 3), round(uniform(12.19, 18.76), 3)

def genRow(row_id, num_chars):
    return [row_id, genRandLoremIpsum(num_chars), genRandCoords()[0], genRandCoords()[1]]

def genCSVFile(num_files):

    filename = "data_100kb.csv" # + str(datetime.now().time().strftime('%H-%M-%S-%f')) + ".csv"
    filedir = "../data/" + filename

    with open(filedir, 'w', newline='') as csv_file:
        writer = csv.writer(csv_file, delimiter=';')
        writer.writerow(getHeader(csv_file))
        filesize = os.path.getsize(data_dir + '\\' + filename)
        row_id = 1
        while(filesize <= 100000):
            writer.writerow(genRow(row_id, max_num_chars))
            row_id += 1
            filesize = os.path.getsize(data_dir + '\\' + filename)
        print('[ CREATED ] ' + data_dir + "/" + filename)

def main():
    makeDataDir()
    genCSVFile(num_files)
    print('\n [ SUCCESS ] All files created in: ' + data_dir)

if __name__== "__main__" :
	main()



