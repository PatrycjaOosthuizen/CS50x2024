#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Define a new type BYTE as an alias for uint8_t (unsigned 8-bit integer)
    typedef uint8_t BYTE;

    // Create a buffer of 512 bytes to hold data read from the file
    BYTE buffer[512];

    // Initialize a counter to keep track of the number of JPEG files found
    int counter = 0;

    // Pointer for the JPEG file being recovered; initialized to NULL
    FILE *jpg = NULL;

    // Check if the program received exactly one command-line argument
    if (argc != 2)
    {
        // If not, print usage instructions and return an error code
        printf("Usage: ./recover <filename>\n");
        return 1;
    }
    // Assign the first command line argument to file_pointer
    char *file_pointer = argv[1];

    // Attempt to open the file specified by file_pointer in read mode
    FILE *data_file_handle = fopen(file_pointer, "r");

    // Check if able to open such file aka exists,if fopen returns NULL, it means the file could not be opened
    if (data_file_handle == NULL)
    {

        // Print an error message indicating failure to open the file
        printf("Failed to open file: '%s'\n", file_pointer);

        // Return 1 to indicate an error occurred
        return 1;
    }

    // Read data from the data_file_handle file into the buffer until the end of the file is reached
    while (fread(buffer, sizeof(buffer), 1, data_file_handle) == 1)
    {
        // Check if the current buffer contains the JPEG file signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If this is not the first JPEG found, close the previous file
            if (counter > 0)
                fclose(jpg);

            // Create a file name variable to store the new JPEG file name
            char jpg_name[8];

            // Format and assign a unique name to the new JPEG file based on counter value
            sprintf(jpg_name, "%03i.jpg", counter);

            // Open a new JPEG file in append mode to write data into it
            jpg = fopen(jpg_name, "a");

            // Write the current buffer content to the newly opened JPEG file
            fwrite(&buffer, sizeof(buffer), 1, jpg);

            // Increment the counter to track how many JPEG files have been created
            counter++;
        }
        else
        {
            // If we are currently processing a JPEG file (counter > 0)
            if (counter > 0)
            {
                // Continue writing data from the buffer to the current JPEG file
                fwrite(&buffer, sizeof(buffer), 1, jpg);
            }
        }
    }
    // Close the file pointers
    fclose(data_file_handle);
    fclose(jpg);

    // Return 0 to indicate successful completion of the program
    return 0;
}
