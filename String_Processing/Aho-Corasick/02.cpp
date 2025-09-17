


//BETTER DOCUMENTATION
#include <bits/stdc++.h>
using namespace std;

const int K = 26;


const int MOD = 1e9+7;
struct Vertex {
    int next[K];
    int link;
    vector<int> out;
    Vertex() {
        fill(begin(next), end(next), -1);
        link = -1;
    }
};

vector<Vertex> t(1);

void add_string(const string &s, int id) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back();
        }
        v = t[v].next[c];
    }
    t[v].out.push_back(id);
}

int main() {
    string s;
    cin >> s;
    int n; cin >> n;
    vector<string> pats(n);
    for (int i = 0; i < n; i++) {
        cin >> pats[i];
        add_string(pats[i], i);
    }

    // build automaton
    queue<int> q;
    t[0].link = 0;
    for (int c = 0; c < K; c++) {
        if (t[0].next[c] != -1) {
            t[t[0].next[c]].link = 0;
            q.push(t[0].next[c]);
        } else {
            t[0].next[c] = 0;
        }
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int c = 0; c < K; c++) {
            if (t[v].next[c] != -1) {
                int u = t[v].next[c];
                t[u].link = t[t[v].link].next[c];
                t[u].out.insert(t[u].out.end(),
                                t[t[u].link].out.begin(),
                                t[t[u].link].out.end());
                q.push(u);
            } else {
                t[v].next[c] = t[t[v].link].next[c];
            }
        }
    }

    // DP
    vector<int> dp(s.size()+1, 0);
    dp[0] = 1;
    int v = 0;
    for (int pos = 0; pos < (int)s.size(); pos++) {
        int c = s[pos] - 'a';
        v = t[v].next[c];
        for (int pat_idx : t[v].out) {
            int len = pats[pat_idx].size();
            dp[pos+1] = (dp[pos+1] + dp[pos+1 - len]) % MOD;
        }
    }

    cout << dp[s.size()] << "\n";
}
