#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    // Loop through all candidates to find a match with the provided name
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare the current candidate's name with the input name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If a match is found, record the candidate's index in preferences
            preferences[voter][rank] = i;
            // Indicate that the vote was successfully recorded
            return true;
        }
    }
    // If no matching candidate was found, return false indicating an invalid vote
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // Iterate over each voter to count their votes
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate over each candidate to find the voter's preference
        for (int j = 0; j < candidate_count; j++)
        {
            // Get the index of the candidate that the current voter prefers
            int vote = preferences[i][j];

            // Check if the preferred candidate has not been eliminated
            if (candidates[vote].eliminated == false)
            {
                // Increment the vote count for this candidate
                candidates[vote].votes++;
                // Break out of the inner loop since we only want to count one vote per voter
                break;
            }
        }
    }
     // End of function, no return value needed as it is a void function
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // Loop through all candidates based on the number of voters
    for (int i = 0; i < voter_count; i++)
    {
        // Check if the current candidate has more than half of the total votes
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // If no candidate has more than half of the votes, return false indicating no winner
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // Set minimum votes to first candidates votes
    int min_votes = candidates[0].votes;

    for (int i = 0; i < candidate_count; i++)
    {
        // If candidates has less votes, then update min_votes
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // Initialize a counter for running candidates who are not eliminated
    int running_candidates = 0;
    // Initialize a counter for candidates who have votes equal to the minimum votes
    int tie_votes = 0;
    // Loop through all candidates to count those still in the race and those with tie votes
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is still running (not eliminated)
        if (candidates[i].eliminated == false)
            running_candidates++;
        // Check if the candidate's vote count equals the minimum vote count passed to the function
        if (candidates[i].votes == min)
            tie_votes++;
    }
    // If the number of running candidates equals the number of candidates with tie votes, return true
    if (running_candidates == tie_votes)
        return true;
  // If not all running candidates have tie votes, return false
  return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    // Loop through all candidates to check their vote counts
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the current candidate is not already eliminated
        if (candidates[i].eliminated == false)
        // If the candidate's vote count matches the minimum, eliminate them
          if (candidates[i].votes == min)
              candidates[i].eliminated = true;
    }
    // Exit the function after processing all candidates
    return;
}
