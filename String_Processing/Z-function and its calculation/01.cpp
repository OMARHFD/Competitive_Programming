// link : https://codeforces.com/problemset/problem/126/B
#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}



int main ()
    {
        string s;
        cin >> s;
        int n;
        n=s.size();
        int answer = -1;
        vector<int> Z = z_function(s);
        for (int i=0;i<n;i++)
            {
                if (i==1 && Z[i] + 1 == n)
                    {
                        answer=max(answer,Z[i]);
                    }
                if (Z[i] + i == n )
                {
                    bool ok = false;
                    for (int j = 0; j < n - Z[i]; j++) if (Z[j] >= Z[i]) ok = true;
                    if (ok) answer = max(answer, Z[i]);
                }
            }
        if (answer == -1)
            cout << "Just a legend";
        else    
            {
                for(int i =0 ; i<answer ;i++)
                    cout << s[i];
            }




        return 0;
    }




