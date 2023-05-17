#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avrg = 0;
            int b = image[i][j].rgbtBlue;
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            float favrg = r + b + g;
            avrg = round(favrg / 3);
            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtRed = avrg;
            image[i][j].rgbtGreen = avrg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double b = image[i][j].rgbtBlue;
            double r = image[i][j].rgbtRed;
            double g = image[i][j].rgbtGreen;
            int sb = round(0.272 * r + 0.534 * g + 0.131 * b);
            int sr = round(0.393 * r + 0.769 * g + 0.189 * b);
            int sg = round(0.349 * r + 0.686 * g + 0.168 * b);
            if (sb > 255)
            {
                sb = 255;
            }
            if (sr > 255)
            {
                sr = 255;
            }
            if (sg > 255)
            {
                sg = 255;
            }
            image[i][j].rgbtBlue = sb;
            image[i][j].rgbtRed = sr;
            image[i][j].rgbtGreen = sg;
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
    RGBTRIPLE image_blur[height][width];
    double avgRed, avgGreen, avgBlue;
    float c;

    // cycle rows
    for (int i = 0; i < height; i++)
    {
        // cycle columns
        for (int j = 0; j < width; j++)
        {
            c = 0;
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;

            // cycle rows within 9 cell square
            for (int s = -1; s < 2; s++)
            {
                // cycle columns within 9 cell square
                for (int n = -1; n < 2; n++)
                {
                    // work only with cells that exist
                    int d = i + s;
                    int k = j + n;

                    if (d < height && k < width && d >= 0 && k >= 0)
                    {

                        avgRed = avgRed + image[d][k].rgbtRed;
                        avgGreen = avgGreen + image[d][k].rgbtGreen;
                        avgBlue = avgBlue + image[d][k].rgbtBlue;

                        // count existing cells within 9 cell square
                        c++;
                    }
                }
            }
            avgRed = round(avgRed / c);
            avgGreen = round(avgGreen / c);
            avgBlue = round(avgBlue / c);
            image_blur[i][j].rgbtRed = avgRed;
            image_blur[i][j].rgbtGreen = avgGreen;
            image_blur[i][j].rgbtBlue = avgBlue;

        }


    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blur[i][j];
        }
    }
    return;
}
