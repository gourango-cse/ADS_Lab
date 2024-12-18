#include <stdio.h>
#include <string.h>

// Function to compute the prefix function
void compute_prefix_function(char P[], int m, int pi[]) {
    pi[0] = 0; // The first value is always 0
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && P[k] != P[q]) {
            k = pi[k - 1];
        }
        if (P[k] == P[q]) {
            k++;
        }
        pi[q] = k;
    }
}

// KMP Matcher function
void kmp_matcher(char T[], char P[]) {
    int n = strlen(T); // Length of text T
    int m = strlen(P); // Length of pattern P
    int pi[m];         // Prefix function array

    // Compute the prefix function
    compute_prefix_function(P, m, pi);

    int q = 0; // Number of characters matched

    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i]) {
            q = pi[q - 1]; // Fall back in the pattern
        }
        if (P[q] == T[i]) {
            q++; // Next character matches
        }
        if (q == m) { // Is the entire pattern matched?
            printf("Pattern occurs with shift %d\n", i - m + 1);
            q = pi[q - 1]; // Look for the next match
        }
    }
}

int main() {
    char T[100], P[100];

    // Test case 1: Pattern found at index 0
    printf("Test Case 1:\n");
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);
    kmp_matcher(T, P);

    // Test case 2: Pattern found at the end index
    printf("\nTest Case 2:\n");
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);
    kmp_matcher(T, P);

    // Test case 3: Pattern found anywhere
    printf("\nTest Case 3:\n");
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);
    kmp_matcher(T, P);

    // Test case 4: Pattern not found
    printf("\nTest Case 4:\n");
    printf("Enter text: ");
    scanf("%s", T);
    printf("Enter pattern: ");
    scanf("%s", P);
    kmp_matcher(T, P);

    return 0;
}
