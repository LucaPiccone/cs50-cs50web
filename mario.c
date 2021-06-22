#include <cs50.h>
#include <stdio.h>

// Declare new function at top of page
int get_pyramid_height(void);

int main(void)
{
    // Promp user for height of pyramid.
    int n = get_pyramid_height();

    // Print # everytime i or j is less then n.
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)

            // Pyramid conditions.
            if (y + x < n - 1)
               
            printf(" ");

            else
            
            printf("#");

        printf("\n");
    }
}

// Create new function
int get_pyramid_height(void)
{
    // Function will return input to user if n is less than 1 or greator than 8
    int n;
    do
    {
        n = get_int("Pryamid Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}