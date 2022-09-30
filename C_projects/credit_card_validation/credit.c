#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //get credit card input from user
    long card       = get_long_long("Number: ");
    //declare variables to use
    int oddEven     = 0, currentDigit = 0, sum1 = 0, sum2 = 0;
    long cardMem    = card;
    //using two variables (oddEven & currentDigit) to select between every other number
    //oddEven starts at 0 and is even, so this will be added into sum1
    //oddEven will increase by 1 each iteration
    //oddEven can also be used as the final credit card digit length
    //currentDigit will cycle through each digiit via modulus then dividing whole card number by 10
    while (card > 0)
    {
        currentDigit = card % 10;
        if (oddEven % 2 == 0) // if we land on digit place 0 2 4 6 8...
        {
            sum1 = sum1 + currentDigit;
        }
        if (oddEven % 2 != 0)
        {
            sum2 = sum2 + ((currentDigit * 2) / 10) + ((currentDigit * 2) % 10);
        }
        card = card / 10; //chop the card down 1 digit from the right
        oddEven++; // move onto the next odd or even number && count how many digits
    }
    int luhn        = (sum1 + sum2) % 10;       //final calculation of luhns algorithm
    int AMEXTest    = cardMem / powl(10, 13);   //check first two digits of AMEX
    int MCTest      = cardMem / powl(10, 14);   //check first two digits of AMEX
    int VISATest13  = cardMem / powl(10, 12);   //check first digit of AMEX with length 13
    int VISATest16  = cardMem / powl(10, 15);   //check first digit of AMEX with length 16
    if (luhn == 0)
    {
        if ((AMEXTest == 34 || AMEXTest == 37) && oddEven == 15)//AMEX
        {
            printf("AMEX\n");
        }
        else if ((MCTest >= 51 && MCTest <= 55) && oddEven == 16)//MASTERCARD
        {
            printf("MASTERCARD\n");
        }
        else if ((VISATest13 == 4 && oddEven == 13) || (VISATest16 == 4 && oddEven == 16))//VISA
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
