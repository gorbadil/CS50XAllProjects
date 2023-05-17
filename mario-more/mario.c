#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get Height of this thing between 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // Build this thing
    for (int line = 1; line <= height; line++)
    {
        for (int space = height - line; space > 0; space--)
        {
            printf(" ");
        }
        for (int hash = line; hash > 0; hash--)
        {
            printf("#");
        }
        printf("  ");
        for (int hash = line; hash > 0; hash--)
        {
            printf("#");
        }
        // for (int space = height - line; space > 0; space --)
        // {
        //     printf(" ");
        // }
        printf("\n");
    }
}