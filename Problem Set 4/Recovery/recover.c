// generates JPEG from provided forensic image

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Opens file "card.raw"
    FILE *f = fopen("card.raw", "r");
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // takes "unsigned char" datatype, which is 1 byte in size, and gives it the name "byte" for easier use
    typedef unsigned char byte;

    // Array named "buffer" to hold bytes; each section of buffer is one byte in size
    byte buffer[512];

    // used for counting JPEG signatures found
    int n = 0;
    
    // name of file that will be written into
    char filename[8];

    sprintf(filename, "%03i.jpg", n);

    FILE *img = fopen(filename, "w");
    if (img == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // looping to continuously read from file
    // reads memory and stores bytes into buffer (fread output is unassigned long)
    while (fread(&buffer, 512, 1, f))
    {
        // checking first four spaces for JPEG signatures; last check takes the "bitwise and" of buffer and 0xf0
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // closes file when new JPEG signatures are found
            fclose(img);
            

            // prints the name of file, i.e. the # of JPEG signature sets found, into the filename array
            sprintf(filename, "%03i.jpg", n);

            // opens an image file, the name of the file is the string printed into filename array
            // MUST REMAIN OPEN AS SUBSEQUENT BYTES ARE BEING WRITTEN TO IT
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }

            // keeps track of iterations; stops naming at 50th JPEG
            if (n != 49)
            {
                n++;
            }

            // writes memory from buffer to filename in 512 byte chunks
            fwrite(&buffer, 512, 1, img);

        }

        else if (n > 0)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(f);
}

