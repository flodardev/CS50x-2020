import cs50
import csv
import re
from sys import argv, exit


# Linking SQL database
db = cs50.SQL("sqlite:///students.db")


# Check for the correct amount of Command Line Arguments
argc = len(argv)
if argc != 2:
    print("Usage: python import.py csvfile")
    exit(1)


# Open CSV file thats in the command line argument
with open(argv[1]) as database:
    reader = csv.DictReader(database)


# For each row parse name
# First Middle Last. If 2 strings present, assign middle name as None
    for row in reader:
        name = row['name'].split()  # Parses the name into list
        house = row['house']
        birth = row['birth']
        # Checking if name has a middle name
        string = len(re.findall(r'\s', row['name']))
        if string == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name[0], name[1], name[2], house, birth)
        else:
            name = row['name'].split()
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       name[0], None, name[1], house, birth)