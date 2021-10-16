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
                    BYTE green_right = image_copy_green[i][j + 1];
                    BYTE red_right = image_copy_red[i][j + 1];

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
                    BYTE green_right = image_copy_green[i][j + 1];
                    BYTE red_right = image_copy_red[i][j + 1];

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
    int first_pixel_in_row = 0;
    int last_pixel_in_row = width - 1;

    int first_row = 0;
    int last_row = height - 1;

    BYTE PIXEL_BLACK = 0.0;

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
                    // TOP LEFT PIXEL
                    // 5 replace with PIXEL_BLACK - bottom_left, left, top_left, top, top_right
                    //

                    BYTE gx_gy_blue_top_left = PIXEL_BLACK;
                    BYTE gx_gy_green_top_left = PIXEL_BLACK;
                    BYTE gx_gy_red_top_left = PIXEL_BLACK;

                    BYTE gx_gy_blue_top = PIXEL_BLACK;
                    BYTE gx_gy_green_top = PIXEL_BLACK;
                    BYTE gx_gy_red_top = PIXEL_BLACK;

                    BYTE gx_gy_blue_top_right = PIXEL_BLACK;
                    BYTE gx_gy_green_top_right = PIXEL_BLACK;
                    BYTE gx_gy_red_top_right = PIXEL_BLACK;

                    BYTE gx_gy_blue_left = PIXEL_BLACK;
                    BYTE gx_gy_green_left = PIXEL_BLACK;
                    BYTE gx_gy_red_left = PIXEL_BLACK;

                    BYTE gx_blue = image_copy_blue[i][j];
                    BYTE gx_green = image_copy_green[i][j];
                    BYTE gx_red = image_copy_green[i][j];

                    BYTE gy_blue = image_copy_blue[i][j];
                    BYTE gy_green = image_copy_green[i][j];
                    BYTE gy_red = image_copy_green[i][j];

                    BYTE gx_blue_right = image_copy_blue[i][j+1];
                    BYTE gx_green_right = image_copy_green[i][j+1];
                    BYTE gx_red_right = image_copy_red[i][j+1];

                    BYTE gy_blue_right = image_copy_blue[i][j+1];
                    BYTE gy_green_right = image_copy_green[i][j+1];
                    BYTE gy_red_right = image_copy_red[i][j+1];

                    BYTE gx_gy_blue_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_left = PIXEL_BLACK;

                    BYTE gx_blue_bottom = image_copy_blue[i+1][j];
                    BYTE gx_green_bottom = image_copy_green[i+1][j];
                    BYTE gx_red_bottom = image_copy_red[i+1][j];

                    BYTE gy_blue_bottom = image_copy_blue[i+1][j];
                    BYTE gy_green_bottom = image_copy_green[i+1][j];
                    BYTE gy_red_bottom = image_copy_red[i+1][j];

                    BYTE gx_blue_bottom_right = image_copy_blue[i+1][j+1];
                    BYTE gx_green_bottom_right = image_copy_green[i+1][j+1];
                    BYTE gx_red_bottom_right = image_copy_red[i+1][j+1];

                    BYTE gy_blue_bottom_right = image_copy_blue[i+1][j+1];
                    BYTE gy_green_bottom_right = image_copy_green[i+1][j+1];
                    BYTE gy_red_bottom_right = image_copy_red[i+1][j+1];

                    BYTE blue_gx = round((2.0 * gx_blue_right) + (1.0 * gx_blue_bottom_right));
                    BYTE green_gx = round((2.0 * gx_green_right) + (1.0 * gx_green_bottom_right));
                    BYTE red_gx = round((2.0 * gx_red_right) + (1.0 * gx_red_bottom_right));

                    BYTE blue_gy = round((2.0 * gy_blue_bottom) + (1.0 * gy_blue_bottom_right));
                    BYTE green_gy = round((2.0 * gy_green_bottom) + (1.0 * gy_green_bottom_right));
                    BYTE red_gy = round((2.0 * gy_red_bottom) + (1.0 * gy_red_bottom_right));

                    BYTE blue_channel = sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2)));
                    BYTE green_channel = sqrt((pow(green_gx, 2)) + (pow(green_gy, 2)));
                    BYTE red_channel = sqrt((pow(red_gx, 2)) + (pow(red_gy, 2)));

                    image[i][j].rgbtBlue = blue_channel;
                    image[i][j].rgbtGreen = green_channel;
                    image[i][j].rgbtRed = red_channel;

                }

                else if (j == last_pixel_in_row)
                {
                    // TOP RIGHT PIXEL
                    // 5 pixels black, top_left, top, top_right, right, bottom_right

                    BYTE gx_gy_blue_top_left = PIXEL_BLACK;
                    BYTE gx_gy_green_top_left = PIXEL_BLACK;
                    BYTE gx_gy_red_top_left = PIXEL_BLACK;

                    BYTE gx_gy_blue_top = PIXEL_BLACK;
                    BYTE gx_gy_green_top = PIXEL_BLACK;
                    BYTE gx_gy_red_top = PIXEL_BLACK;

                    BYTE gx_gy_blue_top_right = PIXEL_BLACK;
                    BYTE gx_gy_green_top_right = PIXEL_BLACK;
                    BYTE gx_gy_red_top_right = PIXEL_BLACK;

                    BYTE gx_blue_left = image_copy_blue[i][j-1];
                    BYTE gx_green_left = image_copy_green[i][j-1];
                    BYTE gx_red_left = image_copy_red[i][j-1];

                    BYTE gy_blue_left = image_copy_blue[i][j-1];
                    BYTE gy_green_left = image_copy_green[i][j-1];
                    BYTE gy_red_left = image_copy_red[i][j-1];

                    BYTE gx_blue = image_copy_blue[i][j];
                    BYTE gx_green = image_copy_green[i][j];
                    BYTE gx_red = image_copy_green[i][j];

                    BYTE gy_blue = image_copy_blue[i][j];
                    BYTE gy_green = image_copy_green[i][j];
                    BYTE gy_red = image_copy_green[i][j];

                    BYTE gx_gy_blue_right = PIXEL_BLACK;
                    BYTE gx_gy_green_right = PIXEL_BLACK;
                    BYTE gx_gy_red_right = PIXEL_BLACK;

                    BYTE gx_blue_bottom_left = image_copy_blue[i+1][j-1];
                    BYTE gx_green_bottom_left = image_copy_green[i+1][j-1];
                    BYTE gx_red_bottom_left = image_copy_red[i+1][j-1];

                    BYTE gy_blue_bottom_left = image_copy_blue[i+1][j-1];
                    BYTE gy_green_bottom_left = image_copy_green[i+1][j-1];
                    BYTE gy_red_bottom_left = image_copy_red[i+1][j-1];

                    BYTE gx_blue_bottom = image_copy_blue[i+1][j];
                    BYTE gx_green_bottom = image_copy_green[i+1][j];
                    BYTE gx_red_bottom = image_copy_red[i+1][j];

                    BYTE gy_blue_bottom = image_copy_blue[i+1][j];
                    BYTE gy_green_bottom = image_copy_green[i+1][j];
                    BYTE gy_red_bottom = image_copy_red[i+1][j];

                    BYTE gx_gy_blue_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_right = PIXEL_BLACK;

                    BYTE blue_gx = round((-2.0 * gx_blue_left) + (-1.0 * gx_blue_bottom_left));
                    BYTE green_gx = round((-2.0 * gx_green_left) + (-1.0 * gx_green_bottom_left));
                    BYTE red_gx = round((-2.0 * gx_red_left) + (-1.0 * gx_red_bottom_left));

                    BYTE blue_gy = round((1.0 * gy_blue_bottom_left) + (2.0 * gy_blue_bottom));
                    BYTE green_gy = round((1.0 * gy_green_bottom_left) + (2.0 * gy_green_bottom));
                    BYTE red_gy = round((1.0 * gy_red_bottom_left) + (2.0 * gy_red_bottom));

                    BYTE blue_channel = sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2)));
                    BYTE green_channel = sqrt((pow(green_gx, 2)) + (pow(green_gy, 2)));
                    BYTE red_channel = sqrt((pow(red_gx, 2)) + (pow(red_gy, 2)));

                    image[i][j].rgbtBlue = blue_channel;
                    image[i][j].rgbtGreen = green_channel;
                    image[i][j].rgbtRed = red_channel;
                }

                else
                {
                    // TOP ROW
                    // 6 pixels with color
                    // 3 pixels black, top_right, top, top_left

                }

            }

            else if (i == last_row)
            {
                if (j == first_pixel_in_row)
                {
                    // BOTTOM LEFT PIXEL
                    // 5 pixels all black: top_left, left, bottom_left, bottom, bottom_right
                    // 4 pixles with color.

                    BYTE gx_gy_blue_top_left = PIXEL_BLACK;
                    BYTE gx_gy_green_top_left = PIXEL_BLACK;
                    BYTE gx_gy_red_top_left = PIXEL_BLACK;

                    BYTE gx_blue_top = image_copy_blue[i-1][j];
                    BYTE gx_green_top = image_copy_green[i-1][j];
                    BYTE gx_red_top = image_copy_red[i-1][j];

                    BYTE gy_blue_top = image_copy_blue[i-1][j];
                    BYTE gy_green_top = image_copy_green[i-1][j];
                    BYTE gy_red_top = image_copy_red[i-1][j];

                    BYTE gx_blue_top_right = image_copy_blue[i-1][j+1];
                    BYTE gx_green_top_right = image_copy_green[i-1][j+1];
                    BYTE gx_red_top_right = image_copy_red[i-1][j+1];

                    BYTE gy_blue_top_right = image_copy_blue[i-1][j+1];
                    BYTE gy_green_top_right = image_copy_green[i-1][j+1];
                    BYTE gy_red_top_right = image_copy_red[i-1][j+1];

                    BYTE gx_gy_blue_left = PIXEL_BLACK;
                    BYTE gx_gy_green_left = PIXEL_BLACK;
                    BYTE gx_gy_red_left = PIXEL_BLACK;

                    BYTE gx_blue = image_copy_blue[i][j];
                    BYTE gx_green = image_copy_green[i][j];
                    BYTE gx_red = image_copy_red[i][j];

                    BYTE gy_blue = image_copy_blue[i][j];
                    BYTE gy_green = image_copy_green[i][j];
                    BYTE gy_red = image_copy_red[i][j];

                    BYTE gx_blue_right = image_copy_blue[i][j+1];
                    BYTE gx_green_right = image_copy_green[i][j+1];
                    BYTE gx_red_right = image_copy_red[i][j+1];

                    BYTE gy_blue_right = image_copy_blue[i][j+1];
                    BYTE gy_green_right = image_copy_green[i][j+1];
                    BYTE gy_red_right = image_copy_red[i][j+1];

                    BYTE gx_blue_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_left = PIXEL_BLACK;

                    BYTE gx_gy_blue_bottom = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom = PIXEL_BLACK;

                    BYTE gx_gy_blue_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_right = PIXEL_BLACK;

                    BYTE blue_gx = round((1.0 * gx_blue_top_right) + (2.0 * gx_blue_right));
                    BYTE green_gx = round((1.0 * gx_green_top_right) + (2.0 * gx_green_right));
                    BYTE red_gx = round((1.0 * gx_red_top_right) + (2.0 * gx_red_right));

                    BYTE blue_gy = round((-2.0 * gy_blue_top) + (-1.0 * gy_blue_top_right));
                    BYTE green_gy = round((-2.0 * gy_green_top) + (-1.0 * gy_green_top_right));
                    BYTE red_gy = round((-2.0 * gy_red_top) + (-1.0 * gy_red_top_right));

                    BYTE blue_channel = sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2)));
                    BYTE green_channel = sqrt((pow(green_gx, 2)) + (pow(green_gy, 2)));
                    BYTE red_channel = sqrt((pow(red_gx, 2)) + (pow(red_gy, 2)));

                    image[i][j].rgbtBlue = blue_channel;
                    image[i][j].rgbtGreen = green_channel;
                    image[i][j].rgbtRed = red_channel;
                }

                else if (j == last_pixel_in_row)
                {
                    // BOTTOM RIGHT PIXEl
                    // 5 pixels all black - top_right, right, bottom_right, bottom, bottom_left
                    // 4 pixels with color

                    BYTE gx_blue_top_left = image_copy_blue[i-1][j-1];
                    BYTE gx_green_top_left = image_copy_green[i-1][j-1];
                    BYTE gx_red_top_left = image_copy_red[i-1][j-1];

                    BYTE gy_blue_top_left = image_copy_blue[i-1][j-1];
                    BYTE gy_green_top_left = image_copy_green[i-1][j-1];
                    BYTE gy_red_top_left = image_copy_red[i-1][j-1];

                    BYTE gx_blue_top = image_copy_blue[i-1][j];
                    BYTE gx_green_top = image_copy_green[i-1][j];
                    BYTE gx_red_top = image_copy_red[i-1][j];

                    BYTE gy_blue_top = image_copy_blue[i-1][j];
                    BYTE gy_green_top = image_copy_green[i-1][j];
                    BYTE gy_red_top = image_copy_red[i-1][j];

                    BYTE gx_gy_blue_top_right = PIXEL_BLACK;
                    BYTE gx_gy_green_top_right = PIXEL_BLACK;
                    BYTE gx_gy_red_top_right = PIXEL_BLACK;

                    BYTE gx_blue_left = image_copy_blue[i][j-1];
                    BYTE gx_green_left = image_copy_green[i][j-1];
                    BYTE gx_red_left = image_copy_red[i][j-1];

                    BYTE gy_blue_left = image_copy_blue[i][j-1];
                    BYTE gy_green_left = image_copy_green[i][j-1];
                    BYTE gy_red_left = image_copy_red[i][j-1];

                    BYTE gx_blue = image_copy_blue[i][j];
                    BYTE gx_green = image_copy_green[i][j];
                    BYTE gx_red = image_copy_red[i][j];

                    BYTE gy_blue = image_copy_blue[i][j];
                    BYTE gy_green = image_copy_green[i][j];
                    BYTE gy_red = image_copy_red[i][j];

                    BYTE gx_gy_blue_right = PIXEL_BLACK;
                    BYTE gx_gy_green_right = PIXEL_BLACK;
                    BYTE gx_gy_red_right = PIXEL_BLACK;

                    BYTE gx_blue_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_left = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_left = PIXEL_BLACK;

                    BYTE gx_gy_blue_bottom = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom = PIXEL_BLACK;

                    BYTE gx_gy_blue_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_green_bottom_right = PIXEL_BLACK;
                    BYTE gx_gy_red_bottom_right = PIXEL_BLACK;

                    BYTE blue_gx = round((-1.0 * gx_blue_top_left) + (-2.0 * gx_blue_left));
                    BYTE green_gx = round((-1.0 * gx_green_top_left) + (-2.0 * gx_green_left));
                    BYTE red_gx = round((-1.0 * gx_red_top_left) + (-2.0 * gx_red_left));

                    BYTE blue_gy = round((-1.0 * gy_blue_top_left) + (-2.0 * gy_blue_top));
                    BYTE green_gy = round((-1.0 * gy_green_top_left) + (-2.0 * gy_green_top));
                    BYTE red_gy = round((-1.0 * gy_red_top_left) + (-2.0 * gy_red_top));

                    BYTE blue_channel = sqrt((pow(blue_gx, 2)) + (pow(blue_gy, 2)));
                    BYTE green_channel = sqrt((pow(green_gx, 2)) + (pow(green_gy, 2)));
                    BYTE red_channel = sqrt((pow(red_gx, 2)) + (pow(red_gy, 2)));

                    image[i][j].rgbtBlue = blue_channel;
                    image[i][j].rgbtGreen = green_channel;
                    image[i][j].rgbtRed = red_channel;
                }

                else
                {
                    // BOTTOM ROW

                }
            }

            else if (j == first_pixel_in_row)
            {
                if (i != first_row || i != last_row)
                {
                    // FIRST COLUMN
                }
            }

            else if (j == last_pixel_in_row)
            {
                if (i != first_row || i != last_row)
                {
                    // LAST COLUMN
                }
            }

            else
            {
                // MAIN PIXELS
            }
        }
    }

    return;
}
