#include <stdio.h>

#define LENGTH 4096

// Exercise 1-22. Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly.

int main(int argc, char const *argv[])
{

    int i = 0;
    int c;
    int counter = 0;
    char filea_cache[LENGTH];
    char filec_cache[LENGTH];
    FILE *filea;
    FILE *fileb;
    FILE *filec;


    filea = fopen(argv[1], "r");
    fileb = fopen("datei-unmodified.txt", "w");
    filec = fopen(argv[2], "w");

    // reading source file
    if (filea)
    {
        while ((c = getc(filea)) != EOF)
        {
            filea_cache[counter] = c;
            fprintf(fileb, "%c", c);
            counter++;
        }
        filea_cache[counter] = '\0';
    }
    counter = 0;
    //printf("filea_cache before modifications:\n%s\n", filea_cache);

    int counter_c = 0, in_comment = 0, in_string = 0;
    // modifying the cache
    while (((c = filea_cache[counter]) != '\0'))
    {
        if ((c = filea_cache[counter]) == '"' && in_string == 0)
        {
            in_string = 1;
            filec_cache[counter_c++] = '"';
            counter++;
        }
        if (((c = filea_cache[counter]) == '"' && in_string == 1))
        {
            in_string = 0;
        }

        // single line comment remover
        if ((filea_cache[counter] == '/') && (filea_cache[counter + 1] == '/') && (in_string == 0))
        {
            in_comment = 1;
            while (in_comment)
            {
                if ((c = filea_cache[counter]) == '\n')
                {
                    in_comment = 0;
                }

                counter++;
            }
            filec_cache[counter_c - 1] = '\n';
        }

        // multi line comment remover
        if ((filea_cache[counter] == '/') && (filea_cache[counter + 1] == '*') && (in_string == 0))
        {
            in_comment = 1;
            while (in_comment)
            {
                if (filea_cache[counter] == '*' && filea_cache[counter + 1] == '/')
                {
                    in_comment = 0;
                    counter++;
                }

                counter++;
            }
        }

        filec_cache[counter_c] = filea_cache[counter];

        counter_c++;
        counter++;
    }
    filec_cache[counter_c] = '\0';
    counter = 0;
    //printf("filec_cache after modifications:\n%s", filec_cache);

    // writing into output file
    while (((c = filec_cache[counter]) != '\0'))
    {
        fprintf(filec, "%c", c);
        counter++;
    }
    printf("file: %s created\n", argv[2]);
    fclose(filea);
    fclose(fileb);
    fclose(filec);
    return 0;
}