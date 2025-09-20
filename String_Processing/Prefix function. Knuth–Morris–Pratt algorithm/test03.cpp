/*
PREFIX FUNCTION

problem:
A border of a string is a prefix that is also a suffix of the string but not the whole string. For example, the borders of abcababcab are ab and abcab.
Your task is to find all border lengths of a given string.
Input
The only input line has a string of length n consisting of characters a–z.
Output
Print all border lengths of the string in increasing order.
Constraints

1 \le n \le 10^6

Example
Input:
abcababcab

Output:
2 5
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


int main()
    {
        string S;
        cin>>S;
        vector <int> anss = prefix_function(S);
        cout <<endl;
        vector <int> answrs;
        answrs.push_back(anss[S.size()-1]);
        int u = anss[S.size()-1];
        while (u!=0)
            {
                answrs.push_back(anss[u - 1]  );
                u = anss[u-1];

            }
    reverse(answrs.begin(), answrs.end()); // ✅ increasing order
        for (auto ele : answrs) 
            if (ele !=0)    
                cout << ele <<" ";
            
        
        return 0;
    }
