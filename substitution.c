#include <stdio.h>          // Write a program that encypts plain text into cipher text
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//Constants.
const int KEYLENGTH = 26;

//Prototypes.
int keyCheck(int length, string word);

int main(int argc, string argv[])
{
    // Assign Command Line Arguments to Var Key.
    string key = argv[1];
    int commands = argc;
    // If Command Line Arguments Count Does Not Equal 2, Return False
    if (argc != 2)
    {
        printf("Error, Two Command Line Arguments Requried.\n");
        return 1;
    }
    // Assign Function KeyCheck to a Var.
    int confirmKey = keyCheck(commands, key);
    if (confirmKey == 1)
    {
        return 1;
    }
    // Get User Input for plaintext:
    string plaintext = get_string("Plaintext: ");
    printf("Ciphertext: ");

    //List Variables for cipher.
    int i = 0;
    int n = strlen(plaintext);
    int cipher[n];
    int finalcipher[n];
    // Cipher Text
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
    return 0;
}

int keyCheck(int length, string word)
{
    int n = strlen(word);

    if (n != KEYLENGTH)
    {
        printf("Error, The Key Must Contain 26 Characters.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < KEYLENGTH; i++)
        {
            if (word[i] < 'A' || word[i] > 'z')
            {
                printf("Error, The Key Must Contain Only Alphabetical Characters.\n");
                return 1;
            }
            else if (word[i] > 'Z' && word[i] < 'a')
            {
                printf("Error, The Key Must Contain Only Alphabetical Characters.\n");
                return 1;
            }
            else
            {
                int cc = 0;
                for (int j = 0; j < KEYLENGTH; j++)
                {
                    if (word[i] == word[j])
                    {
                        cc += 1;
                    }
                    else if (word[i] == word[j] - 32)
                    {
                        cc += 1;
                    }
                    else if (word[i] == word[j] + 32)
                    {
                        cc += 1;
                    }
                    if (cc > 1)
                    {
                        printf("Error, Key Can not Contain Duplicating Chars.\n");
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}