/*
MANACHER'S ALGO
Problem:
Given a string, calculate for each position the length of the longest palindrome that ends at that position.
Input
The only line contains a string of length n. Each character is one of a–z.
Output
Print n numbers: the length of each palindrome.
Constraints

1 \le n \le 2 \cdot 10^5

Example
Input:
ababbababaa

Output:
1 1 3 3 2 4 6 8 5 5 2


to do
*/



#include <bits/stdc++.h>
using namespace std;

// Manacher's Algorithm
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = s.size();
    vector<int> d1(n), d2(n);

    // Odd length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = 1;
        if (i <= r) k = min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }

    // Even length palindromes
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = 0;
        if (i <= r) k = min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k--;
        if (i + k > r) l = i - k - 1, r = i + k;
    }

    return {d1, d2};
}

int main() {
    string s;
    cin >> s;
    auto [d1, d2] = manacher(s);
    int n = s.size();
    vector <int > answer (n,1);
    for (int i = 0; i < n; i++) {
        int lenOdd = 2 * d1[i] - 1;  // centered at i
        int lenEven = 2 * d2[i];     // centered between i-1 and i
        int best =max(lenEven , lenOdd);
        answer[i+(best-1)/2] = max(answer[i+(best-1)/2] , best);
    }
    for (auto ele :answer ) cout <<ele << " ";
    return 0;
}
