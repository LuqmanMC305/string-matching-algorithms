#include <iostream>
#include <vector>
#include <string>

using namespace std;

//KMP search function
vector<int> kmp_search(const string& str, const string& subStr, const vector<int>& table)
{
    vector<int> pos; //Store the positions where the pattern is found
    int numPos = 0; //Number of positions where the pattern is found
    int currStr = 0; //Position of current character in string
    int currSubStr = 0; //Position of current character in substring

    while (currStr < str.length())
    {
        if (subStr[currSubStr] == str[currStr]) // Move the next characters in str and subStr
        {
            currStr++;
            currSubStr++;
            if (currSubStr == subStr.length()) //If the end of pattern is reached, store the position & reset currSubStr
            {
                pos.push_back(currStr - currSubStr);
                numPos++;
                currSubStr = table[currSubStr];
            }
        }
        else
        {
            currSubStr = table[currSubStr]; //If the charactors aren't matched, update currSubStr based on the failure function
            if (currSubStr < 0) //If currSubStr is negative, move to the next character in str & reset currSubStr
            {
                currStr++;
                currSubStr++;
            }
        }
    }

    return pos;
}

// Function to compute the failure function/partial match table
vector<int> compute_failure_function(const string& subStr)
{
    vector<int> t(subStr.length() + 1, -1); // Failure function table initialized with -1
    int pos = 1; // Position in pattern
    int cnd = 0; // Candidate position

    while (pos < subStr.length())
    {
        if (subStr[pos] == subStr[cnd]) // If the characters match, update t[pos] with t[cnd]
            t[pos] = t[cnd];
        else 
        { // If the characters don't match, update t[pos] with cnd and update cnd
            t[pos] = cnd;
            cnd = t[cnd];
            while (cnd >= 0 && subStr[pos] != subStr[cnd])
                cnd = t[cnd];
        }
        pos++;
        cnd++;
    }

    t[pos] = cnd;

    return t;
}

int main()
{
    string str, subStr;

    // Get the input text from user
    cout << "Enter the text: " << endl;
    getline(cin, str);

    // Search the pattern that the user wants to find
    cout << "Enter the pattern that you want to find: " << endl;
    cin >> subStr;

    // Compute the failure function/partial match table for the pattern
    vector<int> partialMatchTable = compute_failure_function(subStr);

    // Search for the pattern in the text using KMP algorithm
    vector<int> pattern = kmp_search(str, subStr, partialMatchTable);
    
    // Print the positions where the pattern is found
    if(pattern.size() == 0)
        cout << "No substring is found." << endl;
    else
    {
        for (int pos : pattern)
            cout << "Found at position: " << pos << endl;
    }
    cout << endl;

    return 0;
}