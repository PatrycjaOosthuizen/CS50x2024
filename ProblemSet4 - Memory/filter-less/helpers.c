#include "helpers.h"
#include "math.h"
#include "string.h"

// Define a constant for the colors, represented by the integers value
#define const_RED_COLOR 0
#define const_GREEN_COLOR 1
#define const_BLUE_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row of the image
    for (int row = 0; row < height; row++)
    {
        // Loop through each column of the current row
        for (int column = 0; column < width; column++)
        {
            // Get RGB values from the current pixel
            int red = image[row][column].rgbtRed;
            int green = image[row][column].rgbtGreen;
            int blue = image[row][column].rgbtBlue;

            // Calculate the average of the RGB values to convert to grayscale, round it to the nearest integer
            int average = round((red + green + blue) / 3.0);

            // Set all RGB components of the pixel to the calculated average value
            image[row][column].rgbtRed = average;
            image[row][column].rgbtGreen = average;
            image[row][column].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row of the image
    for (int row = 0; row < height; row++)
    {
        // Loop through each column of the image
        for (int column = 0; column < width; column++)
        {
            // Get the RGB values of the current pixel
            int red = image[row][column].rgbtRed;
            int green = image[row][column].rgbtGreen;
            int blue = image[row][column].rgbtBlue;

            // Calculate the new sepia values using the sepia conversion formula, round it to the nearest integer
            int sepiaRed = round(0.393 * red + 0.769 * green + 0.189 * blue);
            int sepiaGreen = round(0.349 * red + 0.686 * green + 0.168 * blue);
            int sepiaBlue = round(0.272 * red + 0.534 * green + 0.131 * blue);

            // Cap value at 255 using fmin() to ensure RGB values do not exceed maximum limit
            // Set each RGB values to sepia value
            image[row][column].rgbtRed = fmin(255, sepiaRed);
            image[row][column].rgbtGreen = fmin(255, sepiaGreen);
            image[row][column].rgbtBlue = fmin(255, sepiaBlue);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary variable to hold pixel data during swapping
    RGBTRIPLE temp;
    // Loop through each row of the image
    for (int row = 0; row < height; row++)
    {
        // Loop through half of the columns to swap pixels
        for (int column = 0; column < width / 2; column++)
        {
            // Store the current pixel in a temporary variable
            temp = image[row][column];

            // Swap the current pixel with its corresponding pixel on the opposite side
            image[row][column] = image[row][width - column - 1];

            // Assign the temporary pixel value to the opposite side pixel
            image[row][width - column - 1] = temp;
        }
    }
    return;
}

// Function to calculate the blurred value of a specific color channel (red, green, or blue)
// for a pixel located at (i, j) in an image represented by a 2D array of RGBTRIPLE structures.
// Parameters:
// - int i: The row index of the pixel in the image.
// - int j: The column index of the pixel in the image.
// - int height: The total number of rows in the image.
// - int width: The total number of columns in the image.
// - RGBTRIPLE image[height][width]: A 2D array representing the image where each element contains
//   RGB values for a pixel.
// - int color_position: An integer indicating which color channel to average (red, green, or blue).
int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_position)
{
    // Initialize variables to hold the sum of color values and count of valid pixels.
    float count = 0; // To keep track of how many valid neighboring pixels are considered.
    int sum = 0;     // To accumulate the sum of color values from neighboring pixels.

    // Loop through a 3x3 grid centered around (i, j) to access neighboring pixels.
    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            // Check if the current neighbor is out of bounds. If so, skip it.
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                continue; // Skip this iteration if out of bounds.
            }
            // Depending on which color channel we are averaging, add the appropriate value to sum.
            if (color_position == const_RED_COLOR)
            {
                sum = sum + image[row][column].rgbtRed; // Add red value.
            }
            else if (color_position == const_GREEN_COLOR)
            {
                sum = sum + image[row][column].rgbtGreen; // Add green value.
            }
            else
            {
                sum = sum + image[row][column].rgbtBlue; // Add blue value.
            }
            count++; // Increment count for each valid pixel processed.
        }
    }
    // Return the average value rounded to the nearest integer.
    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image to store pixel values before blurring
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        // Loop through each pixel in the original image
        for (int column = 0; column < width; column++)
        {
            // Copy the pixel value from the original image to the copy array
            copy[row][column] = image[row][column];
        }
    }
    // Loop through each pixel again to apply the blur effect
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Calculate and set the new red value for the current pixel using getBlur function
            image[row][column].rgbtRed = getBlur(row, column, height, width, copy, const_RED_COLOR);

            // Calculate and set the new green value for the current pixel using getBlur function
            image[row][column].rgbtGreen = getBlur(row, column, height, width, copy, const_GREEN_COLOR);

            // Calculate and set the new blue value for the current pixel using getBlur function
            image[row][column].rgbtBlue = getBlur(row, column, height, width, copy, const_BLUE_COLOR);
        }
    }
    return;
}
