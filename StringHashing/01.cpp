// link : https://codeforces.com/contest/271/problem/D
#include <bits/stdc++.h>
using namespace std;



int count_unique_substrings(string const& s , vector<int>good , int k) {
    int n = s.size();

    const int p = 31;
    const int m = 1e9 + 9;
    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++)
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(n + 1, 0);
    vector<int> isgood(n+1,0);
    isgood[0]=good[(s[0] - 'a')];
    for (int i = 0; i < n; i++)

{        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
        isgood[i+1] = isgood[i]+good[(s[i] - 'a')];}

    int cnt = 0;
    for (int l = 1; l <= n; l++) {
        unordered_set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
            int condition = isgood[i+l] - isgood[i];
            long long cur_h = (h[i + l] + m - h[i]) % m;
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            if ((condition-k) <= 0)
                {  
                    hs.insert(cur_h);}
        }
        cnt += hs.size();
    }
    return cnt;
}
int main ()
    {
    string s1;
    string line2;
    int x;

    getline(cin, s1);   // first line as string
    getline(cin, line2); // second line as string representing bits
    cin >> x;           // third line as int

    // Convert second line string to vector<int>
    vector<int> vec;
    for (char c : line2) {
        vec.push_back(c - '0');  // convert char '0' or '1' to int 0 or 1
    }

    for (int &val : vec) {
    if (val == 0)
        val = 1;
    else if (val == 1)
        val = 0;  // if you want to swap 1 → 0 as well
}

    cout << count_unique_substrings(s1 , vec , x);




        return 0;
    }