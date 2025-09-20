#include <bits/stdc++.h>
using namespace std;

// Computes suffix array in O(n log n) using prefix doubling
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    const int ALPH = 256;
    vector<int> p(n), c(n), cnt(max(ALPH, n), 0);

    // Initial counting sort by single characters
    for (char ch : s) cnt[ch]++;
    for (int i = 1; i < ALPH; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;

    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]]) classes++;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; h++) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }

        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];

        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int,int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int,int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev) classes++;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

// Computes LCP array in O(n) using Kasai's algorithm
vector<int> buildLCP(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    vector<int> lcp(n, 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == 0) {
            k = 0;  // First suffix has no previous suffix
            continue;
        }
        int j = sa[rank[i] - 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k > 0) k--;
    }
    return lcp;
}

int main() {
    string s;
    cin >> s;
    s += "$";  // Append sentinel
    vector<int> sa = buildSuffixArray(s);
    vector<int> lcp = buildLCP(s, sa);

    cout << "Suffix Array:\n";
    for (int x : sa) cout << x << " ";
    cout << "\nLCP Array:\n";
    for (int x : lcp) cout << x << " ";
    cout << endl;
}
