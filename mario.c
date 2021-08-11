#include <stdio.h>
#include <cs50.h>

int pyramid_height(void);


int main(void)
{
    const int n = pyramid_height();
    int width = n * 2 + 2;

    for (int y = 0; y <= n - 1; y++)
    {
        for (int x = 0; x <= width; x++)
        {
            if (y + n + 3 < x)
            {
                printf("%c", ' ');
            }
            else if (x == n + 1 || x == n + 2)
            {
                printf("%c", ' ');
            }
            else if ( x + y > n - 1)
            {
                printf("%c", '#');
            }

            else if (x < y)
            {
                printf("%c", ' ');
            }

            else
            {
                printf("%c", ' ');
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