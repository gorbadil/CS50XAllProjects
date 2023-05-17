#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string answer = get_string("Type Here: ");
    int len = strlen(answer);
    for (int i = 0; i < len; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            print_bulb(((int)answer[i] / (int)powl(2, j)));
            answer[i] = answer[i] % (int)powl(2, j);
        }
        printf("\n");
    }
}
// 1 2 4 8 16 32 64 128
void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
