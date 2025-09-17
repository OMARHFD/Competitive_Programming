//link :https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620
#include <bits/stdc++.h>
using namespace std;

const int K = 58;

struct Vertex {
    int next[K];
    int link;
    Vertex() {
        fill(begin(next), end(next), -1);
        link = -1;
    }
};

vector<Vertex> t(1);
vector<int> end_nodes;

void add_string(const string &s) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'A';
        if (t[v].next[c] == -1) {
            t[v].next[c] = t.size();
            t.emplace_back();
        }
        v = t[v].next[c];
    }
    end_nodes.push_back(v);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
int pr;
cin>>pr;
while(pr--) {    
    t.assign(1, Vertex());  // reset trie with one root node
    end_nodes.clear();
    string s;
    cin >> s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string pat;
        cin >> pat;
        add_string(pat);
    }

    queue<int> q;
    t[0].link = 0;
    for (int c = 0; c < K; c++) {
        if (t[0].next[c] != -1) {
            int u = t[0].next[c];
            t[u].link = 0;
            q.push(u);
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
                q.push(u);
            } else {
                t[v].next[c] = t[t[v].link].next[c];
            }
        }
    }

    vector<int> cnt(t.size(), 0);
    int v = 0;
    for (char ch : s) {
        int c = ch - 'A';
        v = t[v].next[c];
        cnt[v]++;
    }

    vector<vector<int>> adj(t.size());
    for (int i = 1; i < t.size(); i++) {
        adj[t[i].link].push_back(i);
    }

    vector<int> order;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int child : adj[u]) {
            q.push(child);
        }
    }
    reverse(order.begin(), order.end());

    for (int u : order) {
        if (u != 0) {
            cnt[t[u].link] += cnt[u];
        }
    }

    for (int i = 0; i < n; i++) {
        if (cnt[end_nodes[i]] > 0) {
            cout << "y\n";
        } else {
            cout << "n\n";
        }
    }}

    return 0;
}