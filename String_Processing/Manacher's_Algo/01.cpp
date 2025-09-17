#include <bits/stdc++.h>
using namespace std;

string manacher(string s) {
    int n = s.size();
    // Transform: add separators
    string t = "#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    int m = t.size();

    vector<int> p(m, 0);  // palindrome radius
    int center = 0, right = 0;
    int max_len = 0, max_center = 0;

    for (int i = 0; i < m; i++) {
        int mirror = 2*center - i;
        if (i < right)
            p[i] = min(right - i, p[mirror]);

        // expand around i
        int a = i - (1 + p[i]), b = i + (1 + p[i]);
        while (a >= 0 && b < m && t[a] == t[b]) {
            p[i]++;
            a--; b++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > max_len) {
            max_len = p[i];
            max_center = i;
        }
    }

    // extract result
    int start = (max_center - max_len) / 2;
    return s.substr(start, max_len);
}

int main() {
    string s;
    cin >> s;
    cout << manacher(s) << "\n";
}
