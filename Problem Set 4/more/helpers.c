#include "helpers.h"
#include <math.h>
#include <stdio.h>

// function declaration
int averagetriple(int b, int g, int r);
int red(float xr, float yr);
int green(float xg, float yg);
int blue(float xb, float yb);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop through each row (y - axis) vertical
    for (int y = 0; y < height; y++)
    {
        // loop through each pixels in x - axis horizontal
        for (int x = 0; x != width; x++)
        {
            // greyscale formula = (R+G+B)/3 = AVG = assign to all pixel
            {
                int avg = averagetriple(image[y][x].rgbtBlue, image[y][x].rgbtGreen, image[y][x].rgbtRed);
                image[y][x].rgbtBlue = avg;
                image[y][x].rgbtGreen = avg;
                image[y][x].rgbtRed = avg;
            }
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
// this attempt is simply for a cleaner code compared to less comfortable
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
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // initializing the variables
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            int xlimit = (x - 1) + 3;
            for (int x1 = x - 1; x1 < xlimit; x1++)
            {
                // if x1 is negative ignore and more than height
                if (x1 > -1 && x1 < height)
                {
                    int ylimit = (y - 1) + 3;
                    for (int y1 = y - 1; y1 < ylimit; y1++)
                    {
                        // if y1 is negative and more than width
                        if (y1 > -1 && y1 < width)
                        {
                            avgred += image[x1][y1].rgbtRed;
                            avggreen += image[x1][y1].rgbtGreen;
                            avgblue += image[x1][y1].rgbtBlue;
                        }
                    }
                }
            }
            // initializes the pixels in the blur struct
            // upper and lower corners and edges
            if (x == 0 || x == height - 1)
            {
                if (y == 0 || y == width - 1)
                {
                    blurs[x][y].rgbtRed = round(avgred / 4.0);
                    blurs[x][y].rgbtGreen = round(avggreen / 4.0);
                    blurs[x][y].rgbtBlue = round(avgblue / 4.0);
                }
                else
                {
                    blurs[x][y].rgbtRed = round(avgred / 6.0);
                    blurs[x][y].rgbtGreen = round(avggreen / 6.0);
                    blurs[x][y].rgbtBlue = round(avgblue / 6.0);
                }
            }
            // left and right edges
            if (x > 0 && x < height - 1)
            {
                if (y == 0 || y == width - 1)
                {
                    blurs[x][y].rgbtRed = round(avgred / 6.0);
                    blurs[x][y].rgbtGreen = round(avggreen / 6.0);
                    blurs[x][y].rgbtBlue = round(avgblue / 6.0);
                }
                // "middle" pixels
                if (y > 0 && y < width - 1)
                {
                    blurs[x][y].rgbtRed = round(avgred / 9.0);
                    blurs[x][y].rgbtGreen = round(avggreen / 9.0);
                    blurs[x][y].rgbtBlue = round(avgblue / 9.0);
                }
            }
        }
    }
    // blurred image into orignal image
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // "edge" struct
    typedef struct
    {
        BYTE rgbtRed;
        BYTE rgbtGreen;
        BYTE rgbtBlue;
    }
    edge;
    edge edges[height][width];
    // Gx Kernel 2D array
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // Gy Kernel 2D array
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    // y axis vertical
    for (int y = 0; y < height; y++)
    {
        // x axis horizontal
        for (int x = 0; x < width; x++)
        {
            // 3x3 grid
            int ylimit = 0, xlimit = 0, cl = 0;
            float gxred = 0, gxgreen = 0, gxblue = 0, gyred = 0, gygreen = 0, gyblue = 0;
            ylimit = (y - 1) + 3;
            for (int y1 = y - 1; y1 < ylimit; y1++)
            {
                int rw = 0;
                xlimit = (x - 1) + 3;
                for (int x1 = x - 1; x1 < xlimit; x1++)
                {
                    // beyond borders all values = 0
                    if (x1 < 0 || y1 < 0 || x1 >= width || y1 >= height)
                    {
                        gxred += 0;
                        gxgreen += 0;
                        gxblue += 0;
                        gyred += 0;
                        gygreen += 0;
                        gyblue += 0;
                        rw += 1;
                    }
                    else
                    {
                        // run through Gx's 3x3 grid
                        gxred += image[y1][x1].rgbtRed * gx[cl][rw];
                        gxgreen += image[y1][x1].rgbtGreen * gx[cl][rw];
                        gxblue += image[y1][x1].rgbtBlue * gx[cl][rw];
                        // run through Gy's 3x3 grid
                        gyred += image[y1][x1].rgbtRed * gy[cl][rw];
                        gygreen += image[y1][x1].rgbtGreen * gy[cl][rw];
                        gyblue += image[y1][x1].rgbtBlue * gy[cl][rw];
                        rw += 1;
                    }
                }
                cl += 1;
            }
            // function for square root of power 2
            // results into edges array
            edges[y][x].rgbtRed = red(gxred, gyred);
            edges[y][x].rgbtGreen = green(gxgreen, gygreen);
            edges[y][x].rgbtBlue = blue(gxblue, gyblue);
        }
    }
    // edged image to original image
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            image[y][x].rgbtRed = edges[y][x].rgbtRed;
            image[y][x].rgbtGreen = edges[y][x].rgbtGreen;
            image[y][x].rgbtBlue = edges[y][x].rgbtBlue;
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

// Square root of Gx^2 + Gy^2
// edge red
int red(float xr, float yr)
{
    xr = pow(xr, 2);
    yr = pow(yr, 2);
    int r = round(sqrt(xr + yr));
    if (r > 255)
    {
        r = 255;
    }
    return r;
}
// edge green
int green(float xg, float yg)
{
    xg = pow(xg, 2);
    yg = pow(yg, 2);
    int g = round(sqrt(xg + yg));
    if (g > 255)
    {
        g = 255;
    }
    return g;
}
// edge blue
int blue(float xb, float yb)
{
    xb = pow(xb, 2);
    yb = pow(yb, 2);
    int b = round(sqrt(xb + yb));
    if (b > 255)
    {
        b = 255;
    }
    return b;
}