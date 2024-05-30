#include <iostream>
#include <vector>
#include <string>
using namespace std;

//KMP search function
vector<int> kmp_search(const string& S, const string& W, const vector<int>& T)
{
    std::vector<int> P; //Store the positions where the pattern is found
    int nP = 0; //Number of positions where the pattern is found
    int j = 0; //Position of current character in string
    int k = 0; //Position of current character in substring

    while (j < S.length())
    {
        if (W[k] == S[j]) // Move the next characters in S and W
        {
            j++;
            k++;
            if (k == W.length()) //If the end of pattern is reached, store the position & reset k
            {
                P.push_back(j - k);
                nP++;
                k = T[k];
            }
        }
        else
        {
            k = T[k]; //If the charactors aren't matched, update k based on the failure function
            if (k < 0) //If k is negative, move to the next character in S & reset k
            {
                j++;
                k++;
            }
        }
    }

    return P;
}

// Function to compute the failure function/partial match table
vector<int> compute_failure_function(const string& W)
{
    vector<int> T(W.length() + 1, -1); // Failure function table initialized with -1
    int pos = 1; // Position in pattern
    int cnd = 0; // Candidate position

    while (pos < W.length())
    {
        if (W[pos] == W[cnd]) // If the characters match, update T[pos] with T[cnd]
            T[pos] = T[cnd];
        else 
        { //If they aren't update T[pos] with cnd and update cnd
            T[pos] = cnd;
            cnd = T[cnd];
            while (cnd >= 0 && W[pos] != W[cnd])
                cnd = T[cnd];
        }
        pos++;
        cnd++;
    }
    T[pos] = cnd;

    return T;
}

int main()
{
    string str, subStr;
    cout << "Enter the text: " << endl;
    getline(cin, str);
    cout << "Enter the pattern that you want to find: " << endl;
    cin >> subStr;

    vector<int> partialMatchTable = compute_failure_function(subStr);
    vector<int> pattern = kmp_search(str, subStr, partialMatchTable);

    cout << "Positions: ";
    if(pattern.size() == 0)
    {
        cout << "No substring is found." << endl;
    }
    else
    {
        for (int pos : pattern)
        {
            cout << pos << " ";
        }
    }
    cout << endl;

    return 0;
}