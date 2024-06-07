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

// Boyer-Moore-Horspool search function
// Uses the bad character rule to search for the pattern in the text
vector<int> boyerMooreHorspool(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;

    if (m == 0) return result; // If the pattern is empty, return an empty result

    vector<int> badChar(ALPHABET_SIZE, -1); // Bad character table
    preprocessBadCharacter(pattern, badChar); // Fill the bad character table

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
            s += m;
        } else {
            // Shift the pattern to align the bad character in text with the last occurrence of it in pattern.
            s += max(1, j - badChar[(int)text[s + j]]);
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

    // Perform the Boyer-Moore-Horspool search
    vector<int> results = boyerMooreHorspool(text, pattern);

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
    cout << "Average-case Time Complexity: O(n)" << endl;
	cout << "Worst-case Time Complexity: O(nm)" << endl;
    return 0;
}
