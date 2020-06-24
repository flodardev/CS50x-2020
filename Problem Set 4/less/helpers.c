#include "helpers.h"
#include <math.h>
#include <stdio.h>

// functions declaration
int averagetriple(int b, int g, int r);
int sepiaRed(int r, int g, int b);
int sepiaGreen(int r, int g, int b);
int sepiaBlue(int r, int g, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each row (x - axis)
    for (int x = 0; x < height; x++)
    {
        // loop through each pixels in x - axis
        for (int y = 0; y != width; y++)
        {
            // greyscale formula = (R+G+B)/3 = AVG = assign to all pixel
            {
                int avg = averagetriple(image[x][y].rgbtBlue, image[x][y].rgbtGreen, image[x][y].rgbtRed);
                image[x][y].rgbtBlue = avg;
                image[x][y].rgbtGreen = avg;
                image[x][y].rgbtRed = avg;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through the rows (x-axis) of the image
    for (int x = 0; x < height; x++)
    {
        // loop through each pixels
        for (int y = 0; y < width; y++)
        {
            int sr = sepiaRed(image[x][y].rgbtRed, image[x][y].rgbtGreen, image[x][y].rgbtBlue);
            int sg = sepiaGreen(image[x][y].rgbtRed, image[x][y].rgbtGreen, image[x][y].rgbtBlue);
            int sb = sepiaBlue(image[x][y].rgbtRed, image[x][y].rgbtGreen, image[x][y].rgbtBlue);
            image[x][y].rgbtRed = sr;
            image[x][y].rgbtGreen = sg;
            image[x][y].rgbtBlue = sb;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int center = (width * 0.5);
    int centerpixel = width % 2;
    for (int x = 0; x < height; x++)
    {
        int y1 = width - 1;
        if (centerpixel == 0)
        {
            for (int y = 0; y < center; y++)
            {
                while (y1 != center - 1)
                {
                    // temp pixels
                    int tempRed = image[x][y].rgbtRed;
                    int tempGreen = image[x][y].rgbtGreen;
                    int tempBlue = image[x][y].rgbtBlue;
                    // swap end to first
                    image[x][y].rgbtRed = image[x][y1].rgbtRed;
                    image[x][y].rgbtGreen = image[x][y1].rgbtGreen;
                    image[x][y].rgbtBlue = image[x][y1].rgbtBlue;
                    // swap temp to end
                    image[x][y1].rgbtRed = tempRed;
                    image[x][y1].rgbtGreen = tempGreen;
                    image[x][y1].rgbtBlue = tempBlue;
                    y1--;
                    break;
                }
            }
        }
        else
        {
            for (int y = 0; y <= center; y++)
            {
                // temp pixels
                int tempRed = image[x][y].rgbtRed;
                int tempGreen = image[x][y].rgbtGreen;
                int tempBlue = image[x][y].rgbtBlue;
                // swap end to first
                image[x][y].rgbtRed = image[x][y1].rgbtRed;
                image[x][y].rgbtGreen = image[x][y1].rgbtGreen;
                image[x][y].rgbtBlue = image[x][y1].rgbtBlue;
                // swap temp to end
                image[x][y1].rgbtRed = tempRed;
                image[x][y1].rgbtGreen = tempGreen;
                image[x][y1].rgbtBlue = tempBlue;
                y1--;
                break;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // "blurred" struct
    typedef struct
    {
        BYTE rgbtRed;
        BYTE rgbtGreen;
        BYTE rgbtBlue;
    }
    blur;
    blur blurs[height][width];
    // declaring variables
    int avgred;
    int avggreen;
    int avgblue;

    // making the blur struct
    // blur middle portion (without corners and edges)
    for (int x = 1; x < height - 1; x++)
    {
        for (int y = 1; y < width - 1; y++)
        {
            // initializing the variables
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            int x2 = x - 1;
            x2 += 3;
            for (int x3 = x - 1; x3 < x2; x3++)
            {
                int y2 = y - 1;
                y2 += 3;
                for (int y3 = y - 1; y3 < y2; y3++)
                {
                    avgred += image[x3][y3].rgbtRed;
                    avggreen += image[x3][y3].rgbtGreen;
                    avgblue += image[x3][y3].rgbtBlue;
                }
            }
            // initializes the pixels in the blur struct
            blurs[x][y].rgbtRed = round(avgred / 9.0);
            blurs[x][y].rgbtGreen = round(avggreen / 9.0);
            blurs[x][y].rgbtBlue = round(avgblue / 9.0);
        }
    }
    // blur upper corner and edges
    for (int y = 0, x = 0; y < width; y++) // 2 variables x is static y is dynamic
    {
        // upper left corner
        if (y == 0)
        {
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            for (int x1 = 0; x1 < 2; x1++)
            {
                for (int y1 = 0; y1 < 2; y1++)
                {
                    avgred += image[x1][y1].rgbtRed;
                    avggreen += image[x1][y1].rgbtGreen;
                    avgblue += image[x1][y1].rgbtBlue;
                }
            }
            // averages the values
            blurs[x][y].rgbtRed = round(avgred / 4.0);
            blurs[x][y].rgbtGreen = round(avggreen / 4.0);
            blurs[x][y].rgbtBlue = round(avgblue / 4.0);
        }
        
        // upper edges
        if (y > 0 && y < width - 1)
        {
            // upper edges except corners
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            for (int x1 = 0; x1 < 2; x1++)
            {
                int y2 = y - 1;
                y2 += 3;
                for (int y3 = y - 1; y3 < y2; y3++)
                {
                    avgred += image[x1][y3].rgbtRed;
                    avggreen += image[x1][y3].rgbtGreen;
                    avgblue += image[x1][y3].rgbtBlue;
                }
            }
            // initializes the pixels in the blur struct
            blurs[x][y].rgbtRed = round(avgred / 6.0);
            blurs[x][y].rgbtGreen = round(avggreen / 6.0);
            blurs[x][y].rgbtBlue = round(avgblue / 6.0);
            // printf("Red:%i Green:%i Blue:%i", blurs[x][y].rgbtRed, blurs[x][y].rgbtGreen, blurs[x][y].rgbtBlue); //debugger
        }
        // upper right corner
        if (y == width - 1)
        {
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            for (int x1 = 0; x1 < 2; x1++)
            {
                for (int y1 = width - 2; y1 < width; y1++)
                {
                    avgred += image[x1][y1].rgbtRed;
                    avggreen += image[x1][y1].rgbtGreen;
                    avgblue += image[x1][y1].rgbtBlue;
                }
            }
            blurs[x][y].rgbtRed = round(avgred / 4.0);
            blurs[x][y].rgbtGreen = round(avggreen / 4.0);
            blurs[x][y].rgbtBlue = round(avgblue / 4.0);
        }
    }
    // left edge
    for (int x = 1, y = 0; x < height - 1; x++)
    {
        avgred = 0;
        avggreen = 0;
        avgblue = 0;
        int x2 = x - 1;
        x2 += 3;
        for (int x1 = x - 1; x1 < x2; x1++)
        {
            for (int y1 = 0; y1 < 2; y1++)
            {
                avgred += image[x1][y1].rgbtRed;
                avggreen += image[x1][y1].rgbtGreen;
                avgblue += image[x1][y1].rgbtBlue;
            }
        }
        blurs[x][y].rgbtRed = round(avgred / 6.0);
        blurs[x][y].rgbtGreen = round(avggreen / 6.0);
        blurs[x][y].rgbtBlue = round(avgblue / 6.0);
    }
    // right edge
    for (int x = 1, y = width - 1; x < height - 1; x++)
    {
        avgred = 0;
        avggreen = 0;
        avgblue = 0;
        int x2 = x - 1;
        x2 += 3;
        for (int x1 = x - 1; x1 < x2; x1++)
        {
            for (int y1 = width - 2; y1 < width; y1++)
            {
                avgred += image[x1][y1].rgbtRed;
                avggreen += image[x1][y1].rgbtGreen;
                avgblue += image[x1][y1].rgbtBlue;
            }
        }
        blurs[x][y].rgbtRed = round(avgred / 6.0);
        blurs[x][y].rgbtGreen = round(avggreen / 6.0);
        blurs[x][y].rgbtBlue = round(avgblue / 6.0);
    }
    // lower corners and edges
    for (int x = height - 1, y = 0; y < width; y++)
    {
        // lower left corner
        if (y == 0)
        {
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            //x2 = height - 2
            for (int x1 = height - 2; x1 < height; x1++)
            {
                for (int y1 = 0; y1 < 2; y1++)
                {
                    avgred += image[x1][y1].rgbtRed;
                    avggreen += image[x1][y1].rgbtGreen;
                    avgblue += image[x1][y1].rgbtBlue;
                }
            }
            blurs[x][y].rgbtRed = round(avgred / 4.0);
            blurs[x][y].rgbtGreen = round(avggreen / 4.0);
            blurs[x][y].rgbtBlue = round(avgblue / 4.0);
        }
        // lower edges
        if (y > 0 && y < width - 1)
        {
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            for (int x1 = height - 2; x1 < height; x1++)
            {
                int y2 = y - 1;
                y2 += 3;
                for (int y1 = y - 1; y1 < y2; y1++)
                {
                    avgred += image[x1][y1].rgbtRed;
                    avggreen += image[x1][y1].rgbtGreen;
                    avgblue += image[x1][y1].rgbtBlue;
                }
            }
            blurs[x][y].rgbtRed = round(avgred / 6.0);
            blurs[x][y].rgbtGreen = round(avggreen / 6.0);
            blurs[x][y].rgbtBlue = round(avgblue / 6.0);
        }
        // lower right corner
        if (y == width - 1)
        {
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            for (int x1 = height - 2; x1 < height; x1++)
            {
                for (int y1 = width - 2; y1 < width; y1++)
                {
                    avgred += image[x1][y1].rgbtRed;
                    avggreen += image[x1][y1].rgbtGreen;
                    avgblue += image[x1][y1].rgbtBlue;
                }
                blurs[x][y].rgbtRed = round(avgred / 4.0);
                blurs[x][y].rgbtGreen = round(avggreen / 4.0);
                blurs[x][y].rgbtBlue = round(avgblue / 4.0);
            }
        }
    }
    // moving pixel data from blur struct to original image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y].rgbtRed = blurs[x][y].rgbtRed;
            image[x][y].rgbtGreen = blurs[x][y].rgbtGreen;
            image[x][y].rgbtBlue = blurs[x][y].rgbtBlue;
        }
    }
    return;
}

// defining functions //

// int average function for greyscale
int averagetriple(int b, int g, int r)
{
    float triple = b + g + r;
    triple = round(triple / 3);
    return triple;
}

// int sepiaRGB
int sepiaRed(int r, int g, int b)
{
    double rr = 0.393 * r;
    double rg = 0.769 * g;
    double rb = 0.189 * b;
    int sr = round(rr + rg + rb);
    if (sr >= 255)
    {
        sr = 255;
        return sr;
    }
    else
    {
        return sr;
    }
}

int sepiaGreen(int r, int g, int b)
{
    float gr = 0.349 * r;
    float gg = 0.686 * g;
    float gb = 0.168 * b;
    int sg = round(gr + gg + gb);
    if (sg >= 255)
    {
        sg = 255;
        return sg;
    }
    else
    {
        return sg;
    }
}

int sepiaBlue(int r, int g, int b)
{
    float br = 0.272 * r;
    float bg = 0.534 * g;
    float bb = 0.131 * b;
    int sb = round(br + bg + bb);
    if (sb >= 255)
    {
        sb = 255;
        return sb;
    }
    else
    {
        return sb;
    }
}