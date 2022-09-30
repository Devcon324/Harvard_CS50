#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9                       // set global max variable of 9

typedef struct                      // create struct of candidates = name + votes
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];          // create array of stuct candidates
int candidate_count;                // ceat global empy int of candidate counts

bool vote(string name);             // reference the vote function
void print_winner(void);            // reference the ptrint function

int main(int argc, string argv[])                           // main program
{
    // Check for invalid usage
    if (argc < 2)                                           // if user has less than 2 ArgC's
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;                             // count how many candidates were in the input
    if (candidate_count > MAX)                              // if user inputs more than 9 (MAX variable) candidates
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)               // loop through the candidate array candidate_count times
    {
        candidates[i].name = argv[i + 1];                   // fills array with candidate names
        candidates[i].votes = 0;                            // gives each candidate score of 0 to start
    }

    int voter_count = get_int("Number of voters: ");        // get input from user of number of voting persons

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)                   // loop through each voter and ask for the name they vote for
    {
        string name = get_string("Vote: ");                 // get string of name each voter inputs

        // Check for invalid vote
        if (!vote(name))                                    // calls function bellow to use strcmp to deliver bool if name is present or not
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();                                         // calls function to sort the votes + search for winner('s)
}

// function
// Validates the inputted name form a voter
// Updates that candidate’s vote total
bool vote(string name)
{

    for (int i = 0; i < candidate_count; i++)               // loop through
    {
        if (strcmp(name, candidates[i].name) == 0)          // if the voter's input name matches the candidate name at positon i
        {
            candidates[i].votes++;                          // increase vote by 1
            return true;                                    // return true (the voter input a valid name)
        }
    }
    return false;                                           // if the loop finished without returning true, then return false
}



// Function
// sort the array from small to large
// search for winner or winners
// Print the winner (or winners) of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count - 1; i++)               // loop through the i position in array
    {
        int min_ID = i;                                         // set the current minimum to position i
        for (int j = i + 1; j < candidate_count; j++)           // loop throught the i + 1 position in the array
        {
            if (candidates[j].votes < candidates[min_ID].votes) // is position i+1 less than position i?
            {
                min_ID = j;                                     // yes = change minimum to positon i+1
            }
        }
        // swap i with i+1 and i+1 with i
        candidate temp = candidates[min_ID];                    // save i+1 for swapping
        candidates[min_ID] = candidates[i];                     // swap i+1 with i
        candidates[i] = temp;                                   // swap i with i+1 (saved)
    }

    printf("%s\n", candidates[candidate_count - 1].name);       // print the last element of the array (the largest vote)
    for (int k = 0; k < candidate_count - 1; k++)               // loop through entire array (now sorted small to large)
    {
        if (candidates[k].votes == candidates[candidate_count - 1].votes)   // if the k'th element ties with the last/largest element
        {
            printf("%s\n", candidates[k].name);                 // print the k'th element name if it ties with alrgest element
        }
    }
    return;
}