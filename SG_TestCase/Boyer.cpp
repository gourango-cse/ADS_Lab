#include <iostream>
#include <cstring>

// Preprocess the bad character heuristic
void preprocessBadCharacter(const char *pattern, int m, int badChar[256]) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }
}

// Preprocess the good suffix heuristic
void preprocessGoodSuffix(const char *pattern, int m, int *shift, int *suffix) {
    for (int i = 0; i <= m; i++) {
        shift[i] = m;
    }
    for (int i = 0; i < m; i++) {
        suffix[i] = -1;
    }

    // Fill the suffix array
    int j = m;
    for (int i = m - 1; i >= 0; i--) {
        if (i == 0 || pattern[i] != pattern[m - 1]) {
            j = i;
        }
        suffix[i] = j;
    }

    // Fill the shift array using the suffix array
    for (int i = 0; i < m; i++) {
        if (suffix[i] == i + 1) {
            for (int j = 0; j < m - i - 1; j++) {
                if (shift[j] == m) {
                    shift[j] = m - i - 1;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        shift[m - suffix[i]] = m - i - 1;
    }
}

// Boyer-Moore search function
int boyerMooreSearch(const char *text, const char *pattern) {
    int n = 0, m = 0;

    // Calculate the lengths of text and pattern
    while (text[n] != '\0') n++;
    while (pattern[m] != '\0') m++;

    if (m == 0 || n == 0) {
        return -1; // Null or empty input
    }

    int badChar[256];
    preprocessBadCharacter(pattern, m, badChar);

    int *shift = new int[m + 1];
    int *suffix = new int[m];
    preprocessGoodSuffix(pattern, m, shift, suffix);

    int s = 0; // s is the shift of the pattern with respect to the text
    while (s <= n - m) {
        int j = m - 1;

        // Compare pattern from right to left
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            delete[] shift;
            delete[] suffix;
            return s; // Pattern found
        } else {
            int badCharShift = j - badChar[(unsigned char)text[s + j]];
            int goodSuffixShift = shift[j + 1];
            s += std::max(1, std::max(badCharShift, goodSuffixShift));
        }
    }

    delete[] shift;
    delete[] suffix;
    return -1; // Pattern not found
}

// Main function
int main() {
    char text[1024], pattern[1024];

    std::cout << "Enter the text: ";
    std::cin.getline(text, sizeof(text));

    std::cout << "Enter the pattern to search: ";
    std::cin.getline(pattern, sizeof(pattern));

    // Check for empty inputs
    if (text[0] == '\0' || pattern[0] == '\0') {
        std::cout << "Error: Text or pattern cannot be empty!" << std::endl;
        return 1;
    }

    // Call the Boyer-Moore search
    int position = boyerMooreSearch(text, pattern);

    if (position == -1) {
        std::cout << "Pattern not found in the text." << std::endl;
    } else {
        std::cout << "Pattern found at index: " << position << std::endl;
    }

    return 0;
}
