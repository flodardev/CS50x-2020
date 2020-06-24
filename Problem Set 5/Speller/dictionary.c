// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 999999;

// Integer for keeping track of how many "words" or "nodes"
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Rehash word for its hash number. To check the word.
    int x = hash(word);
    
    // Loop through table[x] head with a cursor
    for (node *cursor = table[x]; cursor != NULL; cursor = cursor->next)
    {
        // If word is found, return true. If cursor is the same as word.
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Source: http://www.cse.yorku.ca/~oz/hash.html
    // djb2 hash function
    unsigned long hash = 5381;
    int c;
    
    // Dictionary words are all lower case
    while ((c = tolower(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file. dptr is a pointer to the dictionary file with "read" function
    FILE *dptr = fopen(dictionary, "r");
    if (dptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    
    // Buffer(memory) for fscanf to read and copy
    char word[LENGTH + 1];

    // Loop through dictionary, word by word, until the end of file. Word is copied to buffer for later.
    while (fscanf(dptr, "%s", word) != EOF)
    {
        // Create a new node, for hash table
        node *n = malloc(sizeof(node));
        
        // If memory is not sufficient, return false
        if (n == NULL)
        {
            return false;
        }
        
        // Copy word from buffer into node->word
        strcpy(n->word, word);
        
        // Hash word to get a number
        int x = hash(word);
        
        // n-next set to table[x], even IF table[x] = NULL. Basically means n-next = NULL.
        n->next = table[x];
        
        // Reset head to n
        table[x] = n;
        
        // Word count that is copied into node(memory)
        word_count++;
    }
    fclose(dptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Return word count from load function
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Loop through table[N]
    for (int i = 0; i != N; i++)
    {
        // At the head table, cycle through the hash table starting at i until NULL.
        while (table[i] != NULL)
        {
            // Tmp assigned to what table[i] head is pointing at. So it doesn't get "orphaned." Even if it's NULL.
            node *tmp = table[i]->next;
            
            // Free malloc at table[i] head
            free(table[i]);
            
            // Table[i] is reassigned to tmp
            table[i] = tmp;
        }
    }
    return true;
}