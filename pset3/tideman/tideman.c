#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];
bool lock = true;

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

int pair_count;
int candidate_count;

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
    int voter_count = get_int("Number of voters: ");

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
    //Looping through candidates to see if vote is valid/
    for (int i = 0; i < candidate_count; i++)
    {
        //If the vote is valid record the rank in the ranks array
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Looping through ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        //Looping a second time through the ranks array to compare the preferences
        for (int j = 0; j < candidate_count; j++)
        {
            //If the candidate ranks after the current rank then add one for the ith candidate
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }
    // TODO
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Loop through the rows of the preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        //Loop throught the columns of the preferences array
        for (int j = i + 1; j < candidate_count; j++)
        {
            //If candidate i has more votes than candidate j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }

            //If candidate j has more votes than candidate i
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    // TODO
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //Loop through the pairs array
    for (int i = 0; i < pair_count - 1; i++)
    {
        //Loop over the pairs array once more
        for (int j = 0; j < pair_count - 1 ; j++)
        {
            //if the margin is smaller then swap with the j + 1 pair
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        printf("pairs: %i\n", pairs[i].winner);
        printf("pairs: %i\n", pairs[i].loser);
    }
    // TODO
    return;
}

//Function that is used
bool check_cycle_helper(int i, bool node[])
{
    //Base case
    if (node[i])
    {
        return true;
    }

    node[i] = true;

    //Loops through matrix and verifies if the candidate has been visited already
    for (int j = 0; j < candidate_count; j++)
    {
        //If condition is true, a cycle is created and the lock should be set to false
        if (locked[i][j] && check_cycle_helper(j, node))
        {
            return true;
        }
    }
    return false;
}

//Method that verifies if a cycle is created for a given pair and returns a boolean
bool check_cycle(int i)
{
    bool node[candidate_count];

    //Loop through the node array and set values to false meaning they have not been visited
    for (int j = 0; j < candidate_count; j++)
    {
        node[j] = false;
    }
    return check_cycle_helper(pairs[i].winner, node);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Loop through the pairs array and set the edge in the locked array
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        //Verify if a cycle is created after setting the edge
        if (check_cycle(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

    }
}


// Print the winner of the election
void print_winner(void)
{
    bool winner = true;
    int index;

    //Loop through the rows of the locked array
    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;

        //Loop through the columns of the locked array
        for (int j = 0; j < candidate_count; j++)
        {
            //If the locked array has true in the ith column the ith candidate is not the winner
            if (locked[j][i])
            {
                winner = false;
                break;
            }
        }
        //Setting the winner's index
        if (winner)
        {
            index = i;
            break;
        }
    }
    //Print the winner's name;
    if (winner)
    {
        printf("%s\n", candidates[index]);
    }

    // TODO
    return;
}

