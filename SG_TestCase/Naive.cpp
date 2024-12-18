#include <iostream>
#include <string>
using namespace std;

// Function to perform Naive String Matching
void search(string pat, string txt) {
    int M = pat.size();
    int N = txt.size();
    bool found = false; // Flag to check if pattern exists

    // Loop to slide the pattern over text
    for (int i = 0; i <= N - M; i++) {
        int j;

        // Check for pattern match at current index
        for (j = 0; j < M; j++) {
            if (txt[i + j] != pat[j]) {
                break;
            }
        }

        // If pattern matches at index i
        if (j == M) {
            cout << "Pattern found at index " << i << endl;
            found = true;
        }
    }

    // If no match is found
    if (!found) {
        cout << "Pattern not found in the text." << endl;
    }
}

// Driver Code
int main() {
    string txt, pat;

    // Taking user input
    cout << "Enter the text: ";
    getline(cin, txt);

    cout << "Enter the pattern: ";
    getline(cin, pat);

    // Calling the search function
    search(pat, txt);

    return 0;
}