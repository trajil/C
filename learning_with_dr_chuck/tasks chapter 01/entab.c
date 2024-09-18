#include <stdio.h>
#define LENGTH 50
#define TABL 4

// Exercise 1-20. Write the program entab which replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.

int main(int argc, char const *argv[])
{
    char text[LENGTH];
    char c;
    int counter = 0;

    while ((c = getchar()) != EOF && counter <= LENGTH)
    {

        text[counter] = c;
        counter++;
    }
    counter = 0;
    printf("text before modifications: \n%s\n", text);
    int counter_blank = counter;

    // blank_space_remover
    while (counter < LENGTH)
    {
        printf("counter: [%d] : [%c]\n", counter, text[counter]);

        if (text[counter] != ' ' && counter != counter_blank)
        {
            for (size_t i = counter_blank; i < counter - TABL; i = i + TABL)
            {
                for (size_t j = 0; i < TABL; j++)
                {
                    text[i + j] = '-';
                }

                counter_blank = i;
            }
            for (size_t i = counter_blank; i < counter; i++)
            {

                text[i] = '-';

                counter_blank = i;
            }
        }

        else
        {
            counter_blank = counter + 1;
        }

        // T T _ _ _ _ _ 5
        counter++;
    }

    printf("text after modifications: \n%s", text);
    return 0;
}
