#include <stdio.h>
#include <cs50.h>

int pyramid_height(void);

int main(void)
{
    const int n = pyramid_height();
    int width = n * 2 + 2;

    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == n || x == n + 1)
            {
                printf(" ");
            }
            else if (y + n + 2 < x)
            {
                printf(".");
            }
            else if (y + x < n - 1)
            {
                printf(".");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

int pyramid_height(void)
{
    int n;
    do
    {
        n = get_int("Pyramid height: ");
    }
    while (n < 1 || n > 8);
    return (n);
}