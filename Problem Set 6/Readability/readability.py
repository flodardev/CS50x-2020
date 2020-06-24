from cs50 import get_string
import re


# regular expressions code is from geeksforgeeks.org
# isalpha() and isspace() syntax is from geeksforgeeks.org
# Google's Documentation on Python


def main():
    text = get_string("Text: ")
    grade(letters(text), words(text), sentences(text))


def letters(text):
    letter = len(re.findall(r'\w', text))
    return letter


def words(text):
    # From Google for Education
    # re.findall(what to find, where to find) is a regular expression to find in a set of strings
    # The 'r' at the start of the pattern string designates a python "raw" string which passes through backslashes without change.
    # \w matches a "word" character: a letter or digit or underbar [a-zA-Z0-9_]. Note that although "word" is the mnemonic for this, it only matches a single word char, not a whole word.
    # + -- 1 or more occurrences of the pattern to its left, e.g. 'i+' = one or more i's
    word = len(re.findall(r'\s', text))
    return word + 1


def sentences(text):
    sentence = len(re.findall(r'[\.\!\?]', text))
    return sentence


def grade(letter, word, sentence):
    L = (letter * 100) / word
    S = (sentence * 100) / word
    realgrade = round((0.0588 * L) - (0.296 * S) - 15.8)
    if realgrade < 1:
        print("Before Grade 1")
    elif realgrade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {realgrade}")


main()