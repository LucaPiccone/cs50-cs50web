#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

const int IN_WORD = 1;                              //A variable to help the program decide whether or not the cursor is located inside a word.
const int OUT_WORD = 0;                             //A variable to help the program decide whether or not the cursor is located insdie a word.

int main(void)
{
    string text = get_string("Text: ");             // Prompt user for text.

    double letters, words, sentences, cursor;       // Variables.

    int n = strlen(text);                           // Variable of the string length of text.
    cursor = OUT_WORD;                              // Assign Variable.
    letters = words = sentences = 0;                // Assign Variables to 0.
    for (int i = 0; i < n; i++)                     // For Loop for each character in the input text.
    {
        if (text[i] < 'A' || text[i] > 'z')             // If the character isn't a letter, do nothing.
        {
            ;                                               // Do Nothing.
        }
        else if (text[i] > 'Z' && text[i] < 'a')        // Else if the character isn't a letter, do nothing.
        {
            ;                                               // Do Nothing.
        }
        else                                            // Else if the character is a letter, letter += 1.
        {
            letters += 1;                                   // letter = letter + 1.
        }
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n')   // If the character is a space, tab, or newline consider the cursor out of a word.
        {
            cursor = OUT_WORD;                                          // Assign cursor to OUT_WORD.
        }
        else if (cursor == OUT_WORD)                                // If cursor is Out_word assign it to IN_WORD and add word += 1.
        {
            cursor = IN_WORD;                                           // Assign cursor to IN_WORD.
            ++words;                                                    // words = words + 1.
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')     // If the character is a period, bang or question mark assign sentence += 1.
        {
            sentences += 1;                                             // Sentences + sentences + 1.
        }
    }
    
    //Assign index to 0
    double index = 0;
    //Calculate the Coleman-Liau index.
    index = 0.0588 * (letters / words * 100.0) - 0.296 * (sentences / words * 100.0) - 15.8;
    //Round it to the nearest integer.
    int rounded = round(index);


    for (int i = 0; i < n; i++)         // A for loop for each character of the text, although it will end when assigned a rounded index number.
    {
        if (rounded == i)               // If rounded = 1 - 16 print the grade.
        {
            printf("Grade %i\n", i);    // Print Grade.
            break;                      // Break the loop.
        }
        else if (rounded > 16)          // If Rounded is above 16 print: Grade 16+.
        {
            printf("Grade 16+\n");      // Print Grade 16+.
            break;                      // Break the loop.
        }
        else if (rounded < 1)           // Else if rounded is less than 1 print: Before Grade 1.
        {
            printf("Before Grade 1\n"); // Print Before Grade 1.
            break;                      // Break the loop.
        }
    }
    return 0;
}