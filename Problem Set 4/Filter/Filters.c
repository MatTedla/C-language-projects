// applies different photographic filters to BMP files

#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop goes through individual rows of the picture
    for (int i = 0; i < height; i++)
    {
        // loop goes through individual columns; taken with the above loop, it goes through individual pixels
        for (int j = 0; j < width; j++)
        {
            // assign a new variable and make it hold average of R, G, and B values
            float storage;

            // convert to "float" to round decimal averages (roundf rounds floats)
            // converting to "double" also works; its twice as precise but takes up twice the memory as float
            storage = roundf((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);

            // assign that average as the new R, G, and B values of the pixel
            image[i][j].rgbtRed = storage;
            image[i][j].rgbtGreen = storage;
            image[i][j].rgbtBlue = storage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // loop goes through individual rows of the picture
    for (int i = 0; i < height; i++)
    {
        // loop goes through individual columns; taken with the above loop, it goes through individual pixels; loops when j is less or equal to half of width
        for (int j = 0; j < width / 2; j++)
        {

            int index = width - (j + 1);

            // assign temporary variable to hold all RGB values of this pixel
            RGBTRIPLE temp = image[i][j];

            //changes values of current pixel to the values held by the opposite pixel
            image[i][j] = image[i][index];

            // assign opposite pixel values held by temporary variable
            image[i][index] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE placeholder[height][width];

    // make storage arrays of size width; 1 set for odd numbered rows and 1 set for even numbered rows
    int Rstorage[width];
    int Gstorage[width];
    int Bstorage[width];

    for (int g = 0; g < height; g++)
    {
        for (int h = 0; h < width; h++)
        {
            placeholder[g][h] = image[g][h];
        }
    }

    //array that holds RGB values before hexadecimal conversion
    RGBTRIPLE RGBS[9];

    //array that holds RGB values after hexadecimal conversion
    float S[9];

    // ensures that red is the first color to be calculated
    int RGBcount = 1;

    // loop goes through individual rows of the picture
    for (int i = 0; i < height; i++)
    {
        // loop goes through individual columns; taken with the above loop, it goes through individual pixels
        for (int j = 0; j < width; j++)
        {
            // checks that RGB calculations are completed before moving to the next pixel
            int whilecheck = 0;

            while (whilecheck == 0)
            {
                int average = 9;
                int count = 0;

                //pixel values are placed in first array, then converted to a hexadecimal depending on whether R, G, or B is being accounted for
                RGBS[0] = placeholder[i - 1][j - 1];
                RGBS[1] = placeholder[i - 1][j];
                RGBS[2] = placeholder[i - 1][j + 1];
                RGBS[3] = placeholder[i][j - 1];
                RGBS[4] = placeholder[i][j];
                RGBS[5] = placeholder[i][j + 1];
                RGBS[6] = placeholder[i + 1][j - 1];
                RGBS[7] = placeholder[i + 1][j];
                RGBS[8] = placeholder[i + 1][j + 1];

                for (int k = 0; k < 9; k++)
                {
                    if (RGBcount == 1)
                    {
                        S[k] = RGBS[k].rgbtRed;
                    }
                    if (RGBcount == 2)
                    {
                        S[k] = RGBS[k].rgbtGreen;
                    }
                    if (RGBcount == 3)
                    {
                        S[k] = RGBS[k].rgbtBlue;
                    }
                }

                // omits some pixel values when central pixel is in the first row
                if (i == 0)
                {
                    S[0] = 0;
                    S[1] = 0;
                    S[2] = 0;
                    count++;
                }
                // pixel in the last row
                if (i == height - 1)
                {
                    S[6] = 0;
                    S[7] = 0;
                    S[8] = 0;
                    count++;
                }
                // pixel is in the first column
                if (j == 0)
                {
                    S[0] = 0;
                    S[3] = 0;
                    S[6] = 0;
                    count++;
                }
                // pixel is in the last column
                if (j == width - 1)
                {
                    S[2] = 0;
                    S[5] = 0;
                    S[8] = 0;
                    count++;
                }

                // changes average calculation when # of pixel calculcations to consider changes
                if (count == 1)
                {
                    average = 6;
                }
                else if (count == 2)
                {
                    average = 4;
                }

                // rounds the average of the pixel calculations; places value into appropriate storage
                if (RGBcount == 1)
                {
                    Rstorage[j] = roundf((float)(S[0] + S[1] + S[2] + S[3] + S[4] + S[5] + S[6] + S[7] + S[8]) / average);
                    RGBcount = 2;
                }
                else if (RGBcount == 2)
                {
                    Gstorage[j] = roundf((float)(S[0] + S[1] + S[2] + S[3] + S[4] + S[5] + S[6] + S[7] + S[8]) / average);
                    RGBcount = 3;
                }
                else if (RGBcount == 3)
                {
                    Bstorage[j] = roundf((float)(S[0] + S[1] + S[2] + S[3] + S[4] + S[5] + S[6] + S[7] + S[8]) / average);
                    RGBcount = 1;
                    whilecheck = 1;
                }
            }
        }

        // places the calculated rgb colors into the image
        for (int l = 0; l < width; l++)
        {
            image[i][l].rgbtRed = Rstorage[l];
            image[i][l].rgbtGreen = Gstorage[l];
            image[i][l].rgbtBlue = Bstorage[l];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make storage arrays of size width
    // these are ints so the contents within can be easily assigned to image[i][j] - which is also an int value
    int Rstorage[width];
    int Gstorage[width];
    int Bstorage[width];

    // the following are floats to account for decimal ranges; used for the calculation of the square root value
    // for Gx values only
    float Rstoragegx;
    float Gstoragegx;
    float Bstoragegx;

    // for Gy values only
    float Rstoragegy;
    float Gstoragegy;
    float Bstoragegy;

    // a subsitute image; values will be taken from the original image, will be manipulated via calculations, then stored here
    // values will be deposited back to the original image at the end of the function
    RGBTRIPLE placeholder[height][width];

    for (int g = 0; g < height; g++)
    {
        for (int h = 0; h < width; h++)
        {
            placeholder[g][h] = image[g][h];
        }
    }

    //array that holds RGB values before hexadecimal conversion
    RGBTRIPLE RGBS[9];

    //array that holds RGB values after hexadecimal conversion; for both x and y directions
    float Sx[9];
    float Sy[9];

    // ensures that red is the first color to be calculated
    int RGBcount = 1;

    // loop goes through individual rows of the picture
    for (int i = 0; i < height; i++)
    {
        // loop goes through individual columns; taken with the above loop, it goes through individual pixels
        for (int j = 0; j < width; j++)
        {
            // checks that RGB calculations are completed before moving to the next pixel
            int whilecheck = 0;

            while (whilecheck == 0)
            {
                //pixel values are placed in array
                RGBS[0] = placeholder[i - 1][j - 1];
                RGBS[1] = placeholder[i - 1][j];
                RGBS[2] = placeholder[i - 1][j + 1];
                RGBS[3] = placeholder[i][j - 1];
                RGBS[4] = placeholder[i][j];
                RGBS[5] = placeholder[i][j + 1];
                RGBS[6] = placeholder[i + 1][j - 1];
                RGBS[7] = placeholder[i + 1][j];
                RGBS[8] = placeholder[i + 1][j + 1];

                // values converted to a hexadecimal depending on whether R, G, B is being accounted for
                // for each the x and y direction, the # to multiply by is based on which of the 9 pixels (surrounding and including the current pixel) 
                // is being considered; this is based on the Sobel operator
                for (int k = 0; k < 9; k++)
                {
                    if (RGBcount == 1)
                    {
                        Sx[k] = RGBS[k].rgbtRed;
                        Sy[k] = RGBS[k].rgbtRed;
                    }
                    if (RGBcount == 2)
                    {
                        Sx[k] = RGBS[k].rgbtGreen;
                        Sy[k] = RGBS[k].rgbtGreen;
                    }
                    if (RGBcount == 3)
                    {
                        Sx[k] = RGBS[k].rgbtBlue;
                        Sy[k] = RGBS[k].rgbtBlue;
                    }

                    if (k == 0)
                    {
                        Sx[k] = Sx[k] * (-1);
                        Sy[k] = Sy[k] * (-1);
                    }

                    if (k == 1)
                    {
                        Sx[k] = Sx[k] * 0;
                        Sy[k] = Sy[k] * (-2);
                    }

                    if (k == 2)
                    {
                        Sx[k] = Sx[k] * (1);
                        Sy[k] = Sy[k] * (-1);
                    }

                    if (k == 3)
                    {
                        Sx[k] = Sx[k] * (-2);
                        Sy[k] = Sy[k] * 0;
                    }
                    
                    if (k == 4)
                    {
                        Sx[k] = Sx[k] * 0;
                        Sy[k] = Sy[k] * 0;
                    }

                    if (k == 5)
                    {
                        Sx[k] = Sx[k] * (2);
                        Sy[k] = Sy[k] * 0;
                    }
                    
                    if (k == 6)
                    {
                        Sx[k] = Sx[k] * (-1);
                        Sy[k] = Sy[k] * (1);
                    }
                    
                    if (k == 7)
                    {
                        Sx[k] = Sx[k] * 0;
                        Sy[k] = Sy[k] * (2);
                    }
                    
                    if (k == 8)
                    {
                        Sx[k] = Sx[k] * (1);
                        Sy[k] = Sy[k] * (1);
                    }
                }

                // omits some pixel values when central pixel is in the first row
                if (i == 0)
                {
                    Sx[0] = 0;
                    Sx[1] = 0;
                    Sx[2] = 0;

                    Sy[0] = 0;
                    Sy[1] = 0;
                    Sy[2] = 0;
                }
                // pixel in the last row
                if (i == height - 1)
                {
                    Sx[6] = 0;
                    Sx[7] = 0;
                    Sx[8] = 0;

                    Sy[6] = 0;
                    Sy[7] = 0;
                    Sy[8] = 0;
                }
                // pixel is in the first column
                if (j == 0)
                {
                    Sx[0] = 0;
                    Sx[3] = 0;
                    Sx[6] = 0;

                    Sy[0] = 0;
                    Sy[3] = 0;
                    Sy[6] = 0;
                }
                // pixel is in the last column
                if (j == width - 1)
                {
                    Sx[2] = 0;
                    Sx[5] = 0;
                    Sx[8] = 0;

                    Sy[2] = 0;
                    Sy[5] = 0;
                    Sy[8] = 0;
                }

                // takes the sum of the x and y values, squares them; places value into appropriate storage
                if (RGBcount == 1)
                {
                    Rstoragegx = roundf((float)(Sx[0] + Sx[1] + Sx[2] + Sx[3] + Sx[4] + Sx[5] + Sx[6] + Sx[7] + Sx[8]));
                    Rstoragegy = roundf((float)(Sy[0] + Sy[1] + Sy[2] + Sy[3] + Sy[4] + Sy[5] + Sy[6] + Sy[7] + Sy[8]));

                    Rstorage[j] = roundf(sqrt((Rstoragegx * Rstoragegx) + (Rstoragegy * Rstoragegy)));
                    RGBcount = 2;
                }
                else if (RGBcount == 2)
                {
                    Gstoragegx = roundf((float)(Sx[0] + Sx[1] + Sx[2] + Sx[3] + Sx[4] + Sx[5] + Sx[6] + Sx[7] + Sx[8]));
                    Gstoragegy = roundf((float)(Sy[0] + Sy[1] + Sy[2] + Sy[3] + Sy[4] + Sy[5] + Sy[6] + Sy[7] + Sy[8]));

                    Gstorage[j] = roundf(sqrt((Gstoragegx * Gstoragegx) + (Gstoragegy * Gstoragegy)));
                    RGBcount = 3;
                }
                else if (RGBcount == 3)
                {
                    Bstoragegx = roundf((float)(Sx[0] + Sx[1] + Sx[2] + Sx[3] + Sx[4] + Sx[5] + Sx[6] + Sx[7] + Sx[8]));
                    Bstoragegy = roundf((float)(Sy[0] + Sy[1] + Sy[2] + Sy[3] + Sy[4] + Sy[5] + Sy[6] + Sy[7] + Sy[8]));

                    Bstorage[j] = roundf(sqrt((Bstoragegx * Bstoragegx) + (Bstoragegy * Bstoragegy)));
                    RGBcount = 1;
                    whilecheck = 1;
                }
            }

            // caps the values at 255
            if (Rstorage[j] > 255)
            {
                Rstorage[j] = 255;
            }

            if (Gstorage[j] > 255)
            {
                Gstorage[j] = 255;
            }

            if (Bstorage[j] > 255)
            {
                Bstorage[j] = 255;
            }

        }

        // places values into the final image
        for (int m = 0; m < width; m++)
        {
            image[i][m].rgbtRed = Rstorage[m];
            image[i][m].rgbtGreen = Gstorage[m];
            image[i][m].rgbtBlue = Bstorage[m];
        }
    }
    return;
}
