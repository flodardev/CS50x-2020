#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int letter;
int word = 1; // assigned 1 to include the last word after the last space
int sentence;
float L; 
float S;
double grade;
int realgrade;

int main(void)
{
    string s = get_string("Text:"); //prompt user for text
    for (int i = 0, n = strlen(s); i < n; i++) //reminder for self, understand this part of the code
        if isalpha(s[i]) // to detect all letters
        {
            letter += 1;
        }
        else if isspace(s[i]) // spaces count as words
        {
            word += 1;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?') // to catch end sentences
        {
            sentence += 1;
        }

    L = ((letter * (float)100) / word); // should be divided with a float for a more accurate result
    S = ((sentence * (float)100) / word);
    grade = ((0.0588 * L) - (0.296 * S) - 15.8);   // the algorithm
    realgrade = round(grade);
    //printf("%f", grade);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", realgrade);
    }
}