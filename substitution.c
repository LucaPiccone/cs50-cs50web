#include <stdio.h>          // Write a program that encypts plain text into cipher text
#include <cs50.h>
#include <ctype.h>
#include <string.h>
//Constants.
const int KEYLENGTH = 26;
const int COMMAND_LINE_ARGUMENTS = 2;

//Prototypes.
int checkKey(int length, string word);

int main(int argc, string argv[])
{
    int length = argc;
    string key = argv[1];

    //Call Function.
    int check = checkKey(length, key);
    if (check == 1)
    {
        return 1;
    }

    //User Input of Plaintext.
    string plaintext = get_string("Plaintext: ");

    int i = 0;
    int n = strlen(plaintext);
    int cipher[n];
    int finalcipher[n];
    while (i < n)
    {
        if (isupper(plaintext[i]))
        {
            cipher[i] = plaintext[i] - 'A';
            if (islower(key[cipher[i]]))
            {
                finalcipher[i] = key[cipher[i]] - 'a' + 'A';
            }
            else
            {
                finalcipher[i] = key[cipher[i]];
            }
        }
        else if (islower(plaintext[i]))
        {
            cipher[i] = plaintext[i] - 'a';
            if (isupper(key[cipher[i]]))
            {
                finalcipher[i] = key[cipher[i]] - 'A' + 'a';
            }
            else
            {
                finalcipher[i] = key[cipher[i]];
            }
        }
        else
        {
            cipher[i] = plaintext[i];
            finalcipher[i] = cipher[i];
        }

        printf("%c", finalcipher[i]);
        i++;
    }
    printf("\n");

}


int checkKey(int length, string word)
{
    int wordlength = strlen(word);

    if (length != COMMAND_LINE_ARGUMENTS)                                   // Accept a single command line argument, the key to use for the substitution
    {
        printf( "Error, only two command line arguements required.\n " );        // print an error message and return 1 for programs exectued without any command-line arguments
        return 1;
    }
    else
    {
        if ( wordlength != KEYLENGTH)
        {
            printf("Error the key must contain 26 Characters.\n");   // Print an error message for programs executed without all / only 26 alphabetical characters
            return 1;
        }
        else
        {
            for (int i = 0; i < KEYLENGTH; i++)
            {
                if (word[i] < 'A' || word[i] > 'z')                         // print an error message for a program executed with invalid characters.
                {
                    printf("Key must consist of alpabetical characters only.\n");
                    return 1;
                }
                else if (word[i] > 'Z' && word[i] < 'a' )
                {
                    printf("Key must consist of alphabetical characters only.\n");
                    return 1;
                }
                else
                {
                    ;
                }
            }
        }
    }
    return 0;
}

/*
key dcbe (in this case d = a)
a   b   c   d   e
65  66  67  68  69

plaintext: bee ({66, 69, 69})



*/