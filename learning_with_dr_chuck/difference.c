#include <stdio.h>
#include "function_raising_to_the_power.c"

int main(int argc, char const *argv[])
{
    int j = 15;
    int i = 15;
    printf("Hallo\n");
    j = power(j,i);
    printf("Deine Zahl ist:%d",j);
    return 0;
}
