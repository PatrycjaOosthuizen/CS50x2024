#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX], swap[0];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{    // TODO
    // Loop through all candidates to find a match with the provided name
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare the current candidate's name with the input name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If a match is found, add the vote count for that candidate
            candidates[i].votes++;
            return true; // Return true indicating the vote was successfully counted
        }
    }
    // If no matching candidate is found, return false indicating failure to count the vote
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Sort candidates based on their vote counts using a bubble sort algorithm
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - i - 1; j++) // Inner loop for comparing candidates
        {
            // If the current candidate has fewer votes than the next candidate, swap them
            if (candidates[j].votes < candidates[j + 1].votes)
            {
                swap[0] = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = swap[0];
            }
        }
    }
    // Print candidates with max votes
    int i = 0;
    // Print the name of the first candidate with max votes
    do
    {
        printf("%s\n", candidates[i].name); // Output the name of the candidate at index i
        i++; // Move to the next candidate in the sorted list
    }
    // Continue printing while there are more candidates with identical max votes
    while (candidates[i].votes == candidates[i - 1].votes);
}
