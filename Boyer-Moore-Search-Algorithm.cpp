#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int ALPHABET_SIZE = 256;

// Preprocess the bad character rule
// Fills the badChar array with the last occurrence of each character in the pattern
void preprocessBadCharacter(const string& pattern, vector<int>& badChar) {
    int m = pattern.size();
    // Initialize all occurrences to -1
    fill(badChar.begin(), badChar.end(), -1);
    // Set the actual value of the last occurrence of a character in the pattern
    for (int i = 0; i < m; ++i) {
        badChar[(int)pattern[i]] = i;
    }
}

// Preprocess the good suffix rule
// Fills the goodSuffix array for efficient pattern matching
void preprocessGoodSuffix(const string& pattern, vector<int>& goodSuffix) {
    int m = pattern.size();
    vector<int> suffix(m, 0);
    int f = 0, g = m - 1;
    suffix[m - 1] = m;
    // Build the suffix array
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suffix[i + m - 1 - f] < i - g) {
            suffix[i] = suffix[i + m - 1 - f];
        } else {
            if (i < g) {
                g = i;
            }
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f]) {
                --g;
            }
            suffix[i] = f - g;
        }
    }
    // Initialize the goodSuffix array
    fill(goodSuffix.begin(), goodSuffix.end(), m);
    for (int i = m - 1, j = 0; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (; j < m - 1 - i; ++j) {
                if (goodSuffix[j] == m) {
                    goodSuffix[j] = m - 1 - i;
                }
            }
        }
    }
    for (int i = 0; i <= m - 2; ++i) {
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;
    }
}

// Boyer-Moore search function
// Uses the bad character and good suffix rules to search for the pattern in the text
vector<int> boyerMoore(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;

    if (m == 0) return result; // If the pattern is empty, return an empty result

    vector<int> badChar(ALPHABET_SIZE); // Bad character table
    preprocessBadCharacter(pattern, badChar); // Fill the bad character table
    vector<int> goodSuffix(m); // Good suffix table
    preprocessGoodSuffix(pattern, goodSuffix); // Fill the good suffix table

    int s = 0; // Shift of the pattern with respect to the text
    while (s <= n - m) {
        int j = m - 1;

        // Decrease index j of pattern while characters of pattern and text are matching at this shift s
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        
        if (j < 0) {
            // Pattern found at index s
            result.push_back(s);
            // Shift the pattern so that the next character in text aligns with the last occurrence of it in pattern.
            s += (s + m < n) ? m - badChar[(int)text[s + m]] : 1;
        } else {
            // Shift the pattern to align the bad character in text with the last occurrence of it in pattern.
            s += max(goodSuffix[j], j - badChar[(int)text[s + j]]);
        }
    }
    return result; // Return all occurrences of the pattern
}

int main() {
    string text, pattern;

    // Ask the user to enter the text
    cout << "Enter the text: ";
    getline(cin, text);

    // Ask the user to enter the pattern
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Perform the Boyer-Moore search
    vector<int> results = boyerMoore(text, pattern);

    // Print the results
    if (!results.empty()) {
        cout << "Pattern found at indices: ";
        for (int index : results) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found" << endl;
        cout << "--Check your pattern search back--" << endl;
    }
    
    cout << "Best-case Time Complexity: O(n/m)" << endl;
    cout << "Average-case Time Complexity: O(n/m)" << endl;
	cout << "Worst-case Time Complexity: O(nm)" << endl;

    return 0;
}

