 // Implements a dictionary's functionality
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary word count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    //printf("%s\n", word);
    //printf("%i\n", index);
    
    node *tmp = table[index];
    
    while (strcasecmp(tmp->word, word) != 0)
    {
        tmp = tmp->next;
        if(tmp == NULL)
        {
            return false;
        }
    }
    
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    char copy;
    int hash;
    if (islower(word[0]))
    {
        copy = word[0];
        hash = copy - 'a';
    }
    else
    {
        copy = word[0] + 32;
        hash = copy - 'a';
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) == 1)
    {
        int length = strlen(word) + 1;

        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        n->next = NULL;

        strcpy(n->word, word);

        //printf("%s\n", word);
        //printf("%s\n", n->word);

        int index = hash(n->word);

        // printf("%i\n", index);

        n->next = table[index];

        table[index] = n;

        word_count++;
    }

    printf("Start");

    int count[N];
    for (int i = 0; i < N; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            printf("\t%i\t =>\n", i);
        }
        else
        {
            printf("\t%i\t", i);

            node *tmp = table[i];

            while (tmp != NULL)
            {
                count[i]++;
                tmp = tmp->next;
            }
            printf("count %i\n", count[i]);
        }
    }

    printf("End\n");


    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
