import cs50
import csv
import re
from sys import argv, exit


def main():
    
    # Link SQL to access the database
    db = cs50.SQL("sqlite:///students.db")

    # roster.py HOUSE
    # Check command line arguments
    while True:
        argc = len(argv)
        if argc != 2:
            print("Usage: roster.py HOUSE")
            exit(1)
        else:
            break
    
    # Query database for all students in house
    # Students should be sorted alphabetically by last name, then first name.
    database = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house = '{argv[1]}' ORDER BY last, first ASC")
    for row in database:
        # Print out each student's full name and birth year
        if row['middle'] != None:
            print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
        else:
            print(f"{row['first']} {row['last']}, born {row['birth']}")
    
    
main()