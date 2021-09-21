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

    // DELETE THIS - Print 2d array Stored preferences
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

        // DELETE THIS - PRINT EACH CANDIDATES.VOTES
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

        // DELETE THIS - PRINT THE MIN CANDIDATES.VOTES
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
        if (strcmp(name, candidates[i].name) == 0)
        {
            // for voter 1; if rank 1 == candidate[i].name, return true, therefore store i inside [1][1] or else strcmp fails return false.   
            preferences[voter][rank] = i;
            return true;
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
            // Increase candidates votes by 1 if they're the rankers first preference.
            if (preferences[i][0] == j)
            {
                candidates[j].votes += 1;
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
    int points[n];
    for (int i = 0; i < n; i++)
    {
        // If candidate is not eliminated copy candidates votes into the points array.
        if (candidates[i].eliminated == false)
            points[i] = candidates[i].votes;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Selection sort the points array from smallest to biggest.
            if (points[i] < points[j])
                continue;
            else
            {
                swap(&points[i], &points[j]);
            }
        }
    }

    int winner;
    for (int i = 0; i < n; i++)
    {
        // If candidates vote is more then half the voters. Print winner. 
        if (candidates[i].votes > (v - 1) / 2)
        {
           winner = points[n - 1];
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (winner == candidates[i].votes)
        {
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
        if (candidates[i].eliminated == false)
            points[i] = candidates[i].votes;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Selection sort the points array from smallest to biggest
            if (points[i] < points[j])
                continue;
            else
            {
                swap(&points[i], &points[j]);
            }
        }
    }

    int min;
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate is not eliminated already. Store the smallest number of votes a candidate has in min.
        if (candidates[i].eliminated == false)
        {
            min = points[i];
            return min;
        }
    }

    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[i].votes == candidates[j].votes)
            {
                return true;
            }
        }
    }
    
    // int n = candidate_count;
    // for (int i = 0; i < n; i++)
    // {
    //     // If the candidates votes match the minimun number of votes, eliminate them.
    //     if (candidates[i].votes == min)
    //     {
    //         candidates[i].eliminated = true;
    //     }
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     // If the candidates votes is not minimum
    //     if (candidates[i].votes != min)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {   
    //             // 
    //             if (candidates[i].votes == candidates[j].votes)
    //             {
    //                 if (j != i)
    //                 return true;
    //             }
    //         }
    //     }
    // }
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
        }
    }
    return;
}
