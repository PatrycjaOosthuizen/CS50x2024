#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for the pyramid's heigh
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    // Print a pyramid of that height
    for (int rowL = 0; rowL < height; rowL++)
    {
        // Check if we need to print a space or a hash (#)
        for (int columnL = 0; columnL < height; columnL++)
        {
            if (rowL + columnL < height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        // Print two spaces between the left and right pyramids to make a gap
        printf("  ");
        // Loop to print hashes in the right pyramid based on current row number
        for (int rowR = 0; rowR < rowL + 1; rowR++)
        {
            printf("#");
        }
        printf("\n");
    }
}
