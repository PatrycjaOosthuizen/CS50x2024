#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Promped user to enter one parameter (the key)
    if (argc == 2)
    {
        // Check if the input string contains only digits
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            // Checks string for decimal and non-digits
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                // Terminate program and return error message to guide user for correct input
                return 1;
            }
        }
        // Convert string into the int
        int k = atoi(argv[1]);

        // Input plain text string from user
        string user_input = get_string("plaintext: ");

        // Initialize ciphertext output variable
        string cipher_out = user_input;

        // Process each character in the plaintext
        for (int i = 0; i < strlen(user_input); i++)
        {
            // Check if the character at index i of user_input is a lowercase letter
            // Calculate the new character by shifting it by k positions in the alphabet
            // 'user_input[i] - 97' converts the character to a 0-based index (a=0, b=1, ..., z=25)
            // Adding k shifts the index, and % 26 ensures it wraps around if it goes past 'z'
            // Finally, adding 97 converts back to ASCII value for lowercase letters
            if (islower(user_input[i]) != 0)
            {
                cipher_out[i] = (user_input[i] - 97 + k) % 26 + 97;
            }
            // Check if the character at index i of user_input is an uppercase letter
            if (isupper(user_input[i]) != 0)
            {
                // Similar logic as above but for uppercase letters
                // 'user_input[i] - 65' converts the character to a 0-based index (A=0, B=1, ...,
                // Z=25) The same shifting and wrapping logic applies here as well
                cipher_out[i] = (user_input[i] - 65 + k) % 26 + 65;
            }
        }
        // Output the resulting ciphertext after processing all characters
        printf("ciphertext: %s\n", cipher_out);
        return 0;
    }
    else
    {
        // If the program does not receive a valid key argument, print usage instructions
        printf("Usage: ./caesar key\n");
        // Terminate program and return error message indicating incorrect usage
        return 1;
    }
}
