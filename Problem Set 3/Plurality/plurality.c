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
    int counter = 1;
    
    // checks if the string input matches any of the candidates; if yes, then add 1 vote
    for (int i = 0; i < candidate_count; i++)
    {
        int check = strcmp(candidates[i].name, name);
        if (check == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            counter = 0;
            break;
        }
        else if (i + 1 == candidate_count)
        {
            break;
        }
    }
    
    // if we get a valid vote (represented by "counter" equaling zero), we return true; if not, return false
    if (counter == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    static int winner[10];
    winner[0] = 0;
    winner[1] = '\0';
    winner[2] = '\0';
    winner[3] = '\0';
    winner[4] = '\0';
    winner[5] = '\0';
    winner[6] = '\0';
    winner[7] = '\0';
    winner[8] = '\0';
    winner[9] = '\0';

    int winner_count = 1;

    for (int i = 0; i < candidate_count; i++)
    {
        // checks if this is NOT the first candidate
        if (i != 0)
        {
            // checks if the current candidate (i) has a greater number of votes than the previous candidate (i-1)
            if (candidates[i].votes > candidates[i - 1].votes)
            {
                winner[0] = i;
                winner_count = 1;
            }
            // checks if the current candidate has the same number of votes as the previous candidate
            else if (candidates[i].votes == candidates[i - 1].votes)
            {
                // checking available "winner" slots; the # of slots to check is the same as the # of candidates
                // if current "winner" slot holds the previous candidate; the next  "winner" slot will hold the current candidate
                for (int j = 0; j < candidate_count; j++)
                {
                    if (winner[j] == i - 1)
                    {
                        winner[j + 1] = i;
                    }
                }
                winner_count += 1;
            }
        }

    }
    // prints out all the winners based on the winner count
    for (int k = 0; k < winner_count; k++)
    {
        printf("%s\n", candidates[winner[k]].name);
    }
}

