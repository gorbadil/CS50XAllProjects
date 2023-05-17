#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrg = 0;
            avrg += image[i][j].rgbtBlue;
            avrg += image[i][j].rgbtRed;
            avrg += image[i][j].rgbtGreen;
            avrg /= 3;
            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtRed = avrg;
            image[i][j].rgbtGreen = avrg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, oj = width - 1; j < width / 2; j++, oj--)
        {
            int tblue = image[i][j].rgbtBlue;
            int tred = image[i][j].rgbtRed;
            int tgreen = image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][oj].rgbtBlue;
            image[i][j].rgbtRed = image[i][oj].rgbtRed;
            image[i][j].rgbtGreen = image[i][oj].rgbtGreen;
            image[i][oj].rgbtBlue = tblue;
            image[i][oj].rgbtRed = tred;
            image[i][oj].rgbtGreen = tgreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int red, blue, green, redc, bluec, greenc;
    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            for (int bi = i - 1; bi <= i + 1; bi++)
            {
                if (bi > -1 && bi < height - 1)
                {
                    for (int bj = j - 1; bj <= j + 1; bj++)
                    {
                        if (bj > -1 && bj < width - 1)
                        {
                            red += image[bi][bj].rgbtRed;
                            redc++;
                            blue += image[bi][bj].rgbtBlue;
                            bluec++;
                            green += image[bi][bj].rgbtGreen;
                            greenc++;
                        }
                    }
                }
            }
            red = red / redc;
            blue = blue / bluec;
            green = green / greenc;
            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
            red = 0;
            blue = 0;
            green = 0;
            redc = 0;
            bluec = 0;
            greenc = 0;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    return;
}
