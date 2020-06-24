from cs50 import get_int


def main():
    i = get_height()
    pyramid(i)


def get_height():
    while True:  # Infinite loop unless a condition is met in the function
        n = get_int("Height: ")  # Get user's input
        if n < 9 and n > 0:  # In between 0 to 8 only. Condition to break the loop.
            break
    return n


def pyramid(n):
    for i in range(1, n + 1, 1):  # How many times. Initial value is 1, so upper limit add 1.
        for y in range(0, n - i, 1):  # Print white spaces for n - i times.
            print(" ", end="")  # End for continous white spaces.
        for x in range(0, i, 1):  # Print # for i times.
            print("#", end="")  # End for continous #.
        print("  ", end="")  # Double spaces in between the two half pyramids.
        for a in range(0, i, 1):  # Print # for i times.
            print("#", end="")  # End for continous # spaces.
        print("")  # New line
        
        
main()