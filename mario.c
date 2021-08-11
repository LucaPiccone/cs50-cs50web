#include <cs50.h>
#include <stdio.h>
// Declare new function at top of page.
int get_pyramid_height(void);

int main(void)
{
    //Prompt user for height of pyramid.
    int n = get_pyramid_height();
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n * 2 + 2; x++)
        {
            //Pyramid condtions
            if (y + x < n - 1)
            {
                printf(" ");
            }
            else if (y + n + 2 < x)
            {
                printf(" ");
            }
            else if (x == n || x == n + 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
    printf("\n");
    }
}

// Create new function.
int get_pyramid_height(void)

    // Function will return input to user if n is less than 1 or greator than 8
{
    int n;
    do
    {
        n = get_int("Pyramid Height? ");
    }
        while (n < 1 || n > 8);
        return n;
}