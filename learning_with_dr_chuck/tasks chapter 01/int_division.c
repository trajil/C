#include <stdio.h>

int main(int argc, char const *argv[])
{
    int tablength = 4;
    int zahlen = 7;
    int ergebnis = zahlen/tablength;
    int ergebnis2 = zahlen - ergebnis*tablength;
    printf("ergebnis: %d\n",ergebnis);
    printf("ergebnis2: %d\n",ergebnis2);
    return 0;
}
