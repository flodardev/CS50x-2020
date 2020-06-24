from cs50 import get_float
from sys import exit

# Global Variables
# round function
# Learned from the internet, programiz.com and stack overflow
# Global Variable
counter = 0


def main():
    i = getchange()
    coins(i)


def getchange():  # Get input from user
    while True:  # Infinite loop unless a condition is met
        n = get_float("Change owed:")
        if n > 0.00:  # Condition is must be greater than 0, meaning positive numbers only
            break
    return n


def coins(n):  # Function for calculating the least amount of coins needed
    global counter
    if n > .25 or n == .25:
        while True:
            n = round(n - .25, 2)
            counter += 1
            if n < .25:
                break
    if n > .10 or n == .10:
        while True:
            n = round(n - .10, 2)
            counter += 1
            if n < .10:
                break
    if n > 0.05 or n == 0.05:
        while True:
            n = round(n - .05, 2)
            counter += 1
            if n < .5:
                break
    if n != 0.00:
        while True:
            n = round(n - .01, 2)
            counter += 1
            if n == 0.0:
                break
    print(counter)
    exit(1)


main()