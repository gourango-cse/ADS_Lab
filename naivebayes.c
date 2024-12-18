#include<stdio.h>
#include<string.h>

void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int found = 0;

    // Check if the pattern is empty
    if (M == 0) {
        printf("Error: Pattern cannot be empty.\n");
        return;
    }

    // A loop to slide pat[] one by one
    for (int i = 0; i <= N - M; i++)
    {
        int j;

        // For current index i, check for pattern match
        for (j = 0; j < M; j++)
        {
            if (txt[i + j] != pat[j])
                break;
        }

        // if j equal to M, then pattern is found
        if (j == M) {
            printf("\nPattern found at index %d ", i);
            found++;
        }
    }

    // If no pattern is found
    if (found == 0) 
        printf("\nPattern not found");
}

int main()
{
    char txt[100];
    char pat[50];

    // Read input text and pattern
    printf("Please enter the text/string: ");
    scanf("%[^\n]%*c", txt);  // Reads the entire line including spaces

    printf("\nPlease enter the pattern: ");
    scanf("%[^\n]%*c", pat);  // Reads the entire pattern including spaces

    // Check for empty pattern and handle it
    if (strlen(pat) == 0) {
        printf("Error: Pattern cannot be empty.\n");
        return 1;  // Exit if pattern is empty
    }

    // Call the search function
    search(pat, txt);

    return 0;
}
