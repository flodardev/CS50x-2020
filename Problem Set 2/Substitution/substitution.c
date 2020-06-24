#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//variables
int counter = 0;//

int main(int argc, string argv[])
{
    // check if argument count is 2, if false return 1;
    if (argc == 2)
    {
        // check if cipher key is 26 characters
        if (strlen(argv[1]) == 26)
        {
            // check if cipher key is all alphabets only
            for (int i = 0; i < strlen(argv[1]); i++)
            {
                if (!isalpha(argv[1][i])) // if it's not alphabets
                {
                    return 1; // then return 1;
                }
            }
            // check for character repetitions
            for (int i = 0; i < strlen(argv[1]); i++) // the char to be compared
            {
                for (int j = 0; j < strlen(argv[1]); j++) // compares to all char of argv[1]
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        counter++; // if it's the same add 1 to counter, should be just 26.
                    }
                }
            }
            if (counter != strlen(argv[1]))
            {
                return 1;
            }
            // if it's all condtitions met then printf
            //printf("%s\n", argv[1]); // debugger

            //ask for plaintext
            string plaintext = get_string("plaintext:");
            printf("ciphertext:");
            //printf("%s", plaintext); // debugger
            //convert plaintext to ciphertext
            for (int i = 0; i < strlen(plaintext); i++)
            {
                for (int j = 0; j < 26; j++) //check which number of the alphabet, a to z is 26
                {
                    if (plaintext[i] == 'a' + j) //check if the screened letter of the plaintext is lowercase
                    {
                        if (islower(argv[1][j]))
                        {
                            printf("%c", argv[1][j]);
                        }
                        else
                        {
                            char lower = argv[1][j] + 32; // in the ascii table, upper to lower is +32
                            printf("%c", lower);
                        }
                    }
                    else if (plaintext[i] == 'A' + j) //check if the screened letter of the alphabet is uppercase
                    {
                        if (isupper(argv[1][j])) //if the j letter in argv[1] is uppercase too
                        {
                            printf("%c", argv[1][j]);
                        }
                        else
                        {
                            char upper = argv[1][j] - 32; // in the ascii table, lower to upper is -32
                            printf("%c", upper);
                        }
                    }
                }
                for (int k = 0; k < strlen(plaintext); k++) // anything that is not alphabets print it as it is.
                {
                    if (!isalpha(plaintext[i]))
                    {
                        printf("%c", plaintext[i]);
                        break;
                    }
                }
            }
            printf("\n");
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("2 Arguments Only, Not more not less.\n");
        return 1;
    }


}