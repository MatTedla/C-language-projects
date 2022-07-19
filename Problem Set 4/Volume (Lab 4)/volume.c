// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// Array named "buffer" to hold bytes; each section of buffer is one byte in size; WAVbuffer will hold 2 bytes at a time
uint8_t buffer[44];
int16_t WAVbuffer;

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
    fread(&buffer, 44, 1, input);
    fwrite(&buffer, 44, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // reads memory from input, updates, and writes to output
    // the reading is taking place even though "fread" function is being used as a condition for "while"; will be false when end of file is reached
    while (fread(&WAVbuffer, sizeof(int16_t), 1, input))
    {
        WAVbuffer = WAVbuffer * factor;
        fwrite(&WAVbuffer, sizeof(int16_t), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
