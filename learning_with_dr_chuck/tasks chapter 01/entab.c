#include <stdio.h>
#define LENGTH 100
#define TABL 4

// Exercise 1-20. Write the program entab which replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
void move_in_chararray(int from, int positions, char text[], int length);
int main(int argc, char const *argv[])
{
    // static char text[LENGTH];
    char c;
    int i = 0, j = 0, tabs = 0, whitespaces = 0, counter = 0;
    // while ((c = getchar()) != EOF && i < LENGTH)
    // {

    //     text[i] = c;
    //     i++;
    // }
    // text[i] = '\0';
    // int string_length = i + 1;
    // i = 0;
    static char text[LENGTH] = {
        'T',
        'h',
        'i',
        's',
        ' ',
        ' ',
        ' ',
        'i',
        's',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        'v',
        'e',
        'r',
        'y',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        ' ',
        'h',
        'a',
        'r',
        'd',
        '\0'};

    printf("text_array:~%s\n", text);

    while (i < LENGTH && text[i] != '\0')
    {

        if (text[i] == ' ' && j == 0)
        {
            j = i;
        }
        if (text[i] != ' ' && (j != 0) && (i - j <= TABL))
        {
            j = counter = 0;
        }
        if (text[i] != ' ' && (j != 0) && (i - j > TABL))
        {
            counter = i - j;
            tabs = counter / TABL;
            whitespaces = counter % TABL;
            int places_to_shift = tabs * (TABL - 1);
            for (size_t i = 0; i < tabs; i++)
            {
                text[j] = '\t';
                j++;
            }
            for (size_t i = 0; i < whitespaces; i++)
            {
                text[j] = '_';
                j++;
            }
            if (tabs > 0)
            {
                move_in_chararray(j, places_to_shift, text, LENGTH);
            }

            j = counter = 0;
        }
        i++;
    }

    printf("text_after:~%s", text);
    return 0;
}

void move_in_chararray(int from, int positions, char text[], int length)
{
    char temp_array[LENGTH];

    for (size_t k = 0; k < length; k++)
    {
        temp_array[k] = text[k];
    }

    for (size_t n = length - 1; n > (from + positions - 1); n--)
    {
        temp_array[n - positions] = text[n];
    }
    printf("temp_array:~%s\n", temp_array);

    for (from = 0; from < length; from++)
    {
        text[from] = temp_array[from];
    }
    printf("text_array:~%s\n", text);
};