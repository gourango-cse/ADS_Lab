#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Function to preprocess the bad character heuristic
void preprocessBadCharacter(const char *pattern, int m, int badChar[256]) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;  // Initialize all bad character values to -1
    }
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)pattern[i]] = i;  // Store the rightmost index of each character
    }
}

// Function to preprocess the good suffix heuristic
void preprocessGoodSuffix(const char *pattern, int m, int *shift, int *suffix) {
    int i, j;

    for (i = 0; i < m; i++) {
        shift[i] = m;   // Initialize shift array with the length of the pattern
        suffix[i] = -1; // Initialize suffix array with -1
    }

    for (i = m - 1, j = m; i >= 0; i--) {
        if (i == 0 || pattern[i] == pattern[j - 1]) {
            j = i;
            while (j >= 0 && pattern[j] == pattern[m - (i - j)]) {
                j--;
            }
            suffix[i] = i - j;
        }
    }

    for (i = 0; i < m; i++) {
        if (suffix[i] == i + 1) {
            for (j = 0; j < m - i - 1; j++) {
                if (shift[j] == m) {
                    shift[j] = m - i - 1;
                }
            }
        }
    }

    for (i = 0; i < m; i++) {
        if (suffix[i] != -1) {
            shift[m - suffix[i]] = m - i - 1;
        }
    }
}

// Boyer-Moore search function
int boyerMooreSearch(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0 || n == 0) {
        return -1; // Null or empty input
    }

    int badChar[256];
    preprocessBadCharacter(pattern, m, badChar);

    int *shift = (int *)malloc((m + 1) * sizeof(int));
    int *suffix = (int *)malloc(m * sizeof(int));
    preprocessGoodSuffix(pattern, m, shift, suffix);

    int s = 0; // s is the shift of the pattern with respect to the text
    while (s <= n - m) {
        int j = m - 1;

        // Compare pattern from right to left
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            free(shift);
            free(suffix);
            return s; // Pattern found
        } else {
            // Calculate the maximum shift using the bad character and good suffix heuristics
            int badCharShift = j - badChar[(unsigned char)text[s + j]];
            int goodSuffixShift = (j < m - 1) ? shift[j] : 1; // Apply good suffix shift if applicable

            // Move the pattern by the maximum of the two shifts
            s += (badCharShift > goodSuffixShift) ? badCharShift : goodSuffixShift;
        }
    }

    free(shift);
    free(suffix);
    return -1; // Pattern not found
}

// Main function
int main() {
    char text[1024], pattern[1024];

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // Remove trailing newline

    // Check for empty inputs
    if (strlen(text) == 0 || strlen(pattern) == 0) {
        printf("Error: Text or pattern cannot be empty!\n");
        return 1;
    }

    // Call the Boyer-Moore search
    int position = boyerMooreSearch(text, pattern);

    if (position == -1) {
        printf("Pattern not found in the text.\n");
    } else {
        printf("Pattern found at index: %d\n", position);
    }

    return 0;
}
