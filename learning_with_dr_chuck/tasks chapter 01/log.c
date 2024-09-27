#include <stdio.h>

int countDigits(int number) {
    int count = 0;
    while (number != 0) {
        number /= 10;  // Remove the last digit
        count++;       // Increment the digit count
    }
    return count;
}

int main() {
    int number = 100;


    // Edge case for 0, as it has 1 digit
    if (number == 0) {
        printf("The number 0 has 1 digit.\n");
    } else {
        printf("The number %d has %d digits.\n", number, countDigits(number));
    }

    return 0;
}
