#include <stdio.h>

char string[] = "Hello";
char zwischenspeicher;
int i, j = 0;

int count_length(char string[])
{
    while (string[j] != '\0')
    {
        j++;
    }
    return j;
}
int main(int argc, char const *argv[])
{
    count_length(string);

    printf("Your string was: %s\n", string);
    printf("The lenght of the char array is: %d\n", j);
    
    j--;
    while (1 == 1)
    {
        if (i >= j)
        {
            break;
        }

        zwischenspeicher = string[j];
        string[j] = string[i];
        string[i] = zwischenspeicher;

        i++;
        j--;
    }

    printf("The new string is: %s\n", string);

    return 0;
}
