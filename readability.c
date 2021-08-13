#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

const int IN_WORD = 1;
const int OUT_WORD = 0;

int main(void)
{
    string text = get_string("Text: ");

    double letters, words, sentences, cursor;

    int n = strlen(text);
    cursor = OUT_WORD;
    letters = words = sentences = 0;
    for (int i = 0; i < n; i++)
    {
        if(text[i] < 'A' || text[i] > 'z')
        {
            ;
        }
        else if (text[i] > 'Z' && text[i] < 'a')
        {
            ;
        }
        else
        {
            letters += 1;
        }
        if (text[i] == ' ' || text[i] == '\t' || text[i] == '\n')
        {
            cursor = OUT_WORD;
        }
        else if (cursor == OUT_WORD)
        {
            cursor = IN_WORD;
            ++words;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    double index = 0;
    index = 0.0588 * (letters / words * 100.0) - 0.296 * (sentences / words * 100.0) - 15.8;
    int rounded = round(index);


    for (int i = 0; i < n; i++)
    {
        if (rounded == i)
        {
            printf("Grade %i\n", i);
            break;
        }
        else if (rounded > 16)
        {
            printf("Grade 16+\n");
            break;
        }
        else if (rounded < 1)
        {
            printf("Before Grade 1\n");
            break;
        }
    }


    return 0;
}