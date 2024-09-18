#include <stdio.h>
#define LENGTH 100
#define TABL 4

// Exercise 1-19. Write a program detab which replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n positions.

int main(int argc, char const *argv[])
{
    char text[LENGTH];
    char c;
    int counter = 0;

    while ((c = getchar()) != EOF && counter <= LENGTH)
    {
        if (c == '\t')
        {
            for (size_t i = 0; i < TABL; i++)
            {
                text[counter] = 't';
                counter++;
            }
        }

        else
        {
            {
                text[counter] = c;
                counter++;
            }
        }
    }
    counter = 0;
    printf("text before clearing: %s", text);

    return 0;
}