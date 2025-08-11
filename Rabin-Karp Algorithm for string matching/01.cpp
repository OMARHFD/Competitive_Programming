//link : https://www.spoj.com/problems/NAJPF/
#include <bits/stdc++.h>
using namespace std;

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurrences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i+S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurrences.push_back(i);
    }
    if (occurrences.size()==0)
{        cout << "Not Found"<<endl;
        cout<<endl;}
    else{
        cout << occurrences.size()<<endl;
        for (auto ele : occurrences)
            {
                cout << ele+1 <<' ';
            }}
            cout << endl ;
        return occurrences;

}




int main ()
    {
        vector < pair < string, string>> answers;
        int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        string t, s;
        cin >> t >> s;
        answers.push_back({t, s});
}

        for (auto ele :answers )
            {
                rabin_karp(ele.second, ele.first) ;
            }

        return 0;
    }