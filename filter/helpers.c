#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int cap255(int c);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    int i;
    int j;
    int g, b, r;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            g = image[i][j].rgbtGreen; // taken from bmp.h(rgbt)
            b = image[i][j].rgbtBlue;
            r = image[i][j].rgbtRed;

            avg = round((g + b + r) / 3.0);

            //avg = round(avg); // it should be integer so, we will just round it

            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {

            RGBTRIPLE a = image[i][j];

            // Apply provided formulas in pset description
            int sepiaRed = round(.393 * a.rgbtRed + .769 * a.rgbtGreen + .189 * a.rgbtBlue); // round because it is provided in pset descp
            int sepiaGreen = round(.349 * a.rgbtRed + .686 * a.rgbtGreen + .168 * a.rgbtBlue);
            int sepiaBlue = round(.272 * a.rgbtRed + .534 * a.rgbtGreen + .131 * a.rgbtBlue);

            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255; // as per pset cap at 255 if greater than 255
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed; // if not greater than 255 then assign whatever is
            }

            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255; // repeat for green and blue
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue = 255; // repeat for green and blue
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            image[i][j].rgbtBlue = sepiaBlue;


        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE preserve[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            preserve[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = preserve[width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = preserve[width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = preserve[width - 1 - j].rgbtBlue;
        }
    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /*RGBTRIPLE preserve[height][width];

    int count;
    float r;
    float g;
    float b;
    int c;
    int count1;
    int cc = 0;
    int i;
    int j;
    int a;
    int bb;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
             preserve[i][j] = image[i][j]; //then put this into the blurred image
        }
    }

    for (a = 0; a < height; a++)
    {
        for (bb = 0; bb < width; bb++)
        {
            c = 0;
            r = 0.00;
            g = 0.00;
            b = 0.00;

            for (count = -1; count < 2; count++)
            {
                for (count1 = -1; count1 < 2; count1++)
                {
                    if (((a + count) < 0) || ((a + count) >= height))
                    {
                        continue;

                    }

                    if (bb + count1 < 0 ||bb + count1 >= width)
                    {
                        continue;

                    }

                    r += preserve[a + count][bb + count1].rgbtRed;
                    g += preserve[a + count][bb + count1].rgbtGreen;
                    b += preserve[a + count][bb + count1].rgbtBlue;
                    cc++;
                }
            }

            image[a][bb].rgbtRed = (int)round(r / cc);
            image[a][bb].rgbtGreen = (int)round(g / cc);
            image[a][bb].rgbtBlue = (int)round(b / cc);
        }
    }



    //for (i = 0; i < height; i++)
    //{
    // for (j = 0; j < width; j++)
    // {
    //      image[i][j] = preserve[i][j]; //then put this into the blurred image
    //   }
   */

    RGBTRIPLE preserve[height][width];

    for (int y = 0; y < height; y++)
    {
        for (int t = 0; t < width; t++)
        {
            preserve[y][t] = image[y][t];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float r = 0;
            float g = 0;
            float b = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (((i + k) < 0) || ((i + k) >= height))
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (((j + l) < 0) || ((j + l) >= width))
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    r += preserve[i + k][j + l].rgbtRed;
                    g += preserve[i + k][j + l].rgbtGreen;
                    b += preserve[i + k][j + l].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int)round(r / count);
            image[i][j].rgbtGreen = (int)round(g / count);
            image[i][j].rgbtBlue = (int)round(b / count);
        }
    }
}

