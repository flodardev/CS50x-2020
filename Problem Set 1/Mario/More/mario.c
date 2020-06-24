#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); // to set the lower limit and upper limit, and if outside of the limit re prompt the user
    for (int i = 0; i < n; i++) //for rows, dont have to change anything since rows = users input always
    {
        for (int j = 1; j < n - i; j++) // for each int, i need to create for each int
        {                              
            printf(" ");                // spaces for the right angled triangle
        }                               // if j(int = 0) is less than (user input)n - (rows)i print more j
        for (int k = 0; k < i + 1; k++) // condtionals are through trial and error
        {
            printf("#");
        }
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }
        for (int m = 0; m < i + 1; m++)
        {
            printf("#");
        }
        printf("\n");
    }  
}
