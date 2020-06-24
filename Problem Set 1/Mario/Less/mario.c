#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        // The number of # is conditioned by the row
        // Row 1 has 1 hash, row 2 has 2 hash
        // Logically, j is conditioned by i
        // j < i, as i increases so does j
        for (int j = 1; j < n - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
        // spent hours of problem solving
        // created another for loop for hash
        // one loop is for the spaces
        // trial and error of condition formula 
        // for loop for space first
        // for loop for hash 
        // the order of for loop matters
        // because c reads from top to bottom left to right
    }
        
}
