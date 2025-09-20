C++ Code with Documentation
```cpp
#include <bits/stdc++.h>
using namespace std;

/*
Inverse Burrows-Wheeler Transform (BWT)
----------------------------------------
Given a string `bwt` which is the BWT of some original string,
reconstruct the original string.

The BWT is usually obtained by:
1. Appending a special character '#' (smaller than all letters) at the end.
2. Generating all rotations of the string.
3. Sorting the rotations lexicographically.
4. Taking the last column of the sorted rotations => this is `bwt`.

This function reverses the process.
*/

string inverseBWT(const string &bwt) {
    int n = bwt.size();

    // Step 1: First column is the sorted last column
    string firstCol = bwt;
    sort(firstCol.begin(), firstCol.end());

    // Step 2: Count occurrences of each character in the last and first column
    unordered_map<char, vector<int>> pos; // pos[ch] = indices of ch in bwt
    for (int i = 0; i < n; i++) pos[bwt[i]].push_back(i);

    unordered_map<char, int> freq; // number of occurrences in first column so far
    vector<int> tfreq(n);          // occurrence count for first column
    for (int i = 0; i < n; i++) {
        tfreq[i] = freq[firstCol[i]]++;
    }

    // Step 3: LF-mapping to reconstruct original string
    string original;
    int idx = pos['#'][0]; // Start from the special character
    for (int i = 0; i < n - 1; i++) {
        char ch = firstCol[idx];
        original += ch;
        idx = pos[ch][tfreq[idx]]; // Move to next index
    }

    reverse(original.begin(), original.end()); // Reverse to get correct order
    return original;
}

int main() {
    string bwt;
    cin >> bwt;

    string original = inverseBWT(bwt);
    cout << "Original string: " << original << endl;

    return 0;
}

```


What the Code Does

Input: BWT string with a special character # at the end.

Sorts the BWT string to get the first column of sorted rotations.

Tracks occurrences of each character in last and first column (LF-mapping).

Follows the LF-mapping from # to reconstruct the original string.

Outputs the original string.
Overall Time Complexity	O(n log n)
Space Complexity	O(n) (for arrays and vectors)
