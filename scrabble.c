#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie");
    }
    printf("\n");
}

int compute_score(string word)
{
    int score = 0;

    // Loops for as long as word != '\0'.
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Print every char in word to uppercase individually.
        word[i] = toupper(word[i]);

        //Score each letter of the word accordingly and add it to int score.
        if (word[i]  == 'A' || word[i] == 'E' || word[i] == 'I' || word[i] == 'L' || word[i] == 'N' || word[i] == 'O' || word[i] == 'R'
            || word[i] == 'S' || word[i] == 'T' || word[i] == 'U')
        {
            score = score + 1;
        }
        else if (word[i] == 'D' || word[i] == 'G')
        {
            score = score + 2;
        }
        else if (word[i] == 'B' || word[i] == 'C' || word[i] == 'M' || word[i] == 'P')
        {
            score = score + 3;
        }
        else if (word[i] == 'F' || word[i] == 'H' || word[i] == 'V' || word[i] == 'W' || word[i] == 'Y')
        {
            score = score + 4;
        }
        else if (word[i] == 'K')
        {
            score = score + 5;
        }
        else if (word[i] == 'J' || word[i] == 'X')
        {
            score = score + 8;
        }
        else if (word[i] == 'Q' || word[i] == 'Z')
        {
            score = score + 10;
        }
    }
    return score;
}