#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float balance;
    do
    {
        balance = get_float("Change owed: ");
    }
    while (balance < 0);
    int base = round(balance * 100);
    int finalchange;
    // basically greedy method, hours of trial and error
    { 
        int change25 = (base / 25); // the amount of 25 coins used
        int balance25 = (base % 25); // the balance after 25 coins used
        int change10 = (balance25 / 10); // the amount of 10 coins used
        int balance10 = (balance25 % 10); // the balance after 10 coins used
        int change5 = (balance10 / 5); // the amount of 5 coins used
        int balance5 = (balance10 % 5); // the balance after 5 coins used
        int change1 = (balance5 / 1); // the amount of 1 coins used
        finalchange = (change25 + change10 + change5 + change1);
    } // the above in order matters, from biggest first then to lowest
    printf("%i\n", finalchange);
}
