#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
    int first_pixel_in_row = 0;
    int last_pixel_in_row = width - 1;

    int first_row = 0;
    int last_row = height - 1;


    BYTE image_copy_blue[height][width];
    BYTE image_copy_green[height][width];
    BYTE image_copy_red[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy_blue[i][j] = image[i][j].rgbtBlue;
            image_copy_green[i][j] = image[i][j].rgbtGreen;
            image_copy_red[i][j] = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (i == first_row)
            {
                if (j == first_pixel_in_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_right = image_copy_blue[i][j + 1];
                    BYTE red_right = image_copy_green[i][j + 1];
                    BYTE green_right = image_copy_red[i][j + 1];

                    BYTE blue_bottom = image_copy_blue[i + 1][j];
                    BYTE green_bottom = image_copy_green[i + 1][j];
                    BYTE red_bottom = image_copy_red[i + 1][j];

                    BYTE blue_bottom_right = image_copy_blue[i + 1][j + 1];
                    BYTE green_bottom_right = image_copy_green[i + 1][j + 1];
                    BYTE red_bottom_right = image_copy_red[i + 1][j + 1];

                    BYTE blue_average = round((blue_right + blue_bottom + blue_bottom_right + blue) / 4.0);
                    BYTE green_average = round((green_right + green_bottom + green_bottom_right + green) / 4.0);
                    BYTE red_average = round((red_right + red_bottom + red_bottom_right + red) / 4.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }

                else if (j == last_pixel_in_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_left = image_copy_blue[i][j - 1];
                    BYTE green_left = image_copy_green[i][j - 1];
                    BYTE red_left = image_copy_red[i][j - 1];

                    BYTE blue_bottom = image_copy_blue[i + 1][j];
                    BYTE green_bottom = image_copy_green[i + 1][j];
                    BYTE red_bottom = image_copy_red[i + 1][j];

                    BYTE blue_bottom_left = image_copy_blue[i + 1][j - 1];
                    BYTE green_bottom_left = image_copy_green[i + 1][j - 1];
                    BYTE red_bottom_left = image_copy_red[i + 1][j - 1];

                    BYTE blue_average = round((blue_left + blue_bottom + blue_bottom_left + blue) / 4.0);
                    BYTE green_average = round((green_left + green_bottom + green_bottom_left + green) / 4.0);
                    BYTE red_average = round((red_left + red_bottom + red_bottom_left + red) / 4.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }

                else
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_left = image_copy_blue[i][j-1];
                    BYTE green_left = image_copy_green[i][j-1];
                    BYTE red_left = image_copy_red[i][j-1];

                    BYTE blue_right = image_copy_blue[i][j+1];
                    BYTE green_right = image_copy_green[i][j+1];
                    BYTE red_right = image_copy_red[i][j+1];

                    BYTE blue_bottom_left = image_copy_blue[i+1][j-1];
                    BYTE green_bottom_left = image_copy_green[i+1][j-1];
                    BYTE red_bottom_left = image_copy_red[i+1][j-1];

                    BYTE blue_bottom = image_copy_blue[i+1][j];
                    BYTE green_bottom = image_copy_green[i+1][j];
                    BYTE red_bottom = image_copy_red[i+1][j];

                    BYTE blue_bottom_right = image_copy_blue[i+1][j+1];
                    BYTE green_bottom_right = image_copy_green[i+1][j+1];
                    BYTE red_bottom_right = image_copy_red[i+1][j+1];

                    BYTE blue_average = round((blue + blue_left + blue_right + blue_bottom_left + blue_bottom + blue_bottom_right) / 6.0);
                    BYTE green_average = round((green + green_left + green_right + green_bottom_left + green_bottom + green_bottom_right) / 6.0);
                    BYTE red_average = round((red + red_left + red_right + red_bottom_left + red_bottom + red_bottom_right) / 6.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }

            }

            else if (i == last_row)
            {
                if (j == first_pixel_in_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_right = image_copy_blue[i][j + 1];
                    BYTE red_right = image_copy_green[i][j + 1];
                    BYTE green_right = image_copy_red[i][j + 1];

                    BYTE blue_top = image_copy_blue[i - 1][j];
                    BYTE green_top = image_copy_green[i - 1][j];
                    BYTE red_top = image_copy_red[i - 1][j];

                    BYTE blue_top_right = image_copy_blue[i - 1][j + 1];
                    BYTE green_top_right = image_copy_green[i - 1][j + 1];
                    BYTE red_top_right = image_copy_red[i - 1][j + 1];

                    BYTE blue_average = round((blue_right + blue_top + blue_top_right + blue) / 4.0);
                    BYTE green_average = round((green_right + green_top + green_top_right + green) / 4.0);
                    BYTE red_average = round((red_right + red_top + red_top_right + red) / 4.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }

                else if (j == last_pixel_in_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_left = image_copy_blue[i][j - 1];
                    BYTE green_left = image_copy_green[i][j - 1];
                    BYTE red_left = image_copy_red[i][j - 1];

                    BYTE blue_top = image_copy_blue[i - 1][j];
                    BYTE green_top = image_copy_green[i - 1][j];
                    BYTE red_top = image_copy_red[i - 1][j];

                    BYTE blue_top_left = image_copy_blue[i - 1][j - 1];
                    BYTE green_top_left = image_copy_green[i - 1][j - 1];
                    BYTE red_top_left = image_copy_red[i - 1][j - 1];

                    BYTE blue_average = round((blue_left + blue_top + blue_top_left + blue) / 4.0);
                    BYTE green_average = round((green_left + green_top + green_top_left + green) / 4.0);
                    BYTE red_average = round((red_left + red_top + red_top_left + red) / 4.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }

                else
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_left = image_copy_blue[i][j-1];
                    BYTE green_left = image_copy_green[i][j-1];
                    BYTE red_left = image_copy_red[i][j-1];

                    BYTE blue_right = image_copy_blue[i][j+1];
                    BYTE green_right = image_copy_green[i][j+1];
                    BYTE red_right = image_copy_red[i][j+1];

                    BYTE blue_top_left =  image_copy_blue[i-1][j-1];
                    BYTE green_top_left = image_copy_green[i-1][j-1];
                    BYTE red_top_left = image_copy_red[i-1][j-1];

                    BYTE blue_top = image_copy_blue[i-1][j];
                    BYTE green_top = image_copy_green[i-1][j];
                    BYTE red_top = image_copy_red[i-1][j];

                    BYTE blue_top_right = image_copy_blue[i-1][j+1];
                    BYTE green_top_right = image_copy_green[i-1][j+1];
                    BYTE red_top_right = image_copy_red[i-1][j+1];

                    BYTE blue_average = round((blue + blue_left + blue_right + blue_top_left + blue_top + blue_top_right) / 6.0);
                    BYTE green_average = round((green + green_left + green_right + green_top_left + green_top + green_top_right) / 6.0);
                    BYTE red_average = round((red + red_left + red_right + red_top_left + red_top + red_top_right) / 6.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;

                }
            }

            else if (j == first_pixel_in_row)
            {
                if (i != first_row || i != last_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_top = image_copy_blue[i-1][j];
                    BYTE green_top = image_copy_green[i-1][j];
                    BYTE red_top = image_copy_red[i-1][j];

                    BYTE blue_bottom = image_copy_blue[i+1][j];
                    BYTE green_bottom = image_copy_green[i+1][j];
                    BYTE red_bottom = image_copy_red[i+1][j];

                    BYTE blue_top_right = image_copy_blue[i-1][j+1];
                    BYTE green_top_right = image_copy_green[i-1][j+1];
                    BYTE red_top_right = image_copy_red[i-1][j+1];

                    BYTE blue_right = image_copy_blue[i][j+1];
                    BYTE green_right = image_copy_green[i][j+1];
                    BYTE red_right = image_copy_red[i][j+1];

                    BYTE blue_bottom_right = image_copy_blue[i+1][j+1];
                    BYTE green_bottom_right = image_copy_green[i+1][j+1];
                    BYTE red_bottom_right = image_copy_red[i+1][j+1];

                    BYTE blue_average = round((blue + blue_top + blue_bottom + blue_top_right + blue_right + blue_bottom_right) / 6.0);
                    BYTE green_average = round((green + green_top + green_bottom + green_top_right + green_right + green_bottom_right) / 6.0);
                    BYTE red_average = round((red + red_top + red_bottom + red_top_right + red_right + red_bottom_right) / 6.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }
            }

            else if (j == last_pixel_in_row)
            {
                if (i != first_row || i != last_row)
                {
                    BYTE blue = image_copy_blue[i][j];
                    BYTE green = image_copy_green[i][j];
                    BYTE red = image_copy_red[i][j];

                    BYTE blue_top = image_copy_blue[i-1][j];
                    BYTE green_top = image_copy_green[i-1][j];
                    BYTE red_top = image_copy_red[i-1][j];

                    BYTE blue_bottom = image_copy_blue[i+1][j];
                    BYTE green_bottom = image_copy_green[i+1][j];
                    BYTE red_bottom = image_copy_red[i+1][j];

                    BYTE blue_top_left =  image_copy_blue[i-1][j-1];
                    BYTE green_top_left = image_copy_green[i-1][j-1];
                    BYTE red_top_left = image_copy_red[i-1][j-1];

                    BYTE blue_left = image_copy_blue[i][j-1];
                    BYTE green_left = image_copy_green[i][j-1];
                    BYTE red_left = image_copy_red[i][j-1];

                    BYTE blue_bottom_left = image_copy_blue[i+1][j-1];
                    BYTE green_bottom_left = image_copy_green[i+1][j-1];
                    BYTE red_bottom_left = image_copy_red[i+1][j-1];

                    BYTE blue_average = round((blue + blue_top + blue_bottom + blue_top_left + blue_left + blue_bottom_left) / 6.0);
                    BYTE green_average = round((green + green_top + green_bottom + green_top_left + green_left + green_bottom_left) / 6.0);
                    BYTE red_average = round((red + red_top + red_bottom + red_top_left + red_left + red_bottom_left) / 6.0);

                    image[i][j].rgbtBlue = blue_average;
                    image[i][j].rgbtGreen = green_average;
                    image[i][j].rgbtRed = red_average;
                }
            }

            else
            {
                BYTE blue_top_left =  image_copy_blue[i-1][j-1];
                BYTE green_top_left = image_copy_green[i-1][j-1];
                BYTE red_top_left = image_copy_red[i-1][j-1];

                BYTE blue_top = image_copy_blue[i-1][j];
                BYTE green_top = image_copy_green[i-1][j];
                BYTE red_top = image_copy_red[i-1][j];

                BYTE blue_top_right = image_copy_blue[i-1][j+1];
                BYTE green_top_right = image_copy_green[i-1][j+1];
                BYTE red_top_right = image_copy_red[i-1][j+1];

                BYTE blue_left = image_copy_blue[i][j-1];
                BYTE green_left = image_copy_green[i][j-1];
                BYTE red_left = image_copy_red[i][j-1];

                BYTE blue = image_copy_blue[i][j];
                BYTE green = image_copy_green[i][j];
                BYTE red = image_copy_red[i][j];

                BYTE blue_right = image_copy_blue[i][j+1];
                BYTE green_right = image_copy_green[i][j+1];
                BYTE red_right = image_copy_red[i][j+1];

                BYTE blue_bottom_left = image_copy_blue[i+1][j-1];
                BYTE green_bottom_left = image_copy_green[i+1][j-1];
                BYTE red_bottom_left = image_copy_red[i+1][j-1];

                BYTE blue_bottom = image_copy_blue[i+1][j];
                BYTE green_bottom = image_copy_green[i+1][j];
                BYTE red_bottom = image_copy_red[i+1][j];

                BYTE blue_bottom_right = image_copy_blue[i+1][j+1];
                BYTE green_bottom_right = image_copy_green[i+1][j+1];
                BYTE red_bottom_right = image_copy_red[i+1][j+1];

                BYTE blue_average = round((blue_top_left + blue_top + blue_top_right + blue_left + blue + blue_right + blue_bottom_left + blue_bottom + blue_bottom_right) / 9.0);
                BYTE green_average = round((green_top_left + green_top + green_top_right + green_left + green + green_right + green_bottom_left + green_bottom + green_bottom_right) / 9.0);
                BYTE red_average = round((red_top_left + red_top + red_top_right + red_left + red + red_right + red_bottom_left + red_bottom + red_bottom_right) / 9.0);

                image[i][j].rgbtBlue = blue_average;
                image[i][j].rgbtGreen = green_average;
                image[i][j].rgbtRed = red_average;
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
