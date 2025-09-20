/*
PREFIX FUNCTION
problem:
Given a string and a pattern, your task is to count the number of positions where the pattern occurs in the string.
Input
The first input line has a string of length n, and the second input line has a pattern of length m. Both of them consist of characters a–z.
Output
Print one integer: the number of occurrences.
Constraints

1 \le n,m \le 10^6

Example
Input:
saippuakauppias
pp

Output:
2
*/



#include<bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}


int main ()
    {
        string t;
        string s;
        cin>> t;
        cin>> s;
        int answer = 0;
        string ne = s+"#"+t;
        vector <int> anscont = prefix_function(ne);
        for (auto ele : anscont)
            {
                if (ele == s.size()) answer++;
            }
        cout << answer;





        return 0 ;
    }

