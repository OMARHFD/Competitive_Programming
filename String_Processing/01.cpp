//link : https://codeforces.com/contest/808/problem/G
#include <bits/stdc++.h>
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
        string s = "ABACABA";
        cin >> s;
        int n = size(s);
        vector<int> pi = prefix_function(s);   
        vector<int> ans(n + 1);
        for (int i = 0; i < n; i++)
        ans[pi[i]]++;
        for (int i = n-1; i > 0; i--)
        ans[pi[i-1]] += ans[i];
        for (int i = 0; i <= n; i++)
        ans[i]++;
        vector<pair<int,int>> answers ;
        int number = 0;
        int r=pi [n-1];
        while (r)
            {   
                number +=  1;
                answers.push_back(make_pair(r,ans[r]));
                r=pi [r-1];
            };
            reverse(answers.begin(), answers.end());
        cout << number +1 << endl;
        for (auto a : answers)
            {
                cout << a.first<<" "<<a.second<<endl;
            };
        cout << n << " "<<1 ;
        return 0;
    }