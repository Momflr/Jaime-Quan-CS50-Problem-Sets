#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // prompt for credit card DONE
    long cc;
    int sum1 = 0;
    int sum2 = 0;
    int i = 0;
    int double_digit = 0;
    do
    {
        cc = get_long("insert credit card number: ");
    }
    while (cc < 0);
    long times = cc;
    // calculate checksum
    do
    {
        sum1 = sum1 + (times % 10);
        times = times / 10;
        i++;
        if ((2 * (times % 10) < 10))
        {
            sum2 = sum2 + (2 * (times % 10));
        }
        else
        {
            double_digit = 2 * (times % 10);
            sum2 = sum2 + (double_digit % 10);
            double_digit = double_digit / 10;
            sum2 = sum2 + double_digit;
        }
        if (times > 0)
        {
            i++;
            times = times / 10;
        }
    }
    while (times > 0);
    sum1 = sum1 + sum2;

    // check for card length and starting digits, print

    int start = cc / 1000000000000;
    int mc14 = start / 10;
    int mc15 = start / 100;
    int vchecksum = sum1 % 10;

    // printf("start %i, i %i, mc14 %i, mc15 %i, vchecksum %i\n", start, i, mc14, mc15, vchecksum);

    if (vchecksum != 0)
    {
        printf("INVALID\n");
    }
    else
    {

        if ((start == 4 || start / 10 == 4 || start / 100 == 4 || start / 1000 == 4) && (i == 13 || i == 16))
        {
            printf("VISA\n");
        }
        else if ((i == 15) && (mc14 == 34 || mc14 == 37))
        {
            printf("AMEX\n");
        }
        else if ((i == 16) && (mc15 == 51 || mc15 == 52 || mc15 == 53 || mc15 == 54 || mc15 == 55))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
