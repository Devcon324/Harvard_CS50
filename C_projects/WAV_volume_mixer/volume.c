// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];                            // create header buffer array of size 44
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);     // read a 44 byte chunk from input
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);   // write a 44 byte chunk into output

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;                                         // create sample buffer of a single variable
    while (fread(&buffer, sizeof(int16_t), 1, input))       // fread() returns "1" when reading one-byte-at-a-time
    {
        buffer = buffer * factor;                           // current iteration buffer changed
        fwrite(&buffer, sizeof(int16_t), 1, output);        // write new buffer into output file
    }                                                   // while-loop ends when fread() != 1 when it reaches EOF

    // Close files
    fclose(input);
    fclose(output);
}
