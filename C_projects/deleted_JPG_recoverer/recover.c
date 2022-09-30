#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

// takes a RAW file and can extract JPEG files that were deleted but not overwritten with new data in memory
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // fopen card.raw in read mode
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open card.\n");
        return 1;
    }


    BYTE buffer[BLOCK_SIZE];                // buffer of 512 bytes
    FILE *output = NULL;                    // File pointer named "output" points to a empty space
    char filename[8];                       // buffer of 8 chars for xxx.jpeg\0
    int count = 0;                          // integer named "count" set to 0

    //loop while reading || end of file NOT reached
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, card))
    {
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)                         // check first 4 bytes for JPEG format
        {
            if (output != NULL)                             // if output pointer is already pointing to a file = close file
            {
                fclose(output);
            }

            //create a filename called "000.jpg"            // point "output" to a new file
            sprintf(filename, "%03i.jpg", count);           // assign a string of chars inserting of 3 digits
            output = fopen(filename, "w");                  // at output pointer -> open/create file with name "filename"
            count++;                                        // increment file counter
        }

        if (output != NULL)                                 // if output pointer is pointing to a file
        {
            fwrite(&buffer, sizeof(buffer), 1, output);     // write 1 unit of buffer into output folder
        }                                                   // cycle back and check for 4byte header... if no header... contrinue wsriting to same output file
    }



    if (card != NULL)
    {
        fclose(card);
    }
    if (output != NULL)
    {
        fclose(output);
    }

    return 0;

}