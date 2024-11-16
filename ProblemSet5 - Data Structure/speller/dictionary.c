// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare variables
unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //
    // Calculate the hash value for the input word using a hash function
    hash_value = hash(word);

    // Start a pointer 'cursor' to move through the linked list at the index of the calculated hash value
    node *cursor = table[hash_value];

    // Loop through each node in the linked list until we reach the end (cursor becomes NULL)
    while (cursor != 0)
    {
        // Compare the input word with the current node's word, ignoring case differences
        if (strcasecmp(word, cursor->word) == 0)
        {
            // If a match is found, return true indicating that the word exists in the hash table
            return true;
        }
        // Move to the next node in the linked list
        cursor = cursor->next;
    }
    // If no match is found after checking all nodes, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // Convert the current character to lowercase and add its ASCII value to 'total'
        total = total + tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // 1st Open dictionary
    FILE *file = fopen(dictionary, "r");

    // Check if the file was successfully opened
    if (file == NULL)
    {
        // If fopen returned NULL, it indicates that the file could not be opened.
        // Print an error message to inform the user about the failure.
        printf("Unable to open %s\n", dictionary);

        return false; // Return false to indicate that the operation was unsuccessful.
    }

    // Declare variable called word
    char word[LENGTH + 1];

    // Start a loop that continues as long as fscanf successfully reads a string from the file
    // The fscanf function attempts to read a string from 'file' and store it in 'word'
    // If it reaches the end of the file (EOF), the loop will terminate
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate memory for a new node of type 'node'
        node *n = malloc(sizeof(node));

        // If mallock return NULL, return false
        if (n == NULL) // Check if the memory allocation was successful
        {
            return false; // If allocation failed, return false to indicate failure
        }

        // Copy word from dictionary into node
        strcpy(n->word, word);
        hash_value = hash(word);
        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++; // Tracks how many words have been successfully added to the hash table
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // Check if there is at least one word counted
    if (word_count > 0)
    {
        // If word_count is greater than zero, return the current count of words.
        return word_count;
    }
    // If no words are counted, return 0 indicating an empty state.
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Loop through each index of the hash table, which has N slots.
    for (int i = 0; i < N; i++)
    {
        // Initialize a cursor to point to the head of the linked list at index i
        node *cursor = table[i];
        // Go through the linked list until there are no more nodes (cursor is NULL).
        while (cursor)
        {
            // Store the current node in a temporary variable before moving to the next node
            node *tmp = cursor;

            // Move cursor to the next node in the linked list.
            cursor = cursor->next;

            // Free the memory allocated for the current node.
            free(tmp);
        }
        // Check if we are at the last index and if cursor is NULL (indicating all nodes were freed)
        if (i == N - 1 && cursor == NULL)
        {
            return true; // Return true indicating successful unloading of nodes.
        }
    }
    // Return false if unloading was not successful (this line may never be reached)
    return false;
}
