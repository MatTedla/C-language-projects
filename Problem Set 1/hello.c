// user inputs name, outputs greeting

#include <cs50.h>
#include <stdio.h>

// Asks for input, then prints Hello followed by input
int main(void)
{
    string answer = get_string(" ");
    printf("Hello, %s\n", answer);
}
