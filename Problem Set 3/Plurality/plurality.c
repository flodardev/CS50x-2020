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
}
candidate;

// Array of candidates
candidate candidates[MAX];

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
{
    // TODO
    int i = 0;
    for (i = 0; i <= candidate_count; i++)
    {
        if (i == candidate_count) // return false if screen through all strings if non is matched
        {
            return false;
        }
        if (strcmp(name, candidates[i].name) == 0 && i != candidate_count) // return true and add 1 to votes
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false; // if nothing happens then return false
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int vote = candidates[0].votes; // initialized as the first name's vote score
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > vote) //compares it to the adjacent value
        {
            vote = candidates[i].votes; //if adjacent value is higher, assign it to vote. it will be the new highest vote and recompare
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == vote) // identifies which candidates with the same amount of votes;
        {
            printf("%s\n", candidates[i].name);  //print all or one
        }
    }
}