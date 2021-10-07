// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t TWOBYTES;

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

    printf("%f\n", factor);

    //Total bytes in the file 352844.
    
    // TODO: Copy header from input file to output file - Header, first 44 Bytes
    BYTE header[HEADER_SIZE];

    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // printf("%p\n", &header[0]);
    // printf("%p\n", &header[44]);


    // TODO: Read samples from input file and write updated data to output file - Samples, 16 Byte - 17400 - 352800
    // Declare TWOBYTE as a signed int16_t
    TWOBYTES buffer;
    
    // int i = 0;

    while (fread(&buffer, sizeof(TWOBYTES), 1, input))
    {
        TWOBYTES *pt;
        
        pt = &buffer;
        
        *pt = *pt * factor;
        fwrite(&buffer, sizeof(TWOBYTES), 1, output);
        
        //i++;
    
    }
    
    // printf("I: %i\n", i);


    // Close files
    fclose(input);
    fclose(output);

    return 0;

}
