#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i<height; i++)
    {
        for(int j = 0; j<width; j++)
        {
            int valRed, valGreen, valBlue;
            valRed = round(image[i][j].rgbtRed * 0.393 +image[i][j].rgbtGreen * 0.769 +image[i][j].rgbtBlue * 0.189);
            valGreen = round(image[i][j].rgbtRed * 0.349 +image[i][j].rgbtGreen * 0.686 +image[i][j].rgbtBlue * 0.168);
            valBlue = round(image[i][j].rgbtRed * 0.272 +image[i][j].rgbtGreen * 0.534 +image[i][j].rgbtBlue * 0.131);
            image[i][j].rgbtRed = valRed > 255? 255 : valRed;
            image[i][j].rgbtGreen = valGreen > 255? 255: valGreen;
            image[i][j].rgbtBlue = valBlue > 255? 255: valBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_one[height][width];
    for(int row = 0; row<height; row++)
    {
        for(int col = 0; col<width; col++)
        {
            old_one[row][col] = image[row][col];
        }
    }

    for (int row = 0; row< height; row++)
    {
        for (int col = 0,j = width-1; col<width; col++)
        {
            image[row][col] = old_one[row][j];
            j--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE old_one[height][width];
    for(int row = 0; row<height; row++)
    {
        for(int col = 0; col<width; col++)
        {
            old_one[row][col] = image[row][col];
        }
    }
    for(int currow = 0; currow<height; currow++)
    {
        for(int curcol = 0, count = 0; curcol<width; curcol++)
        {
            int totalr = 0;
            int totalg = 0;
            int totalb = 0;
            for(int blurrow = currow-1; blurrow <= currow+1; blurrow++)
            {
                for(int blurcol = curcol-1; blurcol <= curcol+1; blurcol++)
                {
                    if(blurcol >= 0 && blurrow >= 0 && blurcol < width && blurrow < height)
                    {
                        totalr += old_one[blurrow][blurcol].rgbtRed;
                        totalg += old_one[blurrow][blurcol].rgbtGreen;
                        totalb += old_one[blurrow][blurcol].rgbtBlue;
                        count++;
                    }
                }
            }
            image[currow][curcol].rgbtRed = round(totalr / count);
            image[currow][curcol].rgbtGreen = round(totalg / count);
            image[currow][curcol].rgbtBlue = round(totalb / count);
            count = 0;
        }
    }
    return;
}
