#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); 
    // Asking the user for input.
    printf("Hello, %s\n", name);
    // The input, implemented.
}
