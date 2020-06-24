#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// argc = the number of arguements, argv[] is an array, argv[0] = ./caesar and argv[1] is the user's command line arguement
int main(int argc, string argv[])
{
    // if there are two arguments, then proceed if not, return 1.
    if (argc == 2)
    {
        //argv[1] is cipher key
        // to check 2nd argument if is it a alphabet containing, return 1.
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
            if isalpha(argv[1][i])
            {
                return 1;
            }
        // if decimal, convert string to int
        int x = atoi(argv[1]); //atoi converts a string to its int value, assigning that int value to x
        // if argv[string], itll be coverted to 0, Aa-Zz will be 0. If its a decimal no. itll translate that value.
        // if decimal value is less than 0, return 1.
        if (x < 1)
        {
            return 1;
        }
        else if (x >= 1)
        {
            // key is ok. proceed to get plain text and conver to cipher text with key number.
            string plaintext = get_string("plaintext: ");
            for (int i = 0, n = strlen(plaintext); i < n; i++)
                if islower(plaintext[i])
                {
                    // wraparound 97 is a, a to z is 26
                    plaintext[i] = ((((plaintext[i] + x) - 97) % 26) + 97);
                }
                else if isupper(plaintext[i])
                {
                    plaintext[i] = ((((plaintext[i] + x) - 65) % 26) + 65);
                }
            printf("ciphertext:%s\n", plaintext);
            return 0;
        }
    }
    else
    {
        return 1;
    }
}