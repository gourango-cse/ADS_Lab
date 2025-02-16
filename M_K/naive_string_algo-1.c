#include <stdio.h>
#include <string.h>

// Naive String Matcher Function
void naive_string_matcher(char T[], char P[]) {
    int n = strlen(T); // Length of text T
    int m = strlen(P); // Length of pattern P
    int found = 0;     // Flag to check if the pattern is found

    // Loop over possible shifts
    int s;
    for (s = 0; s <= n - m; s++) {
        int j;

        // Check for pattern match
        for (j = 0; j < m; j++) {
            if (P[j] != T[s + j]) {
                break; // Mismatch, stop checking further
            }
        }

        // If full pattern matches
        if (j == m) {
            printf("Pattern occurs with shift %d\n", s);
            found = 1;
        }
    }

    // If no match is found
    if (!found) {
        printf("Pattern not found\n");
    }
}

int main() {
    char T[100], P[100];

    // Test case 1: Pattern found at index 0
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);
    naive_string_matcher(T, P);


    return 0;
}
