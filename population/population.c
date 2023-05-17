#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startPop;
    do
    {
        startPop = get_int("Type your starting population: ");
    }
    while (startPop < 9);
    // TODO: Prompt for end size
    int endPop;
    do
    {
        endPop = get_int("Type your goal: ");
    }
    while (endPop < startPop);

    // TODO: Calculate number of years until we reach threshold
    int n, death, born;
    n = 0;
    while (startPop < endPop)
    {
        death = startPop / 4;
        born = startPop / 3;
        startPop = startPop + born - death;
        n++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", n);
}
