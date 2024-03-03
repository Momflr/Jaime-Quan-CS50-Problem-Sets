#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;
            int rounded_average = average + 0.5;
            image[i][j].rgbtRed = rounded_average;
            image[i][j].rgbtBlue = rounded_average;
            image[i][j].rgbtGreen = rounded_average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            int temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = temp;
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = temp;
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {
            int adjacentblue = 0;
            int adjacentgreen = 0;
            int adjacentred = 0;
            float pixelschecked = 0;
            for (int adjrow = 0; adjrow < 3; adjrow++)
            {
                for (int adjcol = 0; adjcol < 3; adjcol++)
                {
                    if (!((i - 1 + adjrow) < 0 || (i - 1 + adjrow) > (height - 1)) &&
                        !((j - 1 + adjcol) < 0 || (j - 1 + adjcol) > (width - 1)))
                    {
                        adjacentblue += image[i - 1 + adjrow][j - 1 + adjcol].rgbtBlue;
                        adjacentgreen += image[i - 1 + adjrow][j - 1 + adjcol].rgbtGreen;
                        adjacentred += image[i - 1 + adjrow][j - 1 + adjcol].rgbtRed;
                        pixelschecked++;
                    }
                }
            }
            float avrblue = adjacentblue / pixelschecked;
            float avrgreen = adjacentgreen / pixelschecked;
            float avrred = adjacentred / pixelschecked;

            int roundedblue = avrblue + 0.5;
            int roundedgreen = avrgreen + 0.5;
            int roundedred = avrred + 0.5;

            temp[i][j].rgbtBlue = roundedblue;
            temp[i][j].rgbtGreen = roundedgreen;
            temp[i][j].rgbtRed = roundedred;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxcalculatorblue = 0;
            int gxcalculatorgreen = 0;
            int gxcalculatorred = 0;
            int gycalculatorblue = 0;
            int gycalculatorgreen = 0;
            int gycalculatorred = 0;

            for (int adjrow = -1; adjrow <= 1; adjrow++)
            {
                for (int adjcol = -1; adjcol <= 1; adjcol++)
                {
                    int row = i + adjrow;
                    int col = j + adjcol;

                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        gxcalculatorblue += image[row][col].rgbtBlue * gx[adjrow + 1][adjcol + 1];
                        gxcalculatorgreen += image[row][col].rgbtGreen * gx[adjrow + 1][adjcol + 1];
                        gxcalculatorred += image[row][col].rgbtRed * gx[adjrow + 1][adjcol + 1];

                        gycalculatorblue += image[row][col].rgbtBlue * gy[adjrow + 1][adjcol + 1];
                        gycalculatorgreen += image[row][col].rgbtGreen * gy[adjrow + 1][adjcol + 1];
                        gycalculatorred += image[row][col].rgbtRed * gy[adjrow + 1][adjcol + 1];
                    }
                }
            }

            int newBlue = round(
                sqrt(gxcalculatorblue * gxcalculatorblue + gycalculatorblue * gycalculatorblue));
            int newGreen = round(sqrt(gxcalculatorgreen * gxcalculatorgreen +
                                      gycalculatorgreen * gycalculatorgreen));
            int newRed =
                round(sqrt(gxcalculatorred * gxcalculatorred + gycalculatorred * gycalculatorred));

            // apply cap after sqrt
            temp[i][j].rgbtBlue = (newBlue > 255) ? 255 : newBlue;
            temp[i][j].rgbtGreen = (newGreen > 255) ? 255 : newGreen;
            temp[i][j].rgbtRed = (newRed > 255) ? 255 : newRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
