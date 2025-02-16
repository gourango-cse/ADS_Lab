#include <stdio.h>
#include <string.h>

// Function to compute the prefix function
void compute_prefix_function(char P[], int m, int pi[]) {
    pi[0] = 0; // The first value is always 0
    int k = 0;

    printf("Prefix function computation:\n");
    int q;
    for (q = 1; q < m; q++) {
        while (k > 0 && P[k] != P[q]) {
            k = pi[k - 1];
        }
        if (P[k] == P[q]) {
            k++;
        }
        pi[q] = k;
        printf("pi[%d] = %d\n", q, pi[q]);
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
    printf("\nSearching for the pattern in the text:\n");
    int i;
    for (i = 0; i < n; i++) {
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

    if (q != m) {
        printf("No more matches found.\n");
    }
}

int main() {
    char T[100], P[100];

    printf("Enter text: ");
    fgets(T, sizeof(T), stdin);
    T[strcspn(T, "\n")] = '\0'; // Remove trailing newline

    printf("Enter pattern: ");
    fgets(P, sizeof(P), stdin);
    P[strcspn(P, "\n")] = '\0'; // Remove trailing newline

    kmp_matcher(T, P);

    return 0;
}