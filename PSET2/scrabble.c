#include <cs50.h>
#include <stdio.h>
#include <string.h>

int get_score(char x);

int main(void)
{
    string word[2];
    int score[2] = {0, 0};
    // ask player 1
    word[0] = get_string("gimme your word player 1: ");

    // ask player 2
    word[1] = get_string("gimme your word player 2: ");

    // calculate score
    for (int p = 0, step = 0; p < 2; p++, step++)
    {
        for (int i = 0, playertotalscore = score[step], length = strlen(word[step]); i < length; i++)
        {
            score[step] = score[step] + get_score(word[step][i]);
        }
    }
    // TODO: decide who wins
    if (score[0] == score[1])
    {
        printf("Tie!\n");
    }
    else if (score[0] > score[1])
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int get_score(char x)
{
    int points = 0;
    if ((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A'))
    {
        if (x <= 'z' && x >= 'a')
        {
            x = x - 32;
        }
        points = 1;
        if (x == 'D' || x == 'G')
        {
            points = 2;
        }
        if (x == 'B' || x == 'C' || x == 'M' || x == 'P')
        {
            points = 3;
        }
        if (x == 'F' || x == 'H' || x == 'V' || x == 'W' || x == 'Y')
        {
            points = 4;
        }
        if (x == 'K')
        {
            points = 5;
        }
        if (x == 'J' || x == 'X')
        {
            points = 8;
        }
        if (x == 'Q' || x == 'Z')
        {
            points = 10;
        }
    }
    return points;
}
