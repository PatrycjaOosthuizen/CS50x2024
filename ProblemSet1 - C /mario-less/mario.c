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
    for (int row = 0; row < height; row++)
    {
        // Print spaces
        for (int space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        // Print row of bricks
        for (int column = 0; column <= row; column++)
        {
            printf("#");
        }
        printf("\n");
    }
}
