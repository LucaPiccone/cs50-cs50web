 // Implements a dictionary's functionality
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 216000;

// Hash table
node *table[N];

// Dictionary word count
int word_count = 0;

typedef uint64_t EIGHT_BYTES;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    // printf("%s\n", word);
    // printf("%i\n", index);

    if (table[index] == NULL)
        return false;

    node *tmp = table[index];

    while (strcasecmp(tmp->word, word) != 0)
    {
        if (tmp->next != NULL)
            tmp = tmp->next;
        else
            return false;
    }

    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // HASH FUNCTION:
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash

    int length = strlen(word) + 1;

    char copy[length];
    for (int i = 0; i < length; i++)
    {
        if (islower(word[i]))
        {
            copy[i] = word[i];
        }
        else
        {
            copy[i] = (word[i] + 32);
        }
    }

    EIGHT_BYTES fnv_prime = 14695981039346656037U;
    EIGHT_BYTES hash = 14695981039346656037U;

    for (int i = 0; i < length; i++)
    {
        copy[i] *= 7;
        hash = hash * fnv_prime;
        hash = hash ^ copy[i];
    }

    hash = hash % 216000;

    return (hash);
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
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        n->next = NULL;
        strcpy(n->word, word);

        int index = hash(n->word);
        n->next = table[index];
        table[index] = n;

        word_count++;
    }

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
