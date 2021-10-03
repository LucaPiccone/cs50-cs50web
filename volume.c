// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef uint16_t twoBYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor r = read file only
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // w = write to file
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    printf("%f\n", 4 * factor);

    // TODO: Copy header from input file to output file - Header, first 44 Bytes
    BYTE header[HEADER_SIZE];

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    BYTE *p = &header[44];

    // This is the last location of memory storing the header of the audio file
    //printf("%p\n", p);
    // first postion.
    //printf("%p\n", &header);

    // TODO: Read samples from input file and write updated data to output file - Samples, 16 Byte
    twoBYTE buffer;

    for (int i = 0; fread(&buffer, sizeof(twoBYTE), 1, input); i++)
    {
        //twoBYTE *P = &buffer;

        buffer *= factor;

        fwrite(&buffer, sizeof(twoBYTE), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
