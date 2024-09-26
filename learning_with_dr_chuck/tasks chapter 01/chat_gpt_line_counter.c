#include <stdio.h>

#define LENGTH 65536
#define STACKSIZE 4096

// Function to remove an element from the stack
void pop(char stack[], int j, int *succesfully_deleted, int *current_stack_length)
{
    int i = *current_stack_length;
    char temp_stack[STACKSIZE];

    // Copy stack to temp_stack
    for (size_t k = 0; k <= *current_stack_length; k++)
    {
        temp_stack[k] = stack[k];
    }

    // Left shift of stack
    while (i > j)
    {
        stack[i - 1] = temp_stack[i];
        i--;
    }
    *succesfully_deleted = 1;
    (*current_stack_length)--;
}

// Function to handle stack operations for brackets and braces
void handle_stack(char c, char stack[], int *current_stack_length, char chars_to_check[], int *right_bracket_error)
{
    int i = 0, found_char = 0, succesfully_deleted = 0;

    // Finding the right bracket
    while (chars_to_check[i] != '\0' && found_char == 0)
    {
        if (c == chars_to_check[i])
        {
            found_char = 1;
        }
        else
        {
            i++;
        }
    }

    // Check if it's a closing bracket: ), ] or }
    if (chars_to_check[i] % 2 == 1)
    {
        // Set flag, waiting to find an opening bracket to match a pending closing bracket
        *right_bracket_error = 1;
        // Checking the whole stack for a counterpart bracket
        for (int j = *current_stack_length; j > 0; j--)
        {
            // If counterpart bracket is in stack: pop it from stack
            if (stack[j] == chars_to_check[i - 1])
            {
                pop(stack, j, &succesfully_deleted, current_stack_length);
                break;
            }
        }
        if (succesfully_deleted == 1)
            *right_bracket_error = 0;
    }
    // Otherwise: add bracket to stack
    else
    {
        stack[*current_stack_length] = c;
        (*current_stack_length)++;
        stack[*current_stack_length] = '\0';
    }
}

// Function to handle quotes
void handle_quotes(char c, int *counter, char file_cache[])
{
    if (c == '"') // Handling double quotes
    {
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '"' && *counter < LENGTH - 1);
    }
    else if (c == '\'') // Handling single quotes
    {
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '\'' && *counter < LENGTH - 1);
    }
}

// Function to handle comments
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
        do
        {
            (*counter)++;
        } while (file_cache[*counter] != '*' || file_cache[*counter + 1] != '/' && *counter < LENGTH - 1);
        (*counter) += 2; // Skip past '*/'
    }
}

// Function to write the content of a file into a char array
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

// Set the end of the stack
void set_stack_limit(char stack[], int stack_limiter)
{
    stack[stack_limiter] = '\0';
}

// Check if the character is in chars_to_check array
void is_in_chars_to_check(int *relevant_syntax, char c, char chars_to_check[])
{
    int i = 0;
    while (chars_to_check[i] != '\0')
    {
        if (c == chars_to_check[i])
        {
            *relevant_syntax = 1;
        }
        i++;
    }
}

int main(int argc, char const *argv[])
{
    char filea_cache[LENGTH];
    char stack[STACKSIZE];
    int c, counter_stack = 0, counter = 0, current_stack_length = 0, line_counter = 1;
    int in_comment = 0, relevant_syntax = 0, right_bracket_error = 0;
    char chars_to_check[7] = {'(', ')', '[', ']', '{', '}', '\0'};

    FILE *filea;

    filea = fopen("comment1.c", "r");

    write_to_array(filea, filea_cache);
    fclose(filea);
    set_stack_limit(stack, current_stack_length);

    while ((c = filea_cache[counter]) != '\0' && counter < LENGTH - 1 && right_bracket_error == 0)
    {
        if (c == '"' || c == '\'')
            handle_quotes(c, &counter, filea_cache);

        if (c == '/')
            handle_comments(&counter, filea_cache);

        c = filea_cache[counter];
        relevant_syntax = 0;

        is_in_chars_to_check(&relevant_syntax, c, chars_to_check);

        if (relevant_syntax == 1)
            handle_stack(c, stack, &current_stack_length, chars_to_check, &right_bracket_error);

        counter++;
    }

    if (right_bracket_error == 1)
    {
        printf("Your code has missing opening brackets!\n");
        return -1;
    }

    if (stack[0] != '\0')
    {
        printf("Your code has missing closing brackets!\n");
    }
    else
    {
        printf("Your code is about right...\n");
    }

    return 0;
}
