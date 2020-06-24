from cs50 import get_int, get_string
from sys import exit


def main():
    # Custom functions
    credit = getcredit()
    creditid(digitcounter(luhn(credit), credit), credit)


# Get credit card number from user
def getcredit():
    while True:
        credit = get_int("Number: ")
        if credit > 1 and credit < 9999999999999999:
            break
    return credit


# Luhn's Algorithm
def luhn(n):
    s1 = 0  # Variable to store the sum of not multiplied digits from the last digit
    s2 = 0  # Variable to store the sum of every other multiplied digits starting from the 2nd to the last digit
    for i in range(0, 8, 1):
        s1 += int(n % 10)
        c = int((n / 10) % 10)
        c = c * 2
        if c > 9:
            c1 = (c % 10 + int(c / 10))
            s2 += c1
        else:
            s2 += c
        n = int(n / 100)
    if ((s1 + s2) % 10) == 0:
        return True
    else:
        print("INVALID")
        exit(1)


# Count the digit           
def digitcounter(x, y):
    counter = 0
    while True:
        y = int(y / 10)
        counter += 1
        if y == 0:
            if counter == 13 or 15 or 16:
                return counter
      
  
# Identify Credit Card Company     
def creditid(counter, credit):
    while True:
        credit = int(credit / 10)
        if credit < 100:
            break
    if credit in [40, 41, 42, 43, 44, 45, 46, 47, 48, 49] and counter in [16, 14]:
        print("VISA")
        exit(1)
    elif credit in [34, 37] and counter == 15:
        print("AMEX")
        exit(1)
    elif credit in [51, 52, 53, 54, 55] and counter == 16:
        print("MASTERCARD")
        exit(1)
            
            
main()