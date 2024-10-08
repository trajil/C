#include <stdio.h>

// This is a single-line comment

/*
   This is a multi-line comment.
   It spans multiple lines.
*/

int main() {
    int a = 5;  // Single-line comment after code
    
    char c = 'a';  // Single-line comment after char
    
    char quote_in_char = '\'';  // This is a character constant containing a single quote
    
    printf("Hello, World!\n");  // Single-line comment inside code
    
    printf("This string has a // fake comment inside it.\n");
    printf("This string has a // fake comment inside it.\n");
    printf("This string has a // fake comment inside it.\n");
    
    printf("This string has a /* fake multi-line comment */ inside it.\n");
    
    /*
     * Multi-line comment style commonly used in C code.
     * It is generally used for block comments.
     */
    
    // A comment containing quotes: "//", '/* */'
    
    // Another comment that ends here:
    // Still in comment
    printf("Valid code here\n");

    return 0;
}
