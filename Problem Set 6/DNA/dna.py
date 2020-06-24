from sys import argv, exit
import csv
import re


# Read documentations on Python syntax
# Credits to python.org, stack overflow, programiz, kite, literally the internet.

def main():
    while True:
        argc = len(argv)  # Get the number of arguments, similar to argc in C
        if argc < 3 or argc > 3:  # If arguments are less than 3 or more than 3, print error message
            print("Usage: python dna.py CSVfile Textfile")
            break
        else:
            break  # If condition is met, break the while True loop
        
    with open(argv[1]) as csvfile:  # Open argv1, the csv file, notice the With
        database = csv.DictReader(csvfile)  # Use Dict.Reader to "read" the csv file into a Ordered Dict
        text = open(argv[2])  # Open argv2, the text file
        sequence = text.read()  # Open text with f.read()
        data = {}  # Create a dict to store data from text file
        data['AGATC'] = agatc(sequence)  # Custom functions to get the longest repeating STRs
        data['TTTTTTCT'] = ttttttct(sequence)
        data['AATG'] = aatg(sequence)
        data['TCTAG'] = tctag(sequence)
        data['GATA'] = gata(sequence)
        data['TATC'] = tatc(sequence)
        data['GAAA'] = gaaa(sequence)
        data['TCTG'] = tctg(sequence)
        for row in database:  # Iterate through database(CSVfile) by row
            length = len(row) - 1  # Get the number of STRs to be checked, - 1 to not include 'name'
            match = 0  # Match counter to be compared to length
            name = ''  # Empty string
            if 'AGATC' in row:  # If STR name is in row
                if data.get('AGATC') == int(row['AGATC']):  # If STR count similar to STR count in text(row)
                    match += 1  # Update match counter
            if 'TTTTTTCT' in row:
                if data.get('TTTTTTCT') == int(row['TTTTTTCT']):
                    match += 1
            if 'AATG' in row:
                if data.get('AATG') == int(row['AATG']):
                    match += 1
            if 'TCTAG' in row:
                if data.get('TCTAG') == int(row['TCTAG']):
                    match += 1
            if 'GATA' in row:
                if data.get('GATA') == int(row['GATA']):
                    match += 1
            if 'TATC' in row:
                if data.get('TATC') == int(row['TATC']):
                    match += 1
            if 'GAAA' in row:
                if data.get('GAAA') == int(row['GAAA']):
                    match += 1
            if 'TCTG' in row:
                if data.get('TCTG') == int(row['TCTG']):
                    match += 1
            if match == length:  # If matches all STR counts
                print(row['name'])  # Print name
                exit(1)
        print("No match")  # Else, not in the database
        

def agatc(sequence):  # Custom functions
    counter = 0  # Counter for longest repetitions of STRs
    highest = 0  # Update the longest, to be returned later
    i = 0  # Seek function
    while True:
        AGATC = sequence[i:i+5]
        if AGATC == "AGATC" and i != len(sequence):
            counter += 1
            i += 5
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def ttttttct(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        TTTTTTCT = sequence[i:i+8]
        if TTTTTTCT == "TTTTTTCT" and i != len(sequence):
            counter += 1
            i += 8
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def aatg(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        AATG = sequence[i:i+4]
        if AATG == "AATG" and i != len(sequence):
            counter += 1
            i += 4
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def tctag(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        TCTAG = sequence[i:i+5]
        if TCTAG == "TCTAG" and i != len(sequence):
            counter += 1
            i += 5
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def gata(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        GATA = sequence[i:i+4]
        if GATA == "GATA" and i != len(sequence):
            counter += 1
            i += 4
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def tatc(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        TATC = sequence[i:i+4]
        if TATC == "TATC" and i != len(sequence):
            counter += 1
            i += 4
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def gaaa(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        GAAA = sequence[i:i+4]
        if GAAA == "GAAA" and i != len(sequence):
            counter += 1
            i += 4
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


def tctg(sequence):
    counter = 0
    highest = 0
    i = 0
    while True:
        TCTG = sequence[i:i+4]
        if TCTG == "TCTG" and i != len(sequence):
            counter += 1
            i += 4
        elif i >= len(sequence):
            break
        else:
            if counter > highest and i != len(sequence):
                highest = counter
                counter = 0
                i += 1
            else:
                counter = 0
                i += 1
    return highest


main()