// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// if max length is 45
// if highest ascii letter is z (122)
// then sum of largest word is 122 * 45 = 5490
// thus hash function would be = sum % 5490
const unsigned int N = (LENGTH + 1) * ('z');

// Hash table
node *table[N];
int word_count = 0;


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    /*
    1. fopen dicitonary
        a. check if return value is NULL
    */
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    /*
    2. read strings from file one at a time
        a. fscanf(file, "%s", word)
        b. fscanf will return EOF once it reaches end of file
    3. create a new node ofr EACH WORD
        a. malloc for each word
        b. remember to check if return value is NULL
        c. copy word into node using strcpy(n->word, "Hello");
    */
    // buffer an array for 1 word of max length + 1
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return false;
        }
        // copy word into new_word node
        strcpy(new_word->word, word);
        new_word->next = NULL;
        /*
        4. Hash word to optain a hash value
            a. use a hash function
            b. input word, output index number
        */
        int index = hash(word);
        /*
        5. insert word node into hash table at hash location
            a. add a node
                i. malloc TEMP node
                ii. point TEMP to first word in table
                iii. point hash table to TEMP
                iV. free(temp)
        */

        if (table[index] == NULL)           // check if index/head has no linked list
        {
            table[index] = new_word;        // place new_word into index/head location
        }
        else
        {
            new_word->next = table[index];  // new_word's pointer set to point to whatever index/head is pointing to
            table[index] = new_word;        // index/head is now replaced with new_word node
        }
        word_count++;
    }
    fclose(file);
    return true;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
// sum ascii values in lowercase % 26
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum = sum + tolower(word[i]);
    }
    return (sum % N);
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
// kept track of wordcount in load()
    return word_count;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // take the word and hash using hash()
    int index = hash(word);
    // create cursor node that has same values as index/head (start of table)
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)    //look at cursor.word, compare to word (in book)
        {
            return true;
        }
        cursor = cursor->next;              // set cursor node equal to the next node (such as index.next)
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
//  use while loop to go through each array line until NULL
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;              // move cursor firward
            free(tmp);                          // free tmp
            tmp = cursor;                       // move temp over to cursor
        }
    }
    return true;
}
