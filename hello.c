#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //user name input 
    string answer = get_string("What's your name? ");
    //print hello user's name
    printf("Hello, %s\n", answer);
}