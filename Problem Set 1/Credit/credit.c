#include <stdio.h>
#include <cs50.h>
#include <math.h>

//variables
long credit; // original credit input
long credit2 = 0; // credit will be "added" not assigned to credit2, making 2 copies
int credit3;
long credit4 = 0;
int credit5;
int s1; // digits that were not multiplied starting from last digit
int s2; // digits that were multiplied starting from last other digit
long c1; //
long c2; //
int c_1;
int c_2;
int counter = 0; //it counts the number of digit

int main(void)
{
    do
    {
        //to prompt user' credit number
        credit = get_long("Number: ");
    }
    while (credit < 0 || credit > 9999999999999999);
    credit2 += credit;
    credit4 += credit;    
//Luhn's Algorithm
    {
        for (int i = 20; i > 0; i--)
        { 
            c1 = (credit % 10); //to get the last digit
            s1 += c1; //add last digit to s1(has non multiplied digits)
            c2 = (credit / 10); //remove last digit, to get 2nd last digit
            c2 = (c2 % 10); //get 2nd to the last digit
            c2 = (c2 * 2); //every other digit multiplied by 2

            if (c2 > 9) //putting 10 will not be accurate, 9 is more accurate
            {
                c_1 = (c2 % 10); //if digit multiplied has equals to 2 digits, separate them from last digit ane first digit
                c_2 = (c2 / 10); //
                s2 += (c_1 + c_2); // add together
            }
            else // just add into s2
            {
                s2 += c2; // s2 should be 22
            }
            credit = (credit / 100);
        }
        
        // to check the first two digits of credit
        //for AMEX and MASTERCARD
        do
        {
            credit2 = credit2 / 10;
        }
        while (credit2 > 100); 
        credit3 += credit2;
        // to check the first only digit of credit purpose for VISA     identification
        // also to check the number of digits, but it doesnt end at 0,it ends at the first digit, so minus1 to orginial number of digits, like visa supposed to be 16, but code it 15.
        do
        {
            credit4 = credit4 / 10;
            counter += +1;
        }
        while (credit4 > 10); 
        credit5 += credit4; 
        //to check if the sum of digits has zero as the last digit       
        s1 += s2;
        s1 = s1 % 10;
        // 0 in order for it to be valid 
    }
    if (s1 == 0 && credit5 == 4 && counter == 12)
    {
        printf("VISA\n");
    }
    else if (s1 == 0 && credit5 == 4 && counter == 15)
    {
        printf("VISA\n");
    }
    else if (s1 == 0 && credit3 == 34 && counter == 14)
    {
        printf("AMEX\n");
    }
    else if (s1 == 0 && credit3 == 37 && counter == 14)
    {
        printf("AMEX\n");
    } 
    else if (s1 == 0 && credit3 == 51 && counter == 15)
    {
        printf("MASTERCARD\n");
    }
    else if (s1 == 0 && credit3 == 52 && counter == 15)
    {
        printf("MASTERCARD\n");
    }
    else if (s1 == 0 && credit3 == 53 && counter == 15)
    {
        printf("MASTERCARD\n");
    }
    else if (s1 == 0 && credit3 == 54 && counter == 15)
    {
        printf("MASTERCARD\n");
    }
    else if (s1 == 0 && credit3 == 55 && counter == 15)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }       
}
// HARD. but FUN.
