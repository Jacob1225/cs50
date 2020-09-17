// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];


// Hashes word to a number
//Hash function jdb2 by Dan Bernstein
int get_hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }

    return hash % N;
}

//Set global word counter
int wordCount = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *file = fopen(dictionary, "r");

    //Validate if null is returned from opening the file
    if (file == NULL)
    {
        return false;
    }

    //Nullify the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //Declare a string of length LENGTH + 1
    char new_word[LENGTH + 1];

    //Loop until we reach the end of the file/dictionary
    while (fscanf(file, "%s", new_word) != EOF)
    {
        //Create a new node
        node *new_node = malloc(sizeof(node));

        //Verify if node points to null
        if (new_node == NULL)
        {
            return false;
        }

        //Copy the string into the word field of the new node
        strcpy(new_node->word, new_word);

        //Finds where to insert the word into the hashtable with above hash function
        int index = get_hash(new_word);

        //Verify if hash table is empty
        if (table[index] == NULL)
        {
            new_node->next = NULL;
            table[index] = new_node;
        }
        //If there is already a head in the hash table
        else
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
        wordCount++;
    }

    //Close the file once we have reached the end
    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Create a copy of the word
    int n = strlen(word);
    char word_copy[LENGTH + 1];

    //Make the copied word lowercase
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[n] = '\0';

    //Get index of hash table to know where to look in table
    int index = get_hash(word_copy);

    //Create a node cursor to traverse the linked lists at index and find word
    node *cursor = table[index];

    //Loop over linked list until cursor is null meaning end of list
    while (cursor != NULL)
    {
        //Compare the value of the node->word and the word passed as an argument
        if (strcmp(cursor->word, word_copy) == 0)
        {
            return true;
        }

        //If word was not found set cursor to next node in the linked list
        cursor = cursor->next;

    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return wordCount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Loop over the hash table
    for (int i = 0; i < N; i++)
    {
        //Set a cursor to first node of the linked list at table index
        node *cursor = table[i];

        //Loop over list to free all memory allocation
        while (cursor != NULL)
        {
            //Create tmp node to be free'd
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        //Nullify table row
        table[i] = NULL;
    }

    return true;
}
