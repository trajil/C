#include <stdio.h>

// Exercise 1-23. Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, and comments. (This program is hard if you do it in full generality.)
#define LENGTH 65536
#define STACKSIZE 4096
#define LINES 65536

int which_line(int lines[LINES], int *counter)
{
    int in_line = 1, index = 0, counting = 1;
    int position = *counter;

    while (counting == 1 && index < LINES)
    {
        if (position >= lines[index] && position <= lines[index + 1])
        {
            counting = 0;
        }
        if (counting == 1)
        {
            in_line++;
            index += 2;
        }
    }

    return in_line;
}

void pop(char stack[], int stack_address[], int j, int *succesfully_deleted, int *current_stack_length)
{
    // Check if the index `j` is valid
    if (j < 0 || j >= *current_stack_length)
    {
        *succesfully_deleted = 0; // Invalid pop request
        return;
    }

    // Shift elements to the left, starting from index `j`
    for (int i = j; i < *current_stack_length - 1; i++)
    {
        stack[i] = stack[i + 1];
        stack_address[i] = stack_address[i + 1];
    }

    *current_stack_length -= 1;          // Reduce the stack length by 1
    stack[*current_stack_length] = '\0'; // Adjust the null terminator
    *succesfully_deleted = 1;            // Mark successful deletion
}

void handle_stack(char c, char stack[], int stack_address[], int *current_stack_length, char chars_to_check[], int *right_bracket_error, int *position_of_bracket, int *counter)
{
    int i = *position_of_bracket, succesfully_deleted = 0;
    // printf("%d\n",i);
    //  whether or not it's: ), ] or }
    if (i % 2 == 1)
    {
        // setting flag, waiting to find an opening bracket to match a pending closing bracket
        *right_bracket_error = 1;
        // checking the whole stack for a counter part bracket
        for (int j = *current_stack_length; j >= 0; j--)
        {
            if (stack[j] == chars_to_check[i - 1])
            {
                pop(stack, stack_address, j, &succesfully_deleted, current_stack_length);
                *right_bracket_error = 0;
                printf("deleted from stack\n");
                printf("address: %d\n", stack_address[*current_stack_length]);
                break; // Exit the loop once the counterpart is found and deleted.
            }
        }
    }

    // otherwise: add bracket to stack and set new EOF
    else
    {
        stack[*current_stack_length] = c;
        stack_address[*current_stack_length] = *counter;
        printf("added to stack!\n");
        printf("address: %d\n", stack_address[*current_stack_length]);
        (*current_stack_length)++;
        stack[*current_stack_length] = '\0';
    }
}

void handle_quotes(char c, int *counter, char file_cache[])
{
    // int in_singlequote = 0, in_doublequote = 0;

    if (c == '"')
    {
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '"' && *counter < LENGTH - 1);
    }
    else if (c == '\'')
    {
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '\'' && *counter < LENGTH - 1);
    }
}

void handle_comments(int *counter, char file_cache[])
{
    if (file_cache[*counter] == '/' && file_cache[*counter + 1] == '/')
    {
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '\n' && *counter < LENGTH - 1);
    }
    else if (file_cache[*counter] == '/' && file_cache[*counter + 1] == '*')
    {
        (*counter) += 2; // Skip past /*
        while (*counter < LENGTH - 1 && !(file_cache[*counter] == '*' && file_cache[*counter + 1] == '/'))
        {
            (*counter)++;
        }
        (*counter) += 2; // Skip past */
    }
}

void write_to_array(FILE *file, char file_cache[], int lines[])
{
    int d, i = 0, j = 0, start_of_line = 1;
    while ((d = getc(file)) != EOF && i < LENGTH - 1)
    {
        file_cache[i] = d;
        if (start_of_line == 1)
        {
            lines[j] = i;
            start_of_line = 0;
            j++;
        }
        if (start_of_line == 0 && d == '\n')
        {
            lines[j] = i;
            start_of_line = 1;
            j++;
        }
        i++;
    }
    file_cache[i] = '\0';
}

void set_stack_limit(char stack[], int stack_limiter)
{
    stack[stack_limiter] = '\0';
}

void is_in_chars_to_check(int *revelant_syntax, char c, char chars_to_check[], int *position_of_bracket)
{
    int i = 0, b = *revelant_syntax;
    while (chars_to_check[i] != '\0' && b == 0)
    {
        if (c == chars_to_check[i])
        {

            b = 1;
            break;
        }
        i++;
    }
    *revelant_syntax = b;
    *position_of_bracket = i;
}
int main(int argc, char const *argv[])
{
    char filea_cache[LENGTH];
    char stack[STACKSIZE];
    int stack_address[STACKSIZE];
    int lines[LINES];
    int c, counter_stack = 0, counter = 0, current_stack_length = 0, in_line = 0, position_of_bracket = 0;
    int in_comment = 0, relevant_syntax = 0, right_bracket_error = 0;
    char chars_to_check[7] = {'(', ')', '[', ']', '{', '}', '\0'};
    chars_to_check[6] = '\0';
    FILE *filea;

    filea = fopen("comment1.c", "r");

    if (filea == NULL)
    {
        printf("Error: Could not open file.\n");
        return 1;
    }

    write_to_array(filea, filea_cache, lines);
    fclose(filea);
    set_stack_limit(stack, current_stack_length);
    // printf("filea_cache after writing:\n%s", filea_cache);

    while ((c = filea_cache[counter]) != '\0' && counter < LENGTH - 1 && right_bracket_error == 0)
    {
        if (c == '"' || c == '\'')
        {
            handle_quotes(c, &counter, filea_cache);
        }
        if (c == '/')
        {
            handle_comments(&counter, filea_cache);
        }

        c = filea_cache[counter];
        relevant_syntax = 0;
        // printf("check char in\n");
        is_in_chars_to_check(&relevant_syntax, c, chars_to_check, &position_of_bracket);
        // printf("check char out\n");

        if (relevant_syntax == 1)
        {
            printf("c is %c [%d]\n", c, counter);
            handle_stack(c, stack, stack_address, &current_stack_length, chars_to_check, &right_bracket_error, &position_of_bracket, &counter);
            printf("line: %d\n", in_line = which_line(lines, &counter));
        }

        counter++;
    }

    if (right_bracket_error == 1)
    {
        printf("Your code has missing opening brackets!\n");
    }
    else if (stack[0] != '\0')
    {
        printf("Your code has missing closing brackets!\n");
    }
    else
        printf("Your code is about right...\n");

    return 0;
}