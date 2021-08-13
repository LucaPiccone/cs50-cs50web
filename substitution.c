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
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    //List Variables for cipher.
    int i = 0;
    int n = strlen(plaintext);
    int cipher[n];
    int finalcipher[n];
    // Cipher Text
    while (i < n)
    {
        if (isupper(plaintext[i]))                              // Check For Uppercase in Plaintext
        {
            cipher[i] = plaintext[i] - 'A';                     // Find The Location of Plaintext Character in the Alphabet
            if (islower(key[cipher[i]]))                        // If Key's Location of Plaintexts Locations in the key is Lowercase
            {
                finalcipher[i] = key[cipher[i]] - 'a' + 'A';    // Assign it to finalcipher[i] as Uppercase to match plaintext[i] Uppercase
            }
            else                                                // Else Assign finalcipher[i] to key's Character
            {
                finalcipher[i] = key[cipher[i]];
            }
        }
        else if (islower(plaintext[i]))                         // If Plaintext[i] is lowercase
        {
            cipher[i] = plaintext[i] - 'a';                     // Find The Location of Plaintext's Character in the Alphabet
            if (isupper(key[cipher[i]]))                        // If Key's Location of Plaintext's Location in the key is Uppercase
            {
                finalcipher[i] = key[cipher[i]] - 'A' + 'a';    // Assign it to finalcipher[i] as a Lowercase to match plaintext[i] Lowercase
            }
            else                                                // Else Assign finalcipher[i] to key's Character.
            {
                finalcipher[i] = key[cipher[i]];
            }
        }
        else                                                    // If Plaintext[i] is not a Character
        {
            cipher[i] = plaintext[i];
            finalcipher[i] = cipher[i];                         // Assign plaintext[i] to finalcipher[i]
        }

        printf("%c", finalcipher[i]);                           // print each character if finalcipher [i]
        i++;                                                    // increment i for the while loop;
    }
    printf("\n");                                               // print a new line at the end of finalcipher.
    return 0;                                                   // If all works well, return 0.
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