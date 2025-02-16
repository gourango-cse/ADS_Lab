#include <stdio.h>
#include <string.h>

int LCS_table[20][20];

// Function to print the LCS table with directions and values
void printLCS_Table(int m, int n) {
    printf("LCS Table with Directions and Values:\n");
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            // Print the direction along with the corresponding value
            if (i == 0 || j == 0) {
                printf("%3d ", LCS_table[i][j]);  // Print numbers in the first row and column
            } else {
                // Display directions
                if (LCS_table[i][j] == LCS_table[i - 1][j - 1] + 1) {
                    printf("%3s(%d) ", "↖", LCS_table[i][j]);  // Diagonal movement (matching characters)
                } else if (LCS_table[i][j] == LCS_table[i - 1][j]) {
                    printf("%3s(%d) ", "↑", LCS_table[i][j]);  // Upward movement (carrying value from above)
                } else if (LCS_table[i][j] == LCS_table[i][j - 1]) {
                    printf("%3s(%d) ", "←", LCS_table[i][j]);  // Leftward movement (carrying value from the left)
                }
            }
        }
        printf("\n");
    }
}

// Function to find and print the LCS
void lcsAlgo(char S1[], char S2[]) {
    int i, j, m, n;
    m = strlen(S1);
    n = strlen(S2);

    // Filling the matrix with 0's initially
    for (i = 0; i <= m; i++)
        LCS_table[i][0] = 0;
    for (i = 0; i <= n; i++)
        LCS_table[0][i] = 0;

    // Building the matrix in bottom-up way
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++) {
            if (S1[i - 1] == S2[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            } else if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j];
            } else {
                LCS_table[i][j] = LCS_table[i][j - 1];
            }
        }

    // Printing the LCS Table with directions and values
    printLCS_Table(m, n);

    // Reconstructing the LCS from the matrix
    int index = LCS_table[m][n];
    char lcsAlgo[index + 1]; // Array to store the LCS
    lcsAlgo[index] = '\0'; // Null-terminate the string

    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcsAlgo[index - 1] = S1[i - 1];
            i--;
            j--;
            index--;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Printing the subsequences
    printf("S1 : %s\nS2 : %s\n", S1, S2);
    printf("LCS: %s\n", lcsAlgo);
}

int main() {
    char S1[20], S2[20];

    // Taking input dynamically
    printf("Enter the first string (S1): ");
    scanf("%s", S1);
    printf("Enter the second string (S2): ");
    scanf("%s", S2);

    // Calling the LCS function
    lcsAlgo(S1, S2);

    return 0;
}
