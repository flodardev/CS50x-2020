#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
// pair pairs is for pairs only. It is possible to create another array of struct by just pair "newname"

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == candidate_count)  // if scanned through and nothing matches then return false
        {
            return false;
        }
        if (strcmp(candidates[i], name) == 0) // if name is found in candidates[i]array then
        {
            ranks[rank] = i; // ranks[ranknumber starting from '0'] is candidate i
            //printf("%i\n", ranks[rank]); //debugger
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int j = 0; j < candidate_count; j++) // candidate 1 compared to candidate 2
    {
        if (j != candidate_count - 1)
        {
            for (int k = 1; k < candidate_count; k++)
            {
                if (j != k && j != 2)
                {
                    preferences[ranks[j]][ranks[k]] += 1;
                    //printf("%i\n", preferences[ranks[j]][ranks[k]]);  // debugger
                }
                if (j >= 2 && j < k)
                {
                    preferences[ranks[j]][ranks[k]] += 1;
                    //printf("%i\n", preferences[ranks[j]][ranks[k]]);  // debugger
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++) //candidate 1
    {
        for (int j = 1; j < candidate_count; j++) //candidate 2
        {
            if (preferences[i][j] > preferences[j][i]) //only choose the pair with the highest preferences
            {
                pairs[pair_count].winner = i; //update winner from preferences
                pairs[pair_count].loser = j; //update lose from preferences
                pair_count += 1; //update pair count to the next pair
                //printf("Pair Winner:%i\n Pair Loser:%i\n", pairs[pair_count].winner, pairs[pair_count].loser);
            }
        }
    }
    //printf("Pair count:%i\n", pair_count); //debugger
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 1; j < pair_count - i; j++) // loop through remaining pair_count
        {
            //if pairs[i] has less votes/preferences than pairs[j] then swap
            if (preferences[pairs[i].winner][pairs[i].loser] < (preferences[pairs[j].winner][pairs[j].loser]))
            {
                pair temp = pairs[i]; //create a temp for pair then assign that temp with pair pairs[i]
                pairs[i] = pairs[j]; //pairs j assigned to pair i
                pairs[j] = temp; // pair temp assigned to pair pairs[j], inherently swapping the value
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // locked[i][j] means i is locked in over j
    // bool locked[MAX][MAX];
    locked[pairs[0].winner][pairs[0].loser] = true; //pair[0] will be locked
    //printf("winner:%s\n", candidates[pairs[0].winner]); // debugger
    //printf("loser:%s\n", candidates[pairs[0].loser]); // debugger
    for (int i = 1; i < pair_count; i++)
    {
        bool cycle = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[pairs[i].loser][j])// loser lock over anything skipped, starting for pairs[1]
            {
                cycle = true;
                break;
            }
        }
        if (!cycle)// if pairs[i].loser wont lock over anything then lock pairs[i]
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("winner:%s\n", candidates[pairs[i].winner]);
            //printf("loser:%s\n", candidates[pairs[i].loser]);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int f = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[pairs[i].winner][pairs[i].loser] == false)
            {
                f++;
            }
            if (f >= pair_count) //candidates with false amount atleast the size of pair(meaning no locks) is the winner
            {
                printf("%s\n", candidates[i]);
                break;
            }
        }
    }
}
//notes to myself and reader
//runoff was relatively easy
//so i decided to challenged myself with tideman.c
//i always try the "more comfortable" sets because i would like to know how far can i solve it until i get really stuck
//also i would like to learn new things, algorithms, syntaxs, logic, etc
//so i did tideman and managed to solve until the sort function, which i was having a hard time trying to swap a struct array, i learned that for a struct i could just create another array for it like pair temp
//locking was imposibble to me, so i decided to research and i learned many things
//locking could also be done in recursive method which i will learn
//printing winners, i learned how to visualize graphs like rows and columns with a for loop
//first for loop are the "rows"
//second for loop  are the "columns"
//very useful in checking or comparing the cell's content