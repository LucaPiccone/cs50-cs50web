#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int HEADER_SIZE = 4;
const int JPG_SIZE = 512;

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

    // declare the variable to store bytes
    BYTE buffer[JPG_SIZE];

    // jpeg array stores the name of new files being generated
    char jpeg[50][12];

    // This is a file pointer to the jpeg variable.
    FILE *outfile[50];

    // i determine which jpg is being focused.
    int i = 0;

    // Illiustrate through the forensic file in 512 B chuncks
    while (fread(buffer, JPG_SIZE, 1, infile))
    {
        // if the start of a jpg
        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] & 0xfe) == 224)
        {
            // we found the first jpg
            i++;
            // name the jpg according and store it in the jpeg array
            if (i <= 10)
            {
                sprintf(jpeg[i - 1], "00%i.jpg", i - 1);
            }
            else
            {
                sprintf(jpeg[i - 1], "0%i.jpg", i - 1);
            }

            // if the first jpeg
            if (i == 1)
            {
                // open the file pointer array at index 0 and point it to the string stored in the jpeg variable at index 0
                outfile[i - 1] = fopen(jpeg[i - 1], "w");

                // write 512 B to the outfile
                fwrite(buffer, JPG_SIZE, 1, outfile[i - 1]);
            }
            // if not the first jpeg
            else
            {
                //close last jpeg
                fclose(outfile[i - 2]);

                // open and write to the file pointer
                outfile[i - 1] = fopen(jpeg[i - 1], "w");

                fwrite(buffer, JPG_SIZE, 1, outfile[i - 1]);
            }
        }
        else
        {
            // Already found jpeg
            if (i > 0)
            {
                fwrite(buffer, JPG_SIZE, 1, outfile[i - 1]);
            }
        }
    }
}