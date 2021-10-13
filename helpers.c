#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE Blue = image[i][j].rgbtBlue;
            BYTE Green = image[i][j].rgbtGreen;
            BYTE Red = image[i][j].rgbtRed;

            BYTE average = round((Blue + Green + Red) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int last_pixel_in_row = width - 1;
    int last_row = height - 1;

    // from height[0] - height[399] a total of 400 pixels
    for (int i = 0; i < height; i++)
    {
        int n = last_pixel_in_row;
        // for width[j] - width[599] a total of 600 pixels
        for (int j = 0; j < round(width / 2.0); j++)
        {
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][n].rgbtBlue;
            image[i][j].rgbtGreen = image[i][n].rgbtGreen;
            image[i][j].rgbtRed = image[i][n].rgbtRed;

            image[i][n].rgbtBlue = blue;
            image[i][n].rgbtGreen = green;
            image[i][n].rgbtRed = red;

            n--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int last_pixel_in_row = width - 1;
    int last_row = height - 1;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Target Pixel
            BYTE blue = image[i][j].rgbtBlue;
            BYTE green = image[i][j].rgbtGreen;
            BYTE red = image[i][j].rgbtRed;

            if (image[0][0].rgbtBlue)
            {
                // Top Left Pixel
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_BR = image[i+1][j+1].rgbtBlue;
                BYTE green_BR = image[i+1][j+1].rgbtGreen;
                BYTE red_BR = image[i+1][j+1].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_BR + blue_B + blue) / 4;
                BYTE green_total_average = (green_R + green_BR + green_B + green) / 4;
                BYTE red_total_average = (red_R + red_BR + red_B + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;

            }
            else if(image[0][last_pixel_in_row].rgbtBlue)
            {
                // Top Right pixel
                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_BL = image[i+1][j-1].rgbtBlue;
                BYTE green_BL = image[i+1][j-1].rgbtGreen;
                BYTE red_BL = image[i+1][j-1].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_total_average = (blue_L + blue_BL + blue_B + blue) / 4;
                BYTE green_total_average = (green_L + green_BL + green_B + green) / 4;
                BYTE red_total_average = (red_L + red_BL + red_B + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if(image[last_row][last_pixel_in_row].rgbtBlue)
            {
                // Bottom Right Pixel
                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_total_average = (blue_L + blue_TL + blue_T + blue) / 4;
                BYTE green_total_average = (green_L + green_TL + green_T + green) / 4;
                BYTE red_total_average = (red_L + red_TL + red_T + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if (image[last_row][0].rgbtBlue)
            {
                // Bottom Left Pixel
                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_TR + blue_T + blue) / 4;
                BYTE green_total_average = (green_R + green_TR + green_T + green) / 4;
                BYTE red_total_average = (red_R + red_TR + red_T + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if (image[0][j].rgbtBlue)
            {
                // TOP ROW
                continue;
            }
            else if (image[last_row][j].rgbtBlue)
            {
                // BOTTOM ROW
                continue;
            }
            else if (image[j][0].rgbtBlue)
            {
                // FIRST COLUMN
                continue;
            }
            else if (image[j][last_pixel_in_row].rgbtBlue)
            {
                // LAST COLUMN
                continue;
            }
            else
            {
                // Left Pixel
                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                // Right Pixel
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                // Top left of target pixel
                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                // Top of target pixel
                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                // Top right of target pixel
                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                // Bottom left of target pixel
                BYTE blue_BL = image[i+1][j-1].rgbtBlue;
                BYTE green_BL = image[i+1][j-1].rgbtGreen;
                BYTE red_BL = image[i+1][j-1].rgbtRed;

                // Bottom of target pixel
                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                // Bottom right of target pixel
                BYTE blue_BR = image[i+1][j+1].rgbtBlue;
                BYTE green_BR = image[i+1][j+1].rgbtGreen;
                BYTE red_BR = image[i+1][j+1].rgbtRed;

                BYTE blue_total_average = round((blue + blue_TR + blue_T + blue_TL + blue_L + blue_R + blue_BL + blue_B + blue_BR) / 9.0);
                BYTE green_total_average = round((green + green_TL + green_T + green_TR + green_L + green_R + green_BL + green_B + green_BR) / 9.0);
                BYTE red_total_average = round((red + red_TL + red_T + red_TR + red_L + red_R + red_BL + red_B + red_BR) / 9.0);

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE Blue = image[i][j].rgbtBlue;
            BYTE Green = image[i][j].rgbtGreen;
            BYTE Red = image[i][j].rgbtRed;
        }
    }

    return;
}
