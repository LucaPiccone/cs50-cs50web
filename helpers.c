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

            BYTE average = round((Blue + Green + Red) / 3);

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
    for (int i = 0; i < height; i++)
    {
        int n = width * 2;
        for (int j = 0; j < width; j++)
        {
            BYTE Blue = image[i][n].rgbtBlue;
            BYTE Green = image[i][n].rgbtGreen;
            BYTE Red = image[i][n].rgbtRed;

            image[i][j].rgbtBlue = Blue;
            image[i][j].rgbtGreen = Green;
            image[i][j].rgbtRed = Red;

            n--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
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
            else if(image[0][width].rgbtBlue)
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
            else if(image[height][width].rgbtBlue)
            {
                // Bottom Right Pixel
                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_total_average = (blue_L + blue_TL + blue_T + blue) / 4;

                BYTE green_total_average = (green_L + green_TL + green_T + green) / 4;

                BYTE red_total_average = (red_L + red_TL + red_T + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if (image[height][0].rgbtBlue)
            {
                // Bottom Left Pixel
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_TR + blue_T + blue) / 4;

                BYTE green_total_average = (green_R + green_TR + green_T + green) / 4;

                BYTE red_total_average = (red_R + red_TR + red_T + red) / 4;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if(image[0][i].rgbtBlue && !image[0][0].rgbtBlue && !image[0][width].rgbtBlue)
            {
                // Top Row Pixels
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_BL = image[i+1][j-1].rgbtBlue;
                BYTE green_BL = image[i+1][j-1].rgbtGreen;
                BYTE red_BL = image[i+1][j-1].rgbtRed;

                BYTE blue_BR = image[i+1][j+1].rgbtBlue;
                BYTE green_BR = image[i+1][j+1].rgbtGreen;
                BYTE red_BR = image[i+1][j+1].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_L + blue_BL + blue_BR + blue_B + blue) / 6;

                BYTE green_total_average = (red_R + red_L + red_BL + red_BR + red_B + red) / 6;

                BYTE red_total_average = (green_R + green_L + green_BL + green_BR + green_B + green) / 6;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if(image[height][i].rgbtBlue && !image[height][0].rgbtBlue && !image[height][width].rgbtBlue)
            {
                // Bottom Row Pixel
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_L + blue_TL + blue_TR + blue_T + blue) / 6;

                BYTE green_total_average = (red_R + red_L + red_TL + red_TR + red_T + red) / 6;

                BYTE red_total_average = (green_R + green_L + green_TL + green_TR + green_T + green) / 6;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if(image[j][0].rgbtBlue && !image[0][0].rgbtBlue && !image[height][0].rgbtBlue)
            {
                // 1 Column pixel
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_BR = image[i+1][j+1].rgbtBlue;
                BYTE green_BR = image[i+1][j+1].rgbtGreen;
                BYTE red_BR = image[i+1][j+1].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_total_average = (blue_R + blue_TR + blue_T + blue_BR + blue_B + blue) / 6;

                BYTE green_total_average = (red_R + red_TR + red_T + red_BR + red_B + red) / 6;

                BYTE red_total_average = (green_R + green_TR + green_T + green_BR + green_B + green) / 6;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else if(image[j][width].rgbtBlue && !image[0][width].rgbtBlue && !image[height][width].rgbtBlue)
            {
                // last column pixel
                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                BYTE blue_BL = image[i+1][j-1].rgbtBlue;
                BYTE green_BL = image[i+1][j-1].rgbtGreen;
                BYTE red_BL = image[i+1][j-1].rgbtRed;

                BYTE blue_total_average = (blue_T + blue_B + blue_L + blue_TL + blue_BL + blue) / 6;

                BYTE green_total_average = (red_T + red_B + red_L + red_TL + red_BL + red) / 6;

                BYTE red_total_average = (green_T + green_B + green_L + green_TL + green_BL + green) / 6;

                image[i][j].rgbtBlue = blue_total_average;
                image[i][j].rgbtGreen = green_total_average;
                image[i][j].rgbtRed = red_total_average;
            }
            else
            {
                // Every other pixel.
                BYTE blue_R = image[i][j+1].rgbtBlue;
                BYTE green_R = image[i][j+1].rgbtGreen;
                BYTE red_R = image[i][j+1].rgbtRed;

                BYTE blue_L = image[i][j-1].rgbtBlue;
                BYTE green_L = image[i][j-1].rgbtGreen;
                BYTE red_L = image[i][j-1].rgbtRed;

                BYTE blue_TL = image[i-1][j-1].rgbtBlue;
                BYTE green_TL = image[i-1][j-1].rgbtGreen;
                BYTE red_TL = image[i-1][j-1].rgbtRed;

                BYTE blue_TR = image[i-1][j+1].rgbtBlue;
                BYTE green_TR = image[i-1][j+1].rgbtGreen;
                BYTE red_TR = image[i-1][j+1].rgbtRed;

                BYTE blue_T = image[i-1][j].rgbtBlue;
                BYTE green_T = image[i-1][j].rgbtGreen;
                BYTE red_T = image[i-1][j].rgbtRed;

                BYTE blue_BL = image[i+1][j-1].rgbtBlue;
                BYTE green_BL = image[i+1][j-1].rgbtGreen;
                BYTE red_BL = image[i+1][j-1].rgbtRed;

                BYTE blue_BR = image[i+1][j+1].rgbtBlue;
                BYTE green_BR = image[i+1][j+1].rgbtGreen;
                BYTE red_BR = image[i+1][j+1].rgbtRed;

                BYTE blue_B = image[i+1][j].rgbtBlue;
                BYTE green_B = image[i+1][j].rgbtGreen;
                BYTE red_B = image[i+1][j].rgbtRed;

                BYTE blue_total_average = (blue_TR + blue_T + blue_TL + blue_L + blue + blue_R + blue_BL + blue_B + blue_BR) / 9;

                BYTE green_total_average = (green_TR + green_T + green_TL + green_L + green + green_R + green_BL + green_B + green_BR) / 9;

                BYTE red_total_average = (red_TR + red_T + red_TL + red_L + red + red_R + red_BL + red_B + red_BR) / 9;

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
