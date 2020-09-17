#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop over each row of the image array of pixels
    for (int i = 0; i < height; i++)
    {
        //Loop over each pixel of the image array
        for (int j = 0; j < width; j++)
        {
            //Find values of each colour
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            //Compute the average of the colours and store it in a float
            float average = (red + blue + green) / 3.0;
            int final_average = round(average);

            //Set each colour of a pixel to the rounded average
            image[i][j].rgbtRed = final_average;
            image[i][j].rgbtBlue = final_average;
            image[i][j].rgbtGreen = final_average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through the rows of the image array
    for (int i = 0; i < height; i++)
    {
        //Loop through the first half of a row and swap pixels
        for (int j = 0; j < width / 2; j++)
        {
            //The middle pixel of a row should not be swapped
            if (j != (width - 1 - j))
            {
                RGBTRIPLE temp = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avg_red = 0;
    float avg_blue = 0;
    float avg_green = 0;

    //Make a copy of the image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    //Loop through the copy image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            //Set average accumulators back to 0 when changing target pixels
            avg_red = 0;
            avg_blue = 0;
            avg_green = 0;

            //If non-edge pixel
            if (x != 0 && y != 0 && y != width - 1 && x != height - 1)
            {
                for (int i = x - 1; i <= x + 1; i++)
                {
                    for (int j = y - 1; j <= y + 1; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 9.0);
                image[x][y].rgbtBlue = round(avg_blue / 9.0);
                image[x][y].rgbtGreen = round(avg_green / 9.0);
            }

            //Check if pixel is top left
            else if (x == 0 && y == 0)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 4.0);
                image[x][y].rgbtBlue = round(avg_blue / 4.0);
                image[x][y].rgbtGreen = round(avg_green / 4.0);
            }

            //Check if pixel is top right
            else if (x == 0 && y == width - 1)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = width - 1; j > width - 3; j--)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 4.0);
                image[x][y].rgbtBlue = round(avg_blue / 4.0);
                image[x][y].rgbtGreen = round(avg_green / 4.0);
            }

            //Check if pixel is bottom left
            else if (x == height - 1 && y == 0)
            {
                for (int i = height - 1; i > height - 3; i--)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 4.0);
                image[x][y].rgbtBlue = round(avg_blue / 4.0);
                image[x][y].rgbtGreen = round(avg_green / 4.0);
            }

            //Check if pixel is bottom right
            else if (x == height - 1 && y == width - 1)
            {
                for (int i = height - 1; i > height - 3; i--)
                {
                    for (int j = width - 1; j > width - 3; j--)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 4.0);
                image[x][y].rgbtBlue = round(avg_blue / 4.0);
                image[x][y].rgbtGreen = round(avg_green / 4.0);
            }

            //Check if pixel is on the edge of the top row
            else if (x == 0 && y != 0 && y != width - 1)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = y - 1; j < y + 2; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 6.0);
                image[x][y].rgbtBlue = round(avg_blue / 6.0);
                image[x][y].rgbtGreen = round(avg_green / 6.0);
            }

            //Check if pixel is on the edge of the left column
            else if (x != 0 && y == 0 && x != height - 1)
            {
                for (int i = x - 1; i < x + 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 6.0);
                image[x][y].rgbtBlue = round(avg_blue / 6.0);
                image[x][y].rgbtGreen = round(avg_green / 6.0);
            }

            //Check if pixel is on the edge of the bottom row
            else if (x == height - 1 && y != 0 && y != width - 1)
            {
                for (int i = height - 1; i > height - 3; i--)
                {
                    for (int j = y - 1; j < y + 2; j++)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 6.0);
                image[x][y].rgbtBlue = round(avg_blue / 6.0);
                image[x][y].rgbtGreen = round(avg_green / 6.0);
            }

            //Check if pixel is on the edge of the right column
            else if (x != 0 && y == width - 1 && x != height - 1)
            {
                for (int i = x - 1; i < x + 2; i++)
                {
                    for (int j = width - 1; j > width - 3; j--)
                    {
                        //Add the pixel's rgb values to the average
                        avg_red += copy[i][j].rgbtRed;
                        avg_blue += copy[i][j].rgbtBlue;
                        avg_green += copy[i][j].rgbtGreen;
                    }
                }
                //Set the pixel's value to the rounded average in the original image
                image[x][y].rgbtRed = round(avg_red / 6.0);
                image[x][y].rgbtBlue = round(avg_blue / 6.0);
                image[x][y].rgbtGreen = round(avg_green / 6.0);
            }
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Set gx and gy values to 0
    float gx_red = 0;
    float gy_red = 0;
    float gx_blue = 0;
    float gy_blue = 0;
    float gx_green = 0;
    float gy_green = 0;

    //Make a copy of the image to not affect the computations of new color pixels
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    //Create the 3x3 Gx and Gy kernels
    int gx[3][3];
    int gy[3][3];

    gx[0][0] = -1;
    gx[0][1] = 0;
    gx[0][2] = 1;
    gx[1][0] = -2;
    gx[1][1] = 0;
    gx[1][2] = 2;
    gx[2][0] = -1;
    gx[2][1] = 0;
    gx[2][2] = 1;

    gy[0][0] = -1;
    gy[0][1] = -2;
    gy[0][2] = -1;
    gy[1][0] = 0;
    gy[1][1] = 0;
    gy[1][2] = 0;
    gy[2][0] = 1;
    gy[2][1] = 2;
    gy[2][2] = 1;


    //Loop through the copied image to find each pixel
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            gx_red = 0;
            gy_red = 0;
            gx_blue = 0;
            gy_blue = 0;
            gx_green = 0;
            gy_green = 0;

            //If pixel is in the middle
            if (x != 0 && y != 0 && y != width - 1 && x  != height - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red = (copy[x][y + 1].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed) + (copy[x - 1][y + 1].rgbtRed) +
                         (copy[x + 1][y - 1].rgbtRed * -1) + (copy[x][y - 1].rgbtRed * -2) + (copy[x - 1][y - 1].rgbtRed * -1);

                gy_red = (copy[x + 1][y].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed) + (copy[x + 1][y - 1].rgbtRed) +
                         (copy[x - 1][y + 1].rgbtRed * -1) + (copy[x - 1][y].rgbtRed * -2) + (copy[x - 1][y - 1].rgbtRed * -1);

                gx_blue = (copy[x][y + 1].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue) + (copy[x - 1][y + 1].rgbtBlue) +
                          (copy[x + 1][y - 1].rgbtBlue * -1) + (copy[x][y - 1].rgbtBlue * -2) + (copy[x - 1][y - 1].rgbtBlue * -1);

                gy_blue = (copy[x + 1][y].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue) + (copy[x + 1][y - 1].rgbtBlue) +
                          (copy[x - 1][y + 1].rgbtBlue * -1) + (copy[x - 1][y].rgbtBlue * -2) + (copy[x - 1][y - 1].rgbtBlue * -1);

                gx_green = (copy[x][y + 1].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen) + (copy[x - 1][y + 1].rgbtGreen) +
                           (copy[x + 1][y - 1].rgbtGreen * -1) + (copy[x][y - 1].rgbtGreen * -2) + (copy[x - 1][y - 1].rgbtGreen * -1);

                gy_green = (copy[x + 1][y].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen) + (copy[x + 1][y - 1].rgbtGreen) +
                           (copy[x - 1][y + 1].rgbtGreen * -1) + (copy[x - 1][y].rgbtGreen * -2) + (copy[x - 1][y - 1].rgbtGreen * -1);

                //Sum of the squared gx and gy values
                float red_squared = (float)pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = (float)pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = (float)pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;

            }

            //Check if pixel top left
            else if (x == 0 && y == 0)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red = (copy[x][y + 1].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed);
                gy_red = (copy[x + 1][y].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed);
                gx_blue = (copy[x][y + 1].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue);
                gy_blue = (copy[x + 1][y].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue);
                gx_green = (copy[x][y + 1].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen);
                gy_green = (copy[x + 1][y].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen);

                //Sum of the squared gx and gy values
                float red_squared = (float)pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = (float)pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = (float)pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is top right
            else if (x == 0 && y == width - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red = (copy[x][y - 1].rgbtRed * -2) + (copy[x + 1][y - 1].rgbtRed * -1);
                gy_red = (copy[x + 1][y].rgbtRed * 2) + (copy[x + 1][y - 1].rgbtRed);
                gx_blue = (copy[x][y - 1].rgbtBlue * -2) + (copy[x + 1][y - 1].rgbtBlue * -1);
                gy_blue = (copy[x + 1][y].rgbtBlue * 2) + (copy[x + 1][y - 1].rgbtBlue);
                gx_green = (copy[x][y - 1].rgbtGreen * -2) + (copy[x + 1][y - 1].rgbtGreen * -1);
                gy_green = (copy[x + 1][y].rgbtGreen * 2) + (copy[x + 1][y - 1].rgbtGreen);

                //Sum of the squared gx and gy values
                float red_squared = (float)pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = (float)pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = (float)pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is bottom left
            else if (x == height - 1 && y == 0)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red = (copy[x - 1][y + 1].rgbtRed) + (copy[x][y + 1].rgbtRed * 2);
                gy_red = (copy[x - 1][y].rgbtRed * -2) + (copy[x - 1][y + 1].rgbtRed * -1);
                gx_blue = (copy[x - 1][y + 1].rgbtBlue) + (copy[x][y + 1].rgbtBlue * 2);
                gy_blue = (copy[x - 1][y].rgbtBlue * -2) + (copy[x - 1][y + 1].rgbtBlue * -1);
                gx_green = (copy[x - 1][y + 1].rgbtGreen) + (copy[x][y + 1].rgbtGreen * 2);
                gy_green = (copy[x - 1][y].rgbtGreen * -2) + (copy[x - 1][y + 1].rgbtGreen * -1);

                //Sum of the squared gx and gy values
                float red_squared = (float)pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = (float)pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = (float)pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is bottom right
            else if (x == height - 1 && y == width - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red = (copy[x - 1][y - 1].rgbtRed * -1) + (copy[x][y - 1].rgbtRed * -2);
                gy_red = (copy[x - 1][y].rgbtRed * -2) + (copy[x - 1][y - 1].rgbtRed * -1);
                gx_blue = (copy[x - 1][y - 1].rgbtBlue * -1) + (copy[x][y - 1].rgbtBlue * -2);
                gy_blue = (copy[x - 1][y].rgbtBlue * -2) + (copy[x - 1][y - 1].rgbtBlue * -1);
                gx_green = (copy[x - 1][y - 1].rgbtGreen * -1) + (copy[x][y - 1].rgbtGreen * -2);
                gy_green = (copy[x - 1][y].rgbtGreen * -2) + (copy[x - 1][y - 1].rgbtGreen * -1);

                //Sum of the squared gx and gy values
                float red_squared = (float)pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = (float)pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = (float)pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is on the edge of the top row
            else if (x == 0 && y != 0 && y != width - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red += (copy[x][y - 1].rgbtRed * -2) + (copy[x + 1][y - 1].rgbtRed * -1) + (copy[x][y + 1].rgbtRed * 2) +
                          (copy[x + 1][y + 1].rgbtRed);
                gy_red += (copy[x + 1][y - 1].rgbtRed) + (copy[x + 1][y].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed);
                gx_blue += (copy[x][y - 1].rgbtBlue * -2) + (copy[x + 1][y - 1].rgbtBlue * -1) + (copy[x][y + 1].rgbtBlue * 2) +
                           (copy[x + 1][y + 1].rgbtBlue);
                gy_blue += (copy[x + 1][y - 1].rgbtBlue) + (copy[x + 1][y].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue);
                gx_green += (copy[x][y - 1].rgbtGreen * -2) + (copy[x + 1][y - 1].rgbtGreen * -1) + (copy[x][y + 1].rgbtGreen * 2) +
                            (copy[x + 1][y + 1].rgbtGreen);
                gy_green += (copy[x + 1][y - 1].rgbtGreen) + (copy[x + 1][y].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen);

                //Sum of the squared gx and gy values
                float red_squared = pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is on the edge of the left column
            else if (x != 0 && y == 0 && x != height - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red += (copy[x - 1][y + 1].rgbtRed) + (copy[x][y + 1].rgbtRed * 2) + (copy[x + 1][y + 1].rgbtRed);
                gy_red += (copy[x + 1][y + 1].rgbtRed) + (copy[x + 1][y].rgbtRed * 2) + (copy[x - 1][y + 1].rgbtRed * -1) +
                          (copy[x - 1][y].rgbtRed * -2);
                gx_blue += (copy[x - 1][y + 1].rgbtBlue) + (copy[x][y + 1].rgbtBlue * 2) + (copy[x + 1][y + 1].rgbtBlue);
                gy_blue += (copy[x + 1][y + 1].rgbtBlue) + (copy[x + 1][y].rgbtBlue * 2) + (copy[x - 1][y + 1].rgbtBlue * -1) +
                           (copy[x - 1][y].rgbtBlue * -2);
                gx_green += (copy[x - 1][y + 1].rgbtGreen) + (copy[x][y + 1].rgbtGreen * 2) + (copy[x + 1][y + 1].rgbtGreen);
                gy_green += (copy[x + 1][y + 1].rgbtGreen) + (copy[x + 1][y].rgbtGreen * 2) + (copy[x - 1][y + 1].rgbtGreen * -1) +
                            (copy[x - 1][y].rgbtGreen * -2);

                //Sum of the squared gx and gy values
                float red_squared = pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is on the edge of the bottom row
            else if (x == height - 1 && y != 0 && y != width - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red += (copy[x - 1][y + 1].rgbtRed) + (copy[x][y + 1].rgbtRed * 2) + (copy[x - 1][y - 1].rgbtRed * -1) +
                          (copy[x][y - 1].rgbtRed * -2);
                gy_red += (copy[x - 1][y - 1].rgbtRed * -1) + (copy[x - 1][y].rgbtRed * -2) + (copy[x - 1][y + 1].rgbtRed * -1);
                gx_blue += (copy[x - 1][y + 1].rgbtBlue) + (copy[x][y + 1].rgbtBlue * 2) + (copy[x - 1][y - 1].rgbtBlue * -1) +
                           (copy[x][y - 1].rgbtBlue * -2);
                gy_blue += (copy[x - 1][y - 1].rgbtBlue * -1) + (copy[x - 1][y].rgbtBlue * -2) + (copy[x - 1][y + 1].rgbtBlue * -1);
                gx_green += (copy[x - 1][y + 1].rgbtGreen) + (copy[x][y + 1].rgbtGreen * 2) + (copy[x - 1][y - 1].rgbtGreen * -1) +
                            (copy[x][y - 1].rgbtGreen * -2);
                gy_green += (copy[x - 1][y - 1].rgbtGreen * -1) + (copy[x - 1][y].rgbtGreen * -2) + (copy[x - 1][y + 1].rgbtGreen * -1);

                //Sum of the squared gx and gy values
                float red_squared = pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

            //Check if pixel is on the edge of the right column
            else if (x != 0 && y == width - 1 && x != height - 1)
            {
                //Multiply the pixel values by their respective kernel values
                gx_red += (copy[x - 1][y - 1].rgbtRed * -1) + (copy[x][y - 1].rgbtRed * -2) + (copy[x + 1][y - 1].rgbtRed * -1);
                gy_red += (copy[x - 1][y - 1].rgbtRed * -1) + (copy[x - 1][y].rgbtRed * -2) + (copy[x + 1][y - 1].rgbtRed) +
                          (copy[x + 1][y].rgbtRed * 2);
                gx_blue += (copy[x - 1][y - 1].rgbtBlue * -1) + (copy[x][y - 1].rgbtBlue * -2) + (copy[x + 1][y - 1].rgbtBlue * -1);
                gy_blue += (copy[x - 1][y - 1].rgbtBlue * -1) + (copy[x - 1][y].rgbtBlue * -2) + (copy[x + 1][y - 1].rgbtBlue) +
                           (copy[x + 1][y].rgbtBlue * 2);
                gx_green += (copy[x - 1][y - 1].rgbtGreen * -1) + (copy[x][y - 1].rgbtGreen * -2) + (copy[x + 1][y - 1].rgbtGreen * -1);
                gy_green += (copy[x - 1][y - 1].rgbtGreen * -1) + (copy[x - 1][y].rgbtGreen * -2) + (copy[x + 1][y - 1].rgbtGreen) +
                            (copy[x + 1][y].rgbtGreen * 2);

                //Sum of the squared gx and gy values
                float red_squared = pow(gx_red, 2) + pow(gy_red, 2);
                float blue_squared = pow(gx_blue, 2) + pow(gy_blue, 2);
                float green_squared = pow(gx_green, 2) + pow(gy_green, 2);

                //Set the pixel colours to the rounded square root of gx^2 + gy^2
                int red = round(pow(red_squared, 0.5));
                int blue = round(pow(blue_squared, 0.5));
                int green = round(pow(green_squared, 0.5));

                image[x][y].rgbtRed = red > 255 ? 255 : red;
                image[x][y].rgbtBlue = blue > 255 ? 255 : blue;
                image[x][y].rgbtGreen = green > 255 ? 255 : green;
            }

        }
    }

    return;
}
