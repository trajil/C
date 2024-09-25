#include <stdio.h>

// program to convert US style of floor naming to EU (USF -1 = EUF)
int main(int argc, char const *argv[])
{
    while (1 == 1)
    {
        int usf, euf;
        printf("Please enter your US floor level:");
        scanf("%d", &usf);
        euf = usf - 1;
        printf("Your EU floor level would be: %d\n", euf );
    }

    return 0;
}
