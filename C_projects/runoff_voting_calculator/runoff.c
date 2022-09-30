#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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
}
candidate;

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
        candidates[i].name = argv[i + 1];           // populate array with names inputted
        candidates[i].votes = 0;                    // set each candidate to 0
        candidates[i].eliminated = false;           // set each candidate elimiantion to be false
    }

    voter_count = get_int("Number of voters: ");    // get number of voters to max of 100
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)                       // loop over each voter
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)               // loop through each candidate
        {
            string name = get_string("Rank %i: ", j + 1);       // ask for rank 1, 2, 3... up to the max candidates

            // Record vote, unless it's invalid
            if (!vote(i, j, name))                              // check if names are valid (also keeps track of all of the preferences.)
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");                                           // print new line after each input
    }

    // this one’s going to keep looping through the runoff process of checking for a winner
    // and eliminating the last place candidate until there is a winner
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();                                             // execute tabulate

        // Check if election has been won
        bool won = print_winner();                              // execute print_winner
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();                                   // execute find_min to find candidate with fewest votes
        bool tie = is_tie(min);                                 // execute is_tie using the minimum vote count to eliminate tied losers

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)           // loop through each candidate
            {
                if (!candidates[i].eliminated)                  // if the candidates[i].eliminated = false  then print the candidates
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);                                         // run elimiante function to kill off the losers

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}








// Record preference if vote is valid
bool vote(int voter, int rank, string name)                 // grab the voterID, the rank and name JUST INPUTTED
{
    for (int i = 0; i < candidate_count; i++)               // loop through the lsit of candidate names
    {
        if (strcmp(name, candidates[i].name) == 0)          // if the voter's input name matches the candidate name at positon i
        {
            preferences[voter][rank] = i;                   // this i'th voters preference for rank j is the index of candidate
            return true;
        }
    }
    return false;
}




// Tabulate votes for non-eliminated candidates
// should look at all of the voters’ preferences and compute the current vote totals
// by looking at each voter’s top choice candidate who hasn’t yet been eliminated
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;                  //add a vote for every voters Rank #1 candidate
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
// should print out the winner if there is one; if there is, the program is over.
// But otherwise, the program needs to determine the fewest number of votes anyone
// still in the election received (via a call to find_min).
//      If any candidate has more than half of the vote, their name should be printed to stdout and the function should return true.
//      If nobody has won the election yet, the function should return false.
bool print_winner(void)
{
    float majority = (float)voter_count / 2;
    for (int j = 0; j < candidate_count; j++)
    {
        if (!candidates[j].eliminated && (float)candidates[j].votes > majority)
        {
            printf("Winner by Majority = %s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}



// Return true if the election is tied between all candidates, false otherwise
// finds out if everyone in the election is tied with the same number of votes
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
// if no all-out tie,
// then the last-place candidate (or candidates) is eliminated from the election via a call to the eliminate function.
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}