#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Taking Card Number
    long cardnumber;
    do
    {
        cardnumber = get_long("Type your card number: \n");
    }
    while (cardnumber < 0);
    int multi[10], nonmulti[10];
    int j = 0;
    long mastertype = cardnumber;
    long visatype = cardnumber;
    long amextype = cardnumber;
    // Creating Array for calculation
    while (j < 10)
    {
        nonmulti[j] = cardnumber % 10;
        cardnumber = cardnumber / 10;
        multi[j] = cardnumber % 10;
        cardnumber = cardnumber / 10;
        j++;
    }
    int sum1, sum2, sum, sum1m, sum11, sum12;
    for (int sum1i = 0; sum1i < 10; sum1i++)
    {
        sum1m = multi[sum1i] * 2;
        sum11 = sum1m % 10;
        sum12 = (sum1m / 10) % 10;
        sum1 = sum1 + sum11 + sum12;
    }
    for (int sum2i = 0; sum2i < 10; sum2i++)
    {
        sum2 = sum2 + nonmulti[sum2i];
    }
    sum = sum1 + sum2;
    // Controling Card Type
    visatype = visatype / 100000000000;
    while (visatype >= 10)
    {
        visatype /= 10;
    }
    while (mastertype >= 100)
    {
        mastertype /=  100;
    }
    amextype = amextype / 10000000000000;
    // Answer to User
    if (sum % 10 == 0)
    {
        if (amextype == 34 || amextype == 37)
        {
            printf("AMEX\n");
        }
        else if (50 < mastertype && mastertype < 56)
        {
            printf("MASTERCARD\n");
        }
        else if (visatype == 4)
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