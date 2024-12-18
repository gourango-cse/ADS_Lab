#include <iostream>
#include <string>

using namespace std;

void computeLPSArray(string pat, int M, int* lps) {
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0; // lps[0] is always 0

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            // This is tricky. Consider the example AAACAAAA and i = 7
            if (len != 0) {
                // This is the tricky part. len is not 0. We continue the loop from lps[len-1]
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPSearch(string pat, string txt) {
    int M = pat.length();
    int N = txt.length();

    // create lps[] that will hold the longest prefix suffix values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1];
        }

        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
}

int main() {
    string txt, pat;

    cout << "Enter the text: ";
    getline(cin, txt);

    cout << "Enter the pattern: ";
    getline(cin, pat);

    KMPSearch(pat, txt);

    return 0;
}