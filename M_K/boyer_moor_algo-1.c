#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CHAR 256
#define MAX_LEN 1000
int i, j,l;
// Compute Last Occurrence Function (Bad Characteristic Table)
void compute_last_occurrence_function(char P[], int m, int lambda[]) {
    for ( i = 0; i < MAX_CHAR; i++) {
        lambda[i] = -1; // Initialize all characters to -1
    }
    for ( j = 0; j < m; j++) {
        lambda[(int)P[j]] = j; // Set the last occurrence of each character
    }

    // Print the Bad Characteristic Table
    printf("Bad Characteristic Table (Last Occurrence):\n");
    for (i = 0; i < MAX_CHAR; i++) {
        if (lambda[i] != -1) {
            printf("  '%c' -> %d\n", i, lambda[i]);
        }
    }
    printf("\n");
}

// Compute Prefix Function (helper for Good-Suffix Function)
void compute_prefix_function(char P[], int m, int pi[]) {
    pi[0] = 0;
    int k = 0;
	int q;
    for ( q = 1; q < m; q++) {
        while (k > 0 && P[k] != P[q]) {
            k = pi[k - 1];
        }
        if (P[k] == P[q]) {
            k++;
        }
        pi[q] = k;
    }
}

// Compute Good-Suffix Function
void compute_good_suffix_function(char P[], int m, int gamma[]) {
    int pi[m], pi_reverse[m];
    char P_reverse[m + 1];

    // Compute Prefix Function for the pattern
    compute_prefix_function(P, m, pi);

    // Reverse the pattern and compute prefix function for the reverse
    for ( i = 0; i < m; i++) {
        P_reverse[i] = P[m - i - 1];
    }
    P_reverse[m] = '\0';
    compute_prefix_function(P_reverse, m, pi_reverse);

    // Initialize gamma array
    for ( j = 0; j <= m; j++) {
        gamma[j] = m - pi[m - 1];
    }

    // Update gamma array using the reversed prefix function
    for ( l = 1; l < m; l++) {
        int j = m - pi_reverse[l];
        if (gamma[j] > l - pi_reverse[l]) {
            gamma[j] = l - pi_reverse[l];
        }
    }

    // Print the Good Suffix Table
    printf("Good Suffix Table:\n");
    for ( j = 0; j <= m; j++) {
        printf("  Gamma[%d] = %d\n", j, gamma[j]);
    }
    printf("\n");
}

// Boyer-Moore Matcher
void boyer_moore_matcher(char T[], char P[]) {
    int n = strlen(T); // Length of text
    int m = strlen(P); // Length of pattern

    if (m > n) {
        printf("Pattern is longer than the text. No match is possible.\n");
        return;
    }

    int lambda[MAX_CHAR];
    int gamma[m + 1];
    int found = 0; // Flag to track if a match is found

    // Preprocess the pattern
    compute_last_occurrence_function(P, m, lambda);
    compute_good_suffix_function(P, m, gamma);

    int s = 0; // Shift of the pattern
    while (s <= n - m) {
        int j = m - 1;

        // Compare pattern and text from right to left
        while (j >= 0 && P[j] == T[s + j]) {
            j--;
        }

        if (j < 0) {
            // Match found
            printf("Pattern occurs with shift %d\n", s);
            found = 1; // Set flag to indicate a match was found
            s += gamma[0];
        } else {
            // Shift pattern based on the maximum of Good-Suffix and Last Occurrence rules
            int shift_good_suffix = gamma[j + 1];
            int shift_last_occurrence = j - lambda[(int)T[s + j]];
            s += (shift_good_suffix > shift_last_occurrence) ? shift_good_suffix : shift_last_occurrence;
        }
    }

    if (!found) {
        // No match was found
        printf("Pattern not found in the text.\n");
    }
}

int main() {
    char T[MAX_LEN], P[MAX_LEN];

    printf("Enter text: ");
    fgets(T, MAX_LEN, stdin);
    T[strcspn(T, "\n")] = '\0'; // Remove trailing newline

    printf("Enter pattern: ");
    fgets(P, MAX_LEN, stdin);
    P[strcspn(P, "\n")] = '\0'; // Remove trailing newline

    boyer_moore_matcher(T, P);

    return 0;
}
