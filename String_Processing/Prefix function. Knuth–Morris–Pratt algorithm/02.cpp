//link : https://codeforces.com/problemset/problem/471/D
#include <bits/stdc++.h>
using namespace std;


vector<int> prefix_function(vector<int> s) {
    int n = (int)s.size();
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
        int n , w ;
        int r;
        cin >> n >> w;
        if (n==1 ||w == 1 )
            {
                if (w == 1)
                    {
                        cout << n;
                    }
                else 
                    {
                        cout<<0;
                    }
            }
        else 
{        r=w;
        n--;
        w--;
        vector <int> t , s;
        int p1;
        int p2;
        cin >> p1;
        while (n--)
            {
                cin >> p2;
                t.push_back(p2-p1);
                p1=p2;
            };
        cin >> p1;
        while (w--)
            {
                cin >> p2;
                s.push_back(p2-p1);
                p1=p2;
            };
        int mx1 = *max_element(t.begin(), t.end());
        int mx2 = *max_element(s.begin(), s.end());
        vector <int> fs;
        for (auto c : s)
            {
                fs.push_back(c);
            }
        fs.push_back(max(mx1,mx2)+1);
        for (auto c : t)
            {
                fs.push_back(c);
            }

        vector <int> pi = prefix_function(fs);
        r--;
        int cnt = count(pi.begin(), pi.end(), r);
        cout << cnt;}
        return 0;
    }