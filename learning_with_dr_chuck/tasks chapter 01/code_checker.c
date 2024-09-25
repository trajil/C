#include <stdio.h>

// Exercise 1-23. Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, and comments. (This program is hard if you do it in full generality.)
#define LENGTH 65536
#define STACKSIZE 4096

int is_in_singlequote(int in_doublequote, char c);
int is_in_doublequote(int in_doublequote, char c);
int is_in_comment(int in_doublequote, char c);
int check_syntax(int revelant_syntax, char c, char chars_to_check[]);
char pop();
void write_to_array(FILE *file, char file_cache[]);
void set_stack_limit(char stack[], int stack_limiter);


int main(int argc, char const *argv[])
{
    char filea_cache[LENGTH];
    char stack[STACKSIZE];
    int c, counter_stack = 0, counter = 0, stack_limiter = 0;
    int in_singlequote = 0, in_doublequote = 0, in_comment = 0, relevant_syntax = 0;
    char chars_to_check[7] = {'(', ')', '[', ']', '{', '}','\0'};

    FILE *filea;

    filea = fopen("comment.c", "r");

    write_to_array(filea, filea_cache);
    set_stack_limit(stack, stack_limiter);
    printf("filea_cache after writing:\n%s", filea_cache);

    while ((c = getc(filea_cache[counter])) != EOF && counter < LENGTH - 1)
    {
        relevant_syntax = check_syntax(relevant_syntax,c,chars_to_check);

        if (relevant_syntax == 1)
        {
            if (in_doublequote == 0)
            {
                in_singlequote = is_in_singlequote(in_singlequote, c);
            }
            if (in_singlequote == 0)
            {
                in_doublequote = is_in_doublequote(in_doublequote, c);
            }

            if (in_doublequote + in_singlequote + in_comment == 0)
            {
                stack[counter_stack] = c;
                set_stack_limit(stack, counter_stack + 1);
            }
        }
        counter++;
        relevant_syntax = 0;
    }

    if (stack[0] != '\0')
    {
        printf("Your code has syntax errors!\n");
    }

    return 0;
}

void write_to_array(FILE *file, char file_cache[])
{
    if (file)
    {
        int d, i = 0;
        while ((d = getc(file)) != EOF && i < LENGTH - 1)
        {
            file_cache[i] = d;
            i++;
        }
        file_cache[i] = '\0';
    }
}
int is_in_singlequote(int in_singlequote, char c)
{

    if (c == "'" && in_singlequote == 0)
    {
        in_singlequote = 1;
    }
    else if (c == "'" && in_singlequote == 1)
    {
        in_singlequote = 1;
    }

    return in_singlequote;
}

int is_in_doublequote(int in_doublequote, char c)
{

    if (c == '"' && in_doublequote == 0)
    {
        in_doublequote = 1;
    }
    else if (c == "'" && in_doublequote == 1)
    {
        in_doublequote = 0;
    }
    return in_doublequote;
}
// int is_in_comment(int in_doublequote, char c);
// {

// }

void set_stack_limit(char stack[], int stack_limiter)
{
    stack[stack_limiter] = '\0';
}

int check_syntax(int revelant_syntax, char c, char chars_to_check[])
{

    return revelant_syntax;
}