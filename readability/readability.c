#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float letters(string text);
float words(string text);
float sentences(string text);

int main(void)
{
    // Get Text from User
    string text = get_string("Text: ");
    float l = letters(text);
    float w = words(text);
    float s = sentences(text);
    float L = (l / w) * 100;
    float S = (s / w) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int index1 = round(index);
    // printf("letters: %f\n", l);
    // printf("words: %f\n", w);
    // printf("sentences: %f\n", s);
    // Printing Result
    if (index1 > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index1 < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index1);
    }
}

float letters(string text)
{
    // Calculate how many letters
    int len = strlen(text);
    int value = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            value++;
        }
    }
    return value;
}

float words(string text)
{
    // Calculate how many words
    int len = strlen(text);
    int value = 1;
    for (int i = 0; i < len; i++)
    {
        if (isblank(text[i]))
        {
            value++;
        }
    }
    return value;
}

float sentences(string text)
{
    // Calculate how many senteces
    int len = strlen(text);
    int value = 0;
    for (int i = 0; i < len; i++)
    {
        if (ispunct(text[i]))
        {
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                value++;
            }
        }
    }
    return value;
}