#include <cs50.h>
#include <stdio.h>

void stairs(int n);

int main(void)
{
    int height;
    int h;
    int n;
    int r;
    int x;
    // get the height

    do
    height = get_int("Height (1-8): ");
    while (height <= 1 || height >= 8);

    // ignore the rest BOOM RECURSIVE FUNCTION
    // stairs(height);
    // return 0;
    // calculate and print pyramid
    for (r = height; r > 0; r--)
    {
        for (n = r - 1; n > 0; n--)
        {
            printf(" ");
        }
        for (h = r - n - 1; h < height; h++)
        {
            printf("#");
        }
        printf("  ");
        for (x = r - n - 1; x < height; x++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// recursion??
void stairs(int n)
{
    if (n <= 0)
    {
        return;
    }
    stairs(n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}
