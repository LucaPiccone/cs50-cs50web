#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int HEADER_SIZE = 4;
const int JPEG_SIZE = 512;

int main(int argc, char *argv[])
{
    //
    if (argc != 2)
    {
        printf("Usage: Recover JPEGs. Please provide the correct name of an image file.\n");
        return 1;
    }

    // INFILE CONTAINS 7918080 BYTES
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open the input file.\n");
        return 1;
    }


    char jpeg[50][12];
    FILE *outfile[50];
    for (int i = 0; i < 50; i++)
    {
        if (i < 10)
        {
            sprintf(jpeg[i], "00%i.jpeg", i);
        }
        else
        {
            sprintf(jpeg[i], "0%i.jpeg", i);
        }

        outfile[i] = fopen(jpeg[i], "w");
        if (!outfile[i])
        {
            return 1;
        }
    }

    BYTE buffer[JPEG_SIZE];
    BYTE header[HEADER_SIZE];

    int jpeg_count = 0;
    int count = 0;
    while(fread(buffer, JPEG_SIZE, 1, infile))
    {
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 0xfe) == 224)
        {
            jpeg_count++;
            if (jpeg_count == 1)
            {
                //first jpeg
                fwrite(buffer, JPEG_SIZE, 1, outfile[jpeg_count-1]);
            }
            else
            {
                // not first jpeg
                fwrite(buffer, JPEG_SIZE, 1, outfile[jpeg_count-1]);
            }
        }
        else
        {
            // Already found jpeg
            if (jpeg_count > 0)
            {
                fwrite(buffer, JPEG_SIZE, 1, outfile[jpeg_count-1]);
            }
        }
    }

    printf("%i\n", jpeg_count);

    for (int i = 0; i < 50; i++)
    {
        fclose(outfile[i]);
    }

    fclose(infile);

}