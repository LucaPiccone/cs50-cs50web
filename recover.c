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

    BYTE buffer[JPEG_SIZE];

    char jpeg[50][12];
    FILE *outfile[50];

    int jpeg_count = 0;
    int i = 0;
    while(fread(buffer, JPEG_SIZE, 1, infile))
    {
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 0xfe) == 224)
        {
            i++;
            if (i <= 10)
            {
                sprintf(jpeg[i-1], "00%i.jpg", i-1);
            }
            else
            {
                sprintf(jpeg[i-1], "0%i.jpg", i-1);
            }

            if (i == 1)
            {
                // first jpeg
                outfile[i-1] = fopen(jpeg[i-1], "w");

                fwrite(buffer, JPEG_SIZE, 1, outfile[i-1]);
            }
            else
            {
                // not first jpeg
                //close last jpeg
                fclose(outfile[i-2]);
                outfile[i-1] = fopen(jpeg[i-1], "w");

                fwrite(buffer, JPEG_SIZE, 1, outfile[i-1]);
            }
        }
        else
        {
            // Already found jpeg
            if (i > 0)
            {
                fwrite(buffer, JPEG_SIZE, 1, outfile[i-1]);
            }
        }
    }
}