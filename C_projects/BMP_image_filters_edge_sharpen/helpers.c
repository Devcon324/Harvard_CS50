#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            avg = round(((float)image[row][column].rgbtBlue + (float)image[row][column].rgbtGreen + (float)image[row][column].rgbtRed) / 3.0);
            image[row][column].rgbtBlue    = avg;
            image[row][column].rgbtGreen   = avg;
            image[row][column].rgbtRed     = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            RGBTRIPLE buffer = image[row][column];
            // [width - (1 + column)] because width is not an address, it neds to be subtracted by 1
            // image[0][5 - (1 + 0)] = [0][4]
            // image[0][5 - (1 + 1)] = [0][3]
            // image[0][5 - (1 + 2)] = [0][2]
            image[row][column] = image[row][width - (1 + column)];
            image[row][width - (1 + column)] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sum_red = 0, sum_green = 0, sum_blue = 0;
    int count = 0;
    // [row-1, column-1]   [row-1, column]     [row-1, column+1]
    // [row, column-1]      [row, column]      [row, column+1]
    // [row+1, column-1]   [row+1, column]     [row+1, column+1]
    // create a copy of the original image
    RGBTRIPLE og_image[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            og_image[x][y] = image[x][y];
        }
    }
    // loop through each og_image[curRow][curCol]
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // reset variables for each analyzed og_image[curRow][curCol]
            sum_red = 0, sum_green = 0, sum_blue = 0;
            count = 0;
            // starting at the upper line being row-1
            // loop goes top, middle, bottom
            for (int row_kernel = row - 1; row_kernel < (row + 2); row_kernel++)
            {
                // start at the left most point
                // loop goes left, middle, right
                for (int col_kernel = column - 1; col_kernel < (column + 2); col_kernel++)
                {
                    //checks if going out-of-bounds
                    if (row_kernel < 0 || col_kernel < 0 || row_kernel >= height || col_kernel >= width)
                    {
                        continue;
                    }
                    else
                    {
                        sum_red      += og_image[row_kernel][col_kernel].rgbtRed;
                        sum_green    += og_image[row_kernel][col_kernel].rgbtGreen;
                        sum_blue     += og_image[row_kernel][col_kernel].rgbtBlue;
                        count++;
                    }
                }
            }
            image[row][column].rgbtBlue    = round((float)sum_blue / (float)count);
            image[row][column].rgbtGreen   = round((float)sum_green / (float)count);
            image[row][column].rgbtRed     = round((float)sum_red / (float)count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // set up Gx and Gy matrix
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    // create a copy of the original image
    RGBTRIPLE og_image[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            og_image[x][y] = image[x][y];
        }
    }
    // cycle through each og_image[curRow][curCol] of interest (POI) in image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int sumRed_Gx = 0, sumGreen_Gx = 0, sumBlue_Gx = 0;
            int sumRed_Gy = 0, sumGreen_Gy = 0, sumBlue_Gy = 0;

            // need to keep track of each kernel position for loop on line 134
            int row_coord_kernel[] = {row - 1, row, row + 1};
            int col_coord_kernel[] = {column - 1, column, column + 1};

            // cycle through each 3x3 kernal surounding (POI)
            // loop through rows in kernel
            for (int row_kernel = 0; row_kernel < 3; row_kernel++)
            {
                // loop through columns in kernel
                for (int col_kernel = 0; col_kernel < 3; col_kernel++)
                {
                    int curRow = row_coord_kernel[row_kernel];
                    int curCol = col_coord_kernel[col_kernel];
                    //checks if going out-of-bounds
                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        // take the original red values for the 9 pixels in the kernel
                        // multiply them each by the corresponding value in the kernel
                        // take the sum of the resulting values.
                        sumRed_Gx      += Gx[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtRed;
                        sumGreen_Gx    += Gx[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtGreen;
                        sumBlue_Gx     += Gx[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtBlue;

                        sumRed_Gy      += Gy[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtRed;
                        sumGreen_Gy    += Gy[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtGreen;
                        sumBlue_Gy     += Gy[row_kernel][col_kernel] * og_image[curRow][curCol].rgbtBlue;
                    }
                }
            }
            // apply sobel square root function to Gx and Gy
            int red   = round(sqrt(sumRed_Gx * sumRed_Gx + sumRed_Gy * sumRed_Gy));
            int green = round(sqrt(sumGreen_Gx * sumGreen_Gx + sumGreen_Gy * sumGreen_Gy));
            int blue  = round(sqrt(sumBlue_Gx * sumBlue_Gx + sumBlue_Gy * sumBlue_Gy));

            // adjust the image[curRow][curCol] of interest
            image[row][column].rgbtRed     = red > 255 ? 255 : red;
            image[row][column].rgbtGreen   = green > 255 ? 255 : green;
            image[row][column].rgbtBlue    = blue > 255 ? 255 : blue;
        }
    }
    return;
}