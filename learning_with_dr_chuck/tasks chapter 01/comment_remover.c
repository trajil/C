#include <stdio.h>

#define LENGTH 4096

// Exercise 1-22. Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly.

int main(int argc, char const *argv[])
{
    int i = 0;
    int c, counter = 0;
    char filea_cache[LENGTH];
    FILE *filea;
    FILE *fileb;

    filea = fopen("test.txt", "r");
    fileb = fopen("test-output.txt", "w");

    if (filea)
    {
        counter = 0;
        // filling internal char array
        while ((c = getc(filea)) != EOF)
        {
            filea_cache[counter] = c;
            counter++;
        }
        filea_cache[counter] = '\0';
        printf("output:%s", filea_cache);
    }

    while ((c = getc(filea_cache)) != EOF)
    {

        fprintf(fileb, "TEST");
    }
    fprintf(fileb, "\0");

    fclose(filea);
    fclose(fileb);
    return 0;
}