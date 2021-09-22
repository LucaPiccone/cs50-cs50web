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
void swap(int *x, int *y);
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

        // TEST THIS - Print 2d array Stored preferences
        // for (int s = 0; s < voter_count; s++)
        // {
        //     for (int t = 0; t < candidate_count; t++)
        //     {
        //         printf("%i", preferences[s][t]);
        //     }
        //     printf("\n");
        // }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // TEST - PRINT EACH CANDIDATES.VOTES
        // for (int j = 0; j < candidate_count; j++)
        // {
        //      printf("%i\n", candidates[j].votes);
        // }

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }


        // Eliminate last-place candidates
        int min = find_min();

        // TEST - PRINT THE MIN CANDIDATES.VOTES
        // printf("This is min: %i\n", min);

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
    // Compare name with candidates.name options
    for (int i = 0; i < candidate_count; i++)
    {
        // if the voters name matches one of the candidates.
        if (candidates[i].eliminated == 0)
        {
            if (strcmp(name, candidates[i].name) == 0)
            {
                // for voter 1; if rank 1 == candidate[i].name, return true, therefore store i inside [1][1] or else strcmp fails return false.
                preferences[voter][rank] = i;
                return true;
            }
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][0] == j)
            {
                if (candidates[j].eliminated == false)
                {
                    candidates[j].votes += 1;
                }
                else
                {
                    for (int k = 0; k < candidate_count; k++)
                    {
                        if (preferences[i][1] == k && candidates[k].eliminated == false)
                        {
                            candidates[k].votes += 1;
                        }
                    }
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO

    int n = candidate_count;
    int v = voter_count;
    float mid = (v / 2.0);

    // TEST this
    // printf("This is mid: %f\n", mid);

    for (int i = 0; i < n; i++)
    {
        // If a candidate has more than 50% of votes
        if (candidates[i].votes > mid)
        {
            // Candidate wins.
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// A swap function for sorting algorithms.
void swap(int *x, int *y)
{
    int temporary = *x;
    *x = *y;
    *y = temporary;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int n = candidate_count;
    int points[n];
    for (int i = 0; i < n; i++)
    {
        // Copy all candidates votes into a points array
        points[i] = candidates[i].votes;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Selection sort the points array from smallest to biggest
            if (points[i] > points[j])
            {
                swap(&points[i], &points[j]);
            }
        }
    }
    
    // TEST 
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     printf("Min array: %i", points[i]);
    // }
    
    int min;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // check if smalled number is the same of candidates[i].votes
            if (points[i] == candidates[j].votes)
            {
                // Check if the candidate is not already eliminated
                if (candidates[j].eliminated == false)
                {
                    min = candidates[j].votes;
                    return min;
                }
            }   
        }
    }
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int check_tie = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidates[i].votes is the same as min, add one to check_tie
        if (candidates[i].votes == min)
        {
            check_tie += 1;
        }
        // if check tie is the same number of all candidates.
        if (check_tie == candidate_count)
        {
            return true;
        }
    }
    
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If candidates votes is the minimum number of voters eliminate candidate.
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
            // TEST - If candidate was successfully eliminated.
            // if (candidates[i].eliminated == true)
            // {
            //     printf("Candidate %s was elimanted\n", candidates[i].name);
            // }
        }
    }
    return;
}
