/*
HASHING
Problem:
Time limit: 1.00 s
Memory limit: 512 MB

You are given a string that consists of n characters between a–z. The positions of the string are indexed 1,2,\dots,n.
Your task is to process m operations of the following types:

Change the character at position k to x
Check if the substring from position a to position b is a palindrome

Input
The first input line has two integers n and m: the length of the string and the number of operations.
The next line has a string that consists of n characters.
Finally, there are m lines that describe the operations. Each line is of the form "1 k x" or "2 a b".
Output
For each operation 2, print YES if the substring is a palindrome and NO otherwise.
Constraints

1 \le n, m \le 2 \cdot 10^5
1 \le k \le n
1 \le a \le b \le n

Example
Input:
7 5
aybabtu
2 3 5
1 3 x
2 3 5
1 5 x
2 3 5

Output:
YES
NO
YES
*/


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1000000007;
const ll P = 911382323; // random large base
const int MAXN = 200000 + 5;

int n, m;
string s;
ll pwr[MAXN];

// Segment tree
struct SegTree {
    int N;
    vector<ll> tree;

    SegTree(int n) {
        N = n;
        tree.assign(4*n, 0);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node] = val % MOD;
            return;
        }
        int mid = (l+r)/2;
        if (idx <= mid) update(node*2, l, mid, idx, val);
        else update(node*2+1, mid+1, r, idx, val);
        tree[node] = (tree[node*2] + tree[node*2+1]) % MOD;
    }

    void update(int idx, ll val) { update(1,1,N,idx,val); }

    ll query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l+r)/2;
        return (query(node*2,l,mid,ql,qr) + query(node*2+1,mid+1,r,ql,qr)) % MOD;
    }

    ll query(int l, int r) { return query(1,1,N,l,r); }
};

SegTree fw(1), bw(1);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;
    s = "#" + s; // 1-indexed

    // Precompute powers
    pwr[0] = 1;
    for (int i=1; i<=n; i++) pwr[i] = (pwr[i-1] * P) % MOD;

    fw = SegTree(n);
    bw = SegTree(n);

    // Build segment trees
    for (int i=1; i<=n; i++) {
        int val = s[i]-'a'+1;
        fw.update(i, (val * pwr[i]) % MOD);
        bw.update(i, (val * pwr[n-i+1]) % MOD);
    }

    while (m--) {
        int type; cin >> type;
        if (type == 1) {
            int k; char x; cin >> k >> x;
            int oldVal = s[k]-'a'+1;
            int newVal = x-'a'+1;
            s[k] = x;
            fw.update(k, (newVal * pwr[k]) % MOD);
            bw.update(k, (newVal * pwr[n-k+1]) % MOD);
        } else {
            int a,b; cin >> a >> b;
            // forward hash
            ll h1 = fw.query(a,b) * pwr[n-b] % MOD;
            // backward hash
            ll h2 = bw.query(a,b) * pwr[a-1] % MOD;
            if (h1 == h2) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}
