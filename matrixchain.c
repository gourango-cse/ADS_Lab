#include <stdio.h>
#include <limits.h>

#define MAX 100

// Function to print optimal parenthesization
void printOptimalParens(int s[MAX][MAX], int i, int j) {
    if (i == j)
        printf("A%d", i);
    else {
        printf("(");
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        printf(")");
    }
}

// Print m and s tables
void printTables(int m[MAX][MAX], int s[MAX][MAX], int n) {
    printf("\nCost Table m[i][j]:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i > j) {
                printf("   -   ");
            } else {
                printf("%6d ", m[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nSplit Table s[i][j]:\n");
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (i >= j) {
                printf("   -   ");
            } else {
                printf("%6d ", s[i][j]);
            }
        }
        printf("\n");
    }
}

// Matrix Chain Order algorithm
void matrixChainOrder(int p[], int n) {
    int m[MAX][MAX], s[MAX][MAX];

    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    for (int l = 2; l < n; l++) {
        for (int i = 1; i <= n - l; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of multiplications: %d\n", m[1][n-1]);
    printf("Optimal Parenthesization: ");
    printOptimalParens(s, 1, n-1);
    printf("\n");

    printTables(m, s, n);
}

int main() {
    int p[MAX], n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    printf("Enter the dimensions (total %d numbers):\n", n + 1);
    for (int i = 0; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%d", &p[i]);
    }

    matrixChainOrder(p, n + 1);
    return 0;
}