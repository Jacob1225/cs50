#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Ensure user provides one file only
    if (argc != 2)
    {
        printf("Please provide one and only one filename");
        return 1;
    }

    //Open the file provided by the user
    FILE *inputfile = fopen(argv[1], "r");

    //Verify if file provided is valid
    if (inputfile == NULL)
    {
        printf("Could not open card");
        return 1;
    }

    //Declare a buffer of type Byte
    BYTE buffer[512];

    //Variables to name the filenames
    int jpeg_count = 0;
    char filename[8];
    FILE *outfile = NULL;

    //Loop through the memory card until we reach the end
    bool jpeg_found = false;

    while (fread(buffer, BUFFER_SIZE, 1, inputfile) == 1)
    {
        //Verify if a jpeg header has been found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //If we have already found a jpeg we need to close the currently open one
            if (jpeg_found)
            {
                fclose(outfile);
            }
            //If we had not previously found a jpeg set the jpeg boolean to true
            else
            {
                jpeg_found = true;
            }

            sprintf(filename, "%03i.jpg", jpeg_count);
            outfile = fopen(filename, "a");
            jpeg_count++;
        }

        if (jpeg_found)
        {
            fwrite(buffer, BUFFER_SIZE, 1, outfile);
        }

    }

    //Close any open files
    fclose(inputfile);
    fclose(outfile);

    return 0;

}
